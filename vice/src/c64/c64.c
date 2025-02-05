/*
 * c64.c
 *
 * Written by
 *  Andreas Boose <viceteam@t-online.de>
 *  Ettore Perazzoli <ettore@comm2000.it>
 *  Teemu Rantanen <tvr@cs.hut.fi>
 *
 * This file is part of VICE, the Versatile Commodore Emulator.
 * See README for copyright notice.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307  USA.
 *
 */

#include "vice.h"

#include <stdio.h>
#include <stdlib.h>

#include "autostart.h"
#include "c64-cmdline-options.h"
#include "c64-resources.h"
#include "c64-snapshot.h"
#include "c64.h"
#include "c64_256k.h"
#include "c64cart.h"
#define CARTRIDGE_INCLUDE_SLOTMAIN_API
#include "c64cartsystem.h"
#undef CARTRIDGE_INCLUDE_SLOTMAIN_API
#include "c64cia.h"
#include "c64export.h"
#include "c64fastiec.h"
#include "c64gluelogic.h"
#include "c64iec.h"
#include "c64keyboard.h"
#include "c64mem.h"
#include "c64memrom.h"
#include "c64rsuser.h"
#include "c64ui.h"
#include "cartio.h"
#include "cartridge.h"
#include "cia.h"
#include "clkguard.h"
#include "datasette.h"
#include "debug.h"
#include "drive-cmdline-options.h"
#include "drive-resources.h"
#include "drive.h"
#include "drivecpu.h"
#include "imagecontents.h"
#include "kbdbuf.h"
#include "keyboard.h"
#include "lightpen.h"
#include "log.h"
#include "machine-drive.h"
#include "machine-printer.h"
#include "machine-video.h"
#include "machine.h"
#include "maincpu.h"
#include "mem.h"
#include "monitor.h"
#include "network.h"
#include "parallel.h"
#include "patchrom.h"
#include "plus256k.h"
#include "plus60k.h"
#include "printer.h"
#include "psid.h"
#include "resources.h"
#include "rs232drv.h"
#include "rsuser.h"
#include "screenshot.h"
#include "serial.h"
#include "sid-cmdline-options.h"
#include "sid-resources.h"
#include "sid/sid.h"
#include "sound.h"
#include "tape.h"
#include "traps.h"
#include "types.h"
#include "vicii.h"
#include "vicii-mem.h"
#include "video.h"
#include "vsidui.h"
#include "vsync.h"

#ifdef HAVE_MOUSE
#include "mouse.h"
#endif

machine_context_t machine_context;

#define NUM_KEYBOARD_MAPPINGS 3

const char *machine_keymap_res_name_list[NUM_KEYBOARD_MAPPINGS] = {
    "KeymapSymFile",
    "KeymapPosFile",
    "KeymapSymDeFile"
};

char *machine_keymap_file_list[NUM_KEYBOARD_MAPPINGS] = {
    NULL, NULL, NULL
};

const char machine_name[] = "C64";
/* Moved to c64mem.c/c64memsc.c
int machine_class = VICE_MACHINE_C64;
*/
static void machine_vsync_hook(void);

/* ------------------------------------------------------------------------- */

static const trap_t c64_serial_traps[] = {
    { "SerialListen", 0xED24, 0xEDAB, { 0x20, 0x97, 0xEE }, serial_trap_attention, c64memrom_trap_read, c64memrom_trap_store },
    { "SerialSaListen", 0xED37, 0xEDAB, { 0x20, 0x8E, 0xEE }, serial_trap_attention, c64memrom_trap_read, c64memrom_trap_store },
    { "SerialSendByte", 0xED41, 0xEDAB, { 0x20, 0x97, 0xEE }, serial_trap_send, c64memrom_trap_read, c64memrom_trap_store },
    { "SerialReceiveByte", 0xEE14, 0xEDAB, { 0xA9, 0x00, 0x85 }, serial_trap_receive, c64memrom_trap_read, c64memrom_trap_store },
    { "SerialReady", 0xEEA9, 0xEDAB, { 0xAD, 0x00, 0xDD }, serial_trap_ready, c64memrom_trap_read, c64memrom_trap_store },
    { NULL, 0, 0, { 0, 0, 0 }, NULL, NULL, NULL }
};

/* Tape traps.  */
static const trap_t c64_tape_traps[] = {
    { "TapeFindHeader", 0xF72F, 0xF732, { 0x20, 0x41, 0xF8 }, tape_find_header_trap, c64memrom_trap_read, c64memrom_trap_store },
    { "TapeReceive", 0xF8A1, 0xFC93, { 0x20, 0xBD, 0xFC }, tape_receive_trap, c64memrom_trap_read, c64memrom_trap_store },
    { NULL, 0, 0, { 0, 0, 0 }, NULL, NULL, NULL }
};

static const tape_init_t tapeinit = {
    0xb2,
    0x90,
    0x93,
    0x29f,
    0,
    0xc1,
    0xae,
    0x277,
    0xc6,
    c64_tape_traps,
    36 * 8,
    54 * 8,
    55 * 8,
    73 * 8,
    74 * 8,
    100 * 8
};

static log_t c64_log = LOG_ERR;
static machine_timing_t machine_timing;

/* ------------------------------------------------------------------------ */

static io_source_t vicii_d000_device = {
    "VIC-II",
    IO_DETACH_CART, /* dummy */
    NULL,           /* dummy */
    0xd000, 0xd0ff, 0x3f,
    1, /* read is always valid */
    vicii_store,
    vicii_read,
    vicii_peek,
    vicii_dump,
    0, /* dummy (not a cartridge) */
    1, /* priority, device and mirrors never involved in collisions */
    0
};

static io_source_t vicii_d100_device = {
    "VIC-II $D100-$D1FF mirrors",
    IO_DETACH_CART, /* dummy */
    NULL,           /* dummy */
    0xd100, 0xd1ff, 0x3f,
    1, /* read is always valid */
    vicii_store,
    vicii_read,
    vicii_peek,
    vicii_dump,
    0, /* dummy (not a cartridge) */
    1, /* priority, device and mirrors never involved in collisions */
    0
};

static io_source_t vicii_d200_device = {
    "VIC-II $D200-$D2FF mirrors",
    IO_DETACH_CART, /* dummy */
    NULL,           /* dummy */
    0xd200, 0xd2ff, 0x3f,
    1, /* read is always valid */
    vicii_store,
    vicii_read,
    vicii_peek,
    vicii_dump,
    0, /* dummy (not a cartridge) */
    1, /* priority, device and mirrors never involved in collisions */
    0
};

static io_source_t vicii_d300_device = {
    "VIC-II $D300-$D3FF mirrors",
    IO_DETACH_CART, /* dummy */
    NULL,           /* dummy */
    0xd300, 0xd3ff, 0x3f,
    1, /* read is always valid */
    vicii_store,
    vicii_read,
    vicii_peek,
    vicii_dump,
    0, /* dummy (not a cartridge) */
    1, /* priority, device and mirrors never involved in collisions */
    0
};

static io_source_t sid_d400_device = {
    "SID",
    IO_DETACH_CART, /* dummy */
    NULL,           /* dummy */
    0xd400, 0xd4ff, 0x1f,
    1, /* read is always valid */
    sid_store,
    sid_read,
    sid_peek,
    NULL, /* TODO: dump */
    0, /* dummy (not a cartridge) */
    -1, /* priority, device and mirrors never involved in collisions */
    0
};

static io_source_t sid_d500_device = {
    "SID $D500-$D5FF mirrors",
    IO_DETACH_CART, /* dummy */
    NULL,           /* dummy */
    0xd500, 0xd5ff, 0x1f,
    1, /* read is always valid */
    sid_store,
    sid_read,
    sid_peek,
    NULL, /* TODO: dump */
    0, /* dummy (not a cartridge) */
    -1, /* priority, device and mirrors never involved in collisions */
    0
};

static io_source_t sid_d600_device = {
    "SID $D600-$D6FF mirrors",
    IO_DETACH_CART, /* dummy */
    NULL,           /* dummy */
    0xd600, 0xd6ff, 0x1f,
    1, /* read is always valid */
    sid_store,
    sid_read,
    sid_peek,
    NULL, /* TODO: dump */
    0, /* dummy (not a cartridge) */
    -1, /* priority, device and mirrors never involved in collisions */
    0
};

static io_source_t sid_d700_device = {
    "SID $D700-$D7FF mirrors",
    IO_DETACH_CART, /* dummy */
    NULL,           /* dummy */
    0xd700, 0xd7ff, 0x1f,
    1, /* read is always valid */
    sid_store,
    sid_read,
    sid_peek,
    NULL, /* TODO: dump */
    0, /* dummy (not a cartridge) */
    -1, /* priority, device and mirrors never involved in collisions */
    0
};

static io_source_list_t *vicii_d000_list_item = NULL;
static io_source_list_t *vicii_d100_list_item = NULL;
static io_source_list_t *vicii_d200_list_item = NULL;
static io_source_list_t *vicii_d300_list_item = NULL;
static io_source_list_t *sid_d400_list_item = NULL;
static io_source_list_t *sid_d500_list_item = NULL;
static io_source_list_t *sid_d600_list_item = NULL;
static io_source_list_t *sid_d700_list_item = NULL;

void c64io_vicii_init(void)
{
    vicii_d000_list_item = io_source_register(&vicii_d000_device);
    vicii_d100_list_item = io_source_register(&vicii_d100_device);
    vicii_d200_list_item = io_source_register(&vicii_d200_device);
    vicii_d300_list_item = io_source_register(&vicii_d300_device);
}

void c64io_vicii_deinit(void)
{
    if (vicii_d000_list_item != NULL) {
        io_source_unregister(vicii_d000_list_item);
        vicii_d000_list_item = NULL;
    }

    if (vicii_d100_list_item != NULL) {
        io_source_unregister(vicii_d100_list_item);
        vicii_d100_list_item = NULL;
    }

    if (vicii_d200_list_item != NULL) {
        io_source_unregister(vicii_d200_list_item);
        vicii_d200_list_item = NULL;
    }

    if (vicii_d300_list_item != NULL) {
        io_source_unregister(vicii_d300_list_item);
        vicii_d300_list_item = NULL;
    }
}

/* C64-specific I/O initialization. */
static void c64io_init(void)
{
    c64io_vicii_init();
    sid_d400_list_item = io_source_register(&sid_d400_device);
    sid_d500_list_item = io_source_register(&sid_d500_device);
    sid_d600_list_item = io_source_register(&sid_d600_device);
    sid_d700_list_item = io_source_register(&sid_d700_device);
}

/* ------------------------------------------------------------------------ */

/* C64-specific resource initialization.  This is called before initializing
   the machine itself with `machine_init()'.  */
int machine_resources_init(void)
{
    if (traps_resources_init() < 0
        || rombanks_resources_init() < 0
        || vsync_resources_init() < 0
        || machine_video_resources_init() < 0
        || c64_resources_init() < 0
        || c64export_resources_init() < 0
        || plus60k_resources_init() < 0
        || plus256k_resources_init() < 0
        || c64_256k_resources_init() < 0
        || vicii_resources_init() < 0
        || sound_resources_init() < 0
        || sid_resources_init() < 0
        || rs232drv_resources_init() < 0
        || rsuser_resources_init() < 0
        || serial_resources_init() < 0
        || printer_resources_init() < 0
#ifdef HAVE_MOUSE
        || mouse_resources_init() < 0
        || lightpen_resources_init() < 0
#endif
#ifndef COMMON_KBD
        || kbd_resources_init() < 0
#endif
        || drive_resources_init() < 0
        || datasette_resources_init() < 0
        || c64_glue_resources_init() < 0
        || cartio_resources_init() < 0
        || cartridge_resources_init() < 0) {
        return -1;
    }
    if (vsid_mode && psid_init_resources() < 0) {
        return -1;
    }

    return 0;
}

void machine_resources_shutdown(void)
{
    serial_shutdown();
    video_resources_shutdown();
    c64_resources_shutdown();
    plus60k_resources_shutdown();
    plus256k_resources_shutdown();
    c64_256k_resources_shutdown();
    sound_resources_shutdown();
    rs232drv_resources_shutdown();
    printer_resources_shutdown();
    drive_resources_shutdown();
    cartridge_resources_shutdown();
    rombanks_resources_shutdown();
    cartio_shutdown();
}

/* C64-specific command-line option initialization.  */
int machine_cmdline_options_init(void)
{
    if (vsid_mode) {
        if (sound_cmdline_options_init() < 0
            || sid_cmdline_options_init() < 0
            || psid_init_cmdline_options() < 0
            || vsync_cmdline_options_init() < 0) {
            return -1;
        }

        return 0;
    }

    if (traps_cmdline_options_init() < 0
        || vsync_cmdline_options_init() < 0
        || video_init_cmdline_options() < 0
        || c64_cmdline_options_init() < 0
        || plus60k_cmdline_options_init() < 0
        || plus256k_cmdline_options_init() < 0
        || c64_256k_cmdline_options_init() < 0
        || vicii_cmdline_options_init() < 0
        || sound_cmdline_options_init() < 0
        || sid_cmdline_options_init() < 0
        || rs232drv_cmdline_options_init() < 0
        || rsuser_cmdline_options_init() < 0
        || serial_cmdline_options_init() < 0
        || printer_cmdline_options_init() < 0
#ifdef HAVE_MOUSE
        || mouse_cmdline_options_init() < 0
        || lightpen_cmdline_options_init() < 0
#endif
#ifndef COMMON_KBD
        || kbd_cmdline_options_init() < 0
#endif
        || drive_cmdline_options_init() < 0
        || datasette_cmdline_options_init() < 0
        || c64_glue_cmdline_options_init() < 0
        || cartio_cmdline_options_init() < 0
        || cartridge_cmdline_options_init() < 0) {
        return -1;
    }

    return 0;
}

static void c64_monitor_init(void)
{
    unsigned int dnr;
    monitor_cpu_type_t asm6502;
    monitor_interface_t *drive_interface_init[DRIVE_NUM];
    monitor_cpu_type_t *asmarray[2];

    asmarray[0]=&asm6502;
    asmarray[1]=NULL;

    asm6502_init(&asm6502);

    for (dnr = 0; dnr < DRIVE_NUM; dnr++) {
        drive_interface_init[dnr] = drivecpu_monitor_interface_get(dnr);
    }

    /* Initialize the monitor.  */
    monitor_init(maincpu_monitor_interface_get(), drive_interface_init, asmarray);
}

void machine_setup_context(void)
{
    cia1_setup_context(&machine_context);
    cia2_setup_context(&machine_context);
    cartridge_setup_context(&machine_context);
    machine_printer_setup_context(&machine_context);
}

/* C64-specific initialization.  */
int machine_specific_init(void)
{
    int delay;

    c64_log = log_open("C64");

    if (mem_load() < 0) {
        return -1;
    }

    if (!vsid_mode) {
        /* Setup trap handling.  */
        traps_init();

        /* Initialize serial traps.  */
        if (serial_init(c64_serial_traps) < 0) {
            return -1;
        }

        serial_trap_init(0xa4);
        serial_iec_bus_init();

        /* Initialize RS232 handler.  */
        rs232drv_init();
        c64_rsuser_init();

        /* Initialize print devices.  */
        printer_init();

        /* Initialize the tape emulation.  */
        tape_init(&tapeinit);

        /* Initialize the datasette emulation.  */
        datasette_init();

        /* Fire up the hardware-level drive emulation.  */
        drive_init();

        resources_get_int("AutostartDelay", &delay);
        if (delay == 0) {
            delay = 3; /* default */
        }

        /* Initialize autostart.  */
        autostart_init((CLOCK)(delay * C64_PAL_RFSH_PER_SEC * C64_PAL_CYCLES_PER_RFSH), 1, 0xcc, 0xd1, 0xd3, 0xd5);
    }

    if (vicii_init(VICII_STANDARD) == NULL && !video_disabled_mode) {
        return -1;
    }

    c64_mem_init();

    cia1_init(machine_context.cia1);
    cia2_init(machine_context.cia2);

    if (!vsid_mode) {

#ifndef COMMON_KBD
        /* Initialize the keyboard.  */
        if (c64_kbd_init() < 0) {
            return -1;
        }
#endif

        c64keyboard_init();
    }

    c64_monitor_init();

    /* Initialize vsync and register our hook function.  */
    vsync_init(machine_vsync_hook);
    vsync_set_machine_parameter(machine_timing.rfsh_per_sec, machine_timing.cycles_per_sec);

    /* Initialize native sound chip */
    sid_sound_chip_init();

    /* Initialize cartridge based sound chips */
    cartridge_sound_chip_init();

    /* Initialize sound.  Notice that this does not really open the audio
       device yet.  */
    sound_init(machine_timing.cycles_per_sec, machine_timing.cycles_per_rfsh);

    /* Initialize keyboard buffer.  */
    kbdbuf_init(631, 198, 10, (CLOCK)(machine_timing.rfsh_per_sec * machine_timing.cycles_per_rfsh));

    /* Initialize the C64-specific I/O */
    c64io_init();

    /* Initialize the C64-specific part of the UI.  */
    if (!console_mode) {
        if (vsid_mode) {
            vsid_ui_init();
        } else if (machine_class == VICE_MACHINE_C64SC) {
            c64scui_init();
        } else {
            c64ui_init();
        }
    }

    /* Initialize glue logic.  */
    c64_glue_init();

    if (!vsid_mode) {
        /* Initialize the +60K.  */
        plus60k_init();

        /* Initialize the +256K.  */
        plus256k_init();

        /* Initialize the C64 256K.  */
        c64_256k_init();

#ifdef HAVE_MOUSE
        /* Initialize mouse support (if present).  */
        mouse_init();

        /* Initialize lightpen support and register VICII callbacks */
        lightpen_init();
        lightpen_register_timing_callback(vicii_lightpen_timing, 0);
        lightpen_register_trigger_callback(vicii_trigger_light_pen);
#endif
        c64iec_init();
        c64fastiec_init();

        cartridge_init();
    }

    machine_drive_stub();
#if defined (USE_XF86_EXTENSIONS) && (defined(USE_XF86_VIDMODE_EXT) || defined (HAVE_XRANDR))
    {
        /* set fullscreen if user used `-fullscreen' on cmdline */
        int fs;
        resources_get_int("UseFullscreen", &fs);
        if (fs) {
            resources_set_int("VICIIFullscreen", 1);
        }
    }
#endif

    return 0;
}

/* C64-specific reset sequence.  */
void machine_specific_reset(void)
{
    serial_traps_reset();

    ciacore_reset(machine_context.cia1);
    ciacore_reset(machine_context.cia2);
    sid_reset();

    if (!vsid_mode) {

        rs232drv_reset(); /* driver is used by both user- and expansion port ? */
        rsuser_reset();

        printer_reset();

        /* FIXME: whats actually broken here? */
        /* reset_reu(); */
    }

    /* The VIC-II must be the *last* to be reset.  */
    vicii_reset();

    if (vsid_mode) {
        psid_init_driver();
        psid_init_tune();
        return;
    }

    cartridge_reset();
    drive_reset();
    datasette_reset();
    plus60k_reset();
    plus256k_reset();
    c64_256k_reset();
}

void machine_specific_powerup(void)
{
    vicii_reset_registers();
}

void machine_specific_shutdown(void)
{
    /* and the tape */
    tape_image_detach_internal(1);

    /* and cartridge */
    cartridge_detach_image(-1);

    ciacore_shutdown(machine_context.cia1);
    ciacore_shutdown(machine_context.cia2);

    /* close the video chip(s) */
    vicii_shutdown();

    plus60k_shutdown();
    plus256k_shutdown();
    c64_256k_shutdown();

    cartridge_shutdown();

    if (vsid_mode) {
        vsid_ui_close();
    }

    c64ui_shutdown();
}

void machine_handle_pending_alarms(int num_write_cycles)
{
    vicii_handle_pending_alarms_external(num_write_cycles);
}

/* ------------------------------------------------------------------------- */

/* This hook is called at the end of every frame.  */
static void machine_vsync_hook(void)
{
    CLOCK sub;

    if (vsid_mode) {
        unsigned int playtime;
        static unsigned int time = 0;

        playtime = (psid_increment_frames() * machine_timing.cycles_per_rfsh) / machine_timing.cycles_per_sec;
        if (playtime != time) {
            vsid_ui_display_time(playtime);
            time = playtime;
        }
        clk_guard_prevent_overflow(maincpu_clk_guard);
        return;
    }

    network_hook();

    drive_vsync_hook();

    autostart_advance();

    screenshot_record();

    sub = clk_guard_prevent_overflow(maincpu_clk_guard);

    /* The drive has to deal both with our overflowing and its own one, so
       it is called even when there is no overflowing in the main CPU.  */
    drivecpu_prevent_clk_overflow_all(sub);
}

void machine_set_restore_key(int v)
{
    c64keyboard_restore_key(v);
}

int machine_has_restore_key(void)
{
    return 1;
}

/* ------------------------------------------------------------------------- */

long machine_get_cycles_per_second(void)
{
    return machine_timing.cycles_per_sec;
}

long machine_get_cycles_per_frame(void)
{
    return machine_timing.cycles_per_rfsh;
}

void machine_get_line_cycle(unsigned int *line, unsigned int *cycle, int *half_cycle)
{
    *line = (unsigned int)((maincpu_clk) / machine_timing.cycles_per_line % machine_timing.screen_lines);
    *cycle = (unsigned int)((maincpu_clk) % machine_timing.cycles_per_line);
    *half_cycle = (int)-1;
}

void machine_change_timing(int timeval)
{
    int border_mode;

    switch (timeval) {
        default:
        case MACHINE_SYNC_PAL ^ VICII_BORDER_MODE(VICII_NORMAL_BORDERS):
        case MACHINE_SYNC_NTSC ^ VICII_BORDER_MODE(VICII_NORMAL_BORDERS):
        case MACHINE_SYNC_NTSCOLD ^ VICII_BORDER_MODE(VICII_NORMAL_BORDERS):
        case MACHINE_SYNC_PALN ^ VICII_BORDER_MODE(VICII_NORMAL_BORDERS):
            timeval ^= VICII_BORDER_MODE(VICII_NORMAL_BORDERS);
            border_mode = VICII_NORMAL_BORDERS;
            break;
        case MACHINE_SYNC_PAL ^ VICII_BORDER_MODE(VICII_FULL_BORDERS):
        case MACHINE_SYNC_NTSC ^ VICII_BORDER_MODE(VICII_FULL_BORDERS):
        case MACHINE_SYNC_NTSCOLD ^ VICII_BORDER_MODE(VICII_FULL_BORDERS):
        case MACHINE_SYNC_PALN ^ VICII_BORDER_MODE(VICII_FULL_BORDERS):
            timeval ^= VICII_BORDER_MODE(VICII_FULL_BORDERS);
            border_mode = VICII_FULL_BORDERS;
            break;
        case MACHINE_SYNC_PAL ^ VICII_BORDER_MODE(VICII_DEBUG_BORDERS):
        case MACHINE_SYNC_NTSC ^ VICII_BORDER_MODE(VICII_DEBUG_BORDERS):
        case MACHINE_SYNC_NTSCOLD ^ VICII_BORDER_MODE(VICII_DEBUG_BORDERS):
        case MACHINE_SYNC_PALN ^ VICII_BORDER_MODE(VICII_DEBUG_BORDERS):
            timeval ^= VICII_BORDER_MODE(VICII_DEBUG_BORDERS);
            border_mode = VICII_DEBUG_BORDERS;
            break;
    }

    switch (timeval) {
        case MACHINE_SYNC_PAL:
            machine_timing.cycles_per_sec = C64_PAL_CYCLES_PER_SEC;
            machine_timing.cycles_per_rfsh = C64_PAL_CYCLES_PER_RFSH;
            machine_timing.rfsh_per_sec = C64_PAL_RFSH_PER_SEC;
            machine_timing.cycles_per_line = C64_PAL_CYCLES_PER_LINE;
            machine_timing.screen_lines = C64_PAL_SCREEN_LINES;
            break;
        case MACHINE_SYNC_NTSC:
            machine_timing.cycles_per_sec = C64_NTSC_CYCLES_PER_SEC;
            machine_timing.cycles_per_rfsh = C64_NTSC_CYCLES_PER_RFSH;
            machine_timing.rfsh_per_sec = C64_NTSC_RFSH_PER_SEC;
            machine_timing.cycles_per_line = C64_NTSC_CYCLES_PER_LINE;
            machine_timing.screen_lines = C64_NTSC_SCREEN_LINES;
            break;
        case MACHINE_SYNC_NTSCOLD:
            machine_timing.cycles_per_sec = C64_NTSCOLD_CYCLES_PER_SEC;
            machine_timing.cycles_per_rfsh = C64_NTSCOLD_CYCLES_PER_RFSH;
            machine_timing.rfsh_per_sec = C64_NTSCOLD_RFSH_PER_SEC;
            machine_timing.cycles_per_line = C64_NTSCOLD_CYCLES_PER_LINE;
            machine_timing.screen_lines = C64_NTSCOLD_SCREEN_LINES;
            break;
        case MACHINE_SYNC_PALN:
            machine_timing.cycles_per_sec = C64_PALN_CYCLES_PER_SEC;
            machine_timing.cycles_per_rfsh = C64_PALN_CYCLES_PER_RFSH;
            machine_timing.rfsh_per_sec = C64_PALN_RFSH_PER_SEC;
            machine_timing.cycles_per_line = C64_PALN_CYCLES_PER_LINE;
            machine_timing.screen_lines = C64_PALN_SCREEN_LINES;
            break;
        default:
            log_error(c64_log, "Unknown machine timing.");
    }

    vsync_set_machine_parameter(machine_timing.rfsh_per_sec, machine_timing.cycles_per_sec);
    sound_set_machine_parameter(machine_timing.cycles_per_sec, machine_timing.cycles_per_rfsh);
    debug_set_machine_parameter(machine_timing.cycles_per_line, machine_timing.screen_lines);
    drive_set_machine_parameter(machine_timing.cycles_per_sec);
    serial_iec_device_set_machine_parameter(machine_timing.cycles_per_sec);
    sid_set_machine_parameter(machine_timing.cycles_per_sec);
    clk_guard_set_clk_base(maincpu_clk_guard, machine_timing.cycles_per_rfsh);

    vicii_change_timing(&machine_timing, border_mode);

    cia1_set_timing(machine_context.cia1, machine_timing.cycles_per_rfsh);
    cia2_set_timing(machine_context.cia2, machine_timing.cycles_per_rfsh);

    machine_trigger_reset(MACHINE_RESET_MODE_HARD);
}

/* ------------------------------------------------------------------------- */

int machine_write_snapshot(const char *name, int save_roms, int save_disks, int event_mode)
{
    return c64_snapshot_write(name, save_roms, save_disks, event_mode);
}

int machine_read_snapshot(const char *name, int event_mode)
{
    return c64_snapshot_read(name, event_mode);
}

/* ------------------------------------------------------------------------- */

int machine_autodetect_psid(const char *name)
{
    if (name == NULL) {
        return -1;
    }

    return psid_load_file(name);
}

void machine_play_psid(int tune)
{
    psid_set_tune(tune);
}

int machine_screenshot(screenshot_t *screenshot, struct video_canvas_s *canvas)
{
    if (canvas != vicii_get_canvas()) {
        return -1;
    }

    vicii_screenshot(screenshot);
    return 0;
}

int machine_canvas_async_refresh(struct canvas_refresh_s *refresh, struct video_canvas_s *canvas)
{
    if (canvas != vicii_get_canvas()) {
        return -1;
    }

    vicii_async_refresh(refresh);
    return 0;
}

void machine_update_memory_ptrs(void)
{
    vicii_update_memory_ptrs_external();
}

int machine_num_keyboard_mappings(void)
{
    return NUM_KEYBOARD_MAPPINGS;
}

struct image_contents_s *machine_diskcontents_bus_read(unsigned int unit)
{
    return diskcontents_iec_read(unit);
}

BYTE machine_tape_type_default(void)
{
    return TAPE_CAS_TYPE_BAS;
}

static int get_cart_emulation_state(void)
{
    int value;

    if (resources_get_int("CartridgeType", &value) < 0) {
        return CARTRIDGE_NONE;
    }

    return value;
}

static int check_cart_range(unsigned int addr)
{
    if (get_cart_emulation_state() == CARTRIDGE_NONE) {
        return 1;
    }

    return (!(addr >= 0x8000 && addr < 0xa000));
}

int machine_addr_in_ram(unsigned int addr)
{
    return ((addr < 0xe000 && !(addr >= 0xa000 && addr < 0xc000)) && check_cart_range(addr));
}

const char *machine_get_name(void)
{
    if (vsid_mode) {
        return "VSID";
    }

    if (machine_class == VICE_MACHINE_C64SC) {
        return "C64SC";
    }

    return machine_name;
}
