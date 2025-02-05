/*
 * vic20machinecontroller.m - VIC20 machine controller
 *
 * Written by
 *  Christian Vogelgsang <chris@vogelgsang.org>
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
 
#include "cartridge.h"
 
#import "vic20machinecontroller.h"

@implementation VIC20MachineController

 - (BOOL)attachCartridge:(int)type image:(NSString *)imageFile
 {
     return cartridge_attach_image(type,[imageFile fileSystemRepresentation]) == 0;
 }

 - (void)detachCartridge:(int)type
 {
     cartridge_detach_image(type);
 }

 - (void)setDefaultCartridge
 {
     cartridge_set_default();
 }

@end
