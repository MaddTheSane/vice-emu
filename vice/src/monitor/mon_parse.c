/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "mon_parse.y"

/* -*- C -*-
 *
 * mon_parse.y - Parser for the VICE built-in monitor.
 *
 * Written by
 *  Daniel Sladic <sladic@eecg.toronto.edu>
 *  Andreas Boose <viceteam@t-online.de>
 *  Thomas Giesel <skoe@directbox.com>
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

#ifndef MINIXVMD
#ifdef __GNUC__
#undef alloca
#define        alloca(n)       __builtin_alloca (n)
#else
#ifdef HAVE_ALLOCA_H
#include <alloca.h>
#else  /* Not HAVE_ALLOCA_H.  */
#if !defined(_AIX) && !defined(WINCE)
#ifndef _MSC_VER
extern char *alloca();
#else
#define alloca(n)   _alloca(n)
#endif  /* MSVC */
#endif /* Not AIX and not WINCE.  */
#endif /* HAVE_ALLOCA_H.  */
#endif /* GCC.  */
#endif /* MINIXVMD */

/* SunOS 4.x specific stuff */
#if defined(sun) || defined(__sun)
#  if !defined(__SVR4) && !defined(__svr4__)
#    ifdef __sparc__
#      define YYFREE
#    endif
#  endif
#endif

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "asm.h"
#include "console.h"
#include "lib.h"
#include "machine.h"
#include "mon_breakpoint.h"
#include "mon_command.h"
#include "mon_disassemble.h"
#include "mon_drive.h"
#include "mon_file.h"
#include "mon_memory.h"
#include "mon_util.h"
#include "montypes.h"
#include "types.h"
#include "uimon.h"


#define join_ints(x,y) (LO16_TO_HI16(x)|y)
#define separate_int1(x) (HI16_TO_LO16(x))
#define separate_int2(x) (LO16(x))

static int yyerror(char *s);
static int temp;
static int resolve_datatype(unsigned guess_type, const char *num);
static int resolve_range(enum t_memspace memspace, MON_ADDR range[2], 
                         const char *num);
static void mon_quit(void);

#ifdef __IBMC__
static void __yy_memcpy (char *to, char *from, int count);
#endif

/* Defined in the lexer */
extern int new_cmd, opt_asm;
extern void free_buffer(void);
extern void make_buffer(char *str);
extern int yylex(void);
extern int cur_len, last_len;

#define ERR_ILLEGAL_INPUT 1     /* Generic error as returned by yacc.  */
#define ERR_RANGE_BAD_START 2
#define ERR_RANGE_BAD_END 3
#define ERR_BAD_CMD 4
#define ERR_EXPECT_CHECKNUM 5
#define ERR_EXPECT_END_CMD 6
#define ERR_MISSING_CLOSE_PAREN 7
#define ERR_INCOMPLETE_COMPARE_OP 8
#define ERR_EXPECT_FILENAME 9
#define ERR_ADDR_TOO_BIG 10
#define ERR_IMM_TOO_BIG 11
#define ERR_EXPECT_STRING 12
#define ERR_UNDEFINED_LABEL 13
#define ERR_EXPECT_DEVICE_NUM 14
#define ERR_EXPECT_ADDRESS 15

#define BAD_ADDR (new_addr(e_invalid_space, 0))
#define CHECK_ADDR(x) ((x) == addr_mask(x))

#define YYDEBUG 1


#line 197 "mon_parse.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_MON_PARSE_H_INCLUDED
# define YY_YY_MON_PARSE_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    H_NUMBER = 258,                /* H_NUMBER  */
    D_NUMBER = 259,                /* D_NUMBER  */
    O_NUMBER = 260,                /* O_NUMBER  */
    B_NUMBER = 261,                /* B_NUMBER  */
    CONVERT_OP = 262,              /* CONVERT_OP  */
    B_DATA = 263,                  /* B_DATA  */
    H_RANGE_GUESS = 264,           /* H_RANGE_GUESS  */
    D_NUMBER_GUESS = 265,          /* D_NUMBER_GUESS  */
    O_NUMBER_GUESS = 266,          /* O_NUMBER_GUESS  */
    B_NUMBER_GUESS = 267,          /* B_NUMBER_GUESS  */
    BAD_CMD = 268,                 /* BAD_CMD  */
    MEM_OP = 269,                  /* MEM_OP  */
    IF = 270,                      /* IF  */
    MEM_COMP = 271,                /* MEM_COMP  */
    MEM_DISK8 = 272,               /* MEM_DISK8  */
    MEM_DISK9 = 273,               /* MEM_DISK9  */
    MEM_DISK10 = 274,              /* MEM_DISK10  */
    MEM_DISK11 = 275,              /* MEM_DISK11  */
    EQUALS = 276,                  /* EQUALS  */
    TRAIL = 277,                   /* TRAIL  */
    CMD_SEP = 278,                 /* CMD_SEP  */
    LABEL_ASGN_COMMENT = 279,      /* LABEL_ASGN_COMMENT  */
    CMD_SIDEFX = 280,              /* CMD_SIDEFX  */
    CMD_RETURN = 281,              /* CMD_RETURN  */
    CMD_BLOCK_READ = 282,          /* CMD_BLOCK_READ  */
    CMD_BLOCK_WRITE = 283,         /* CMD_BLOCK_WRITE  */
    CMD_UP = 284,                  /* CMD_UP  */
    CMD_DOWN = 285,                /* CMD_DOWN  */
    CMD_LOAD = 286,                /* CMD_LOAD  */
    CMD_SAVE = 287,                /* CMD_SAVE  */
    CMD_VERIFY = 288,              /* CMD_VERIFY  */
    CMD_IGNORE = 289,              /* CMD_IGNORE  */
    CMD_HUNT = 290,                /* CMD_HUNT  */
    CMD_FILL = 291,                /* CMD_FILL  */
    CMD_MOVE = 292,                /* CMD_MOVE  */
    CMD_GOTO = 293,                /* CMD_GOTO  */
    CMD_REGISTERS = 294,           /* CMD_REGISTERS  */
    CMD_READSPACE = 295,           /* CMD_READSPACE  */
    CMD_WRITESPACE = 296,          /* CMD_WRITESPACE  */
    CMD_RADIX = 297,               /* CMD_RADIX  */
    CMD_MEM_DISPLAY = 298,         /* CMD_MEM_DISPLAY  */
    CMD_BREAK = 299,               /* CMD_BREAK  */
    CMD_TRACE = 300,               /* CMD_TRACE  */
    CMD_IO = 301,                  /* CMD_IO  */
    CMD_BRMON = 302,               /* CMD_BRMON  */
    CMD_COMPARE = 303,             /* CMD_COMPARE  */
    CMD_DUMP = 304,                /* CMD_DUMP  */
    CMD_UNDUMP = 305,              /* CMD_UNDUMP  */
    CMD_EXIT = 306,                /* CMD_EXIT  */
    CMD_DELETE = 307,              /* CMD_DELETE  */
    CMD_CONDITION = 308,           /* CMD_CONDITION  */
    CMD_COMMAND = 309,             /* CMD_COMMAND  */
    CMD_ASSEMBLE = 310,            /* CMD_ASSEMBLE  */
    CMD_DISASSEMBLE = 311,         /* CMD_DISASSEMBLE  */
    CMD_NEXT = 312,                /* CMD_NEXT  */
    CMD_STEP = 313,                /* CMD_STEP  */
    CMD_PRINT = 314,               /* CMD_PRINT  */
    CMD_DEVICE = 315,              /* CMD_DEVICE  */
    CMD_HELP = 316,                /* CMD_HELP  */
    CMD_WATCH = 317,               /* CMD_WATCH  */
    CMD_DISK = 318,                /* CMD_DISK  */
    CMD_SYSTEM = 319,              /* CMD_SYSTEM  */
    CMD_QUIT = 320,                /* CMD_QUIT  */
    CMD_CHDIR = 321,               /* CMD_CHDIR  */
    CMD_BANK = 322,                /* CMD_BANK  */
    CMD_LOAD_LABELS = 323,         /* CMD_LOAD_LABELS  */
    CMD_SAVE_LABELS = 324,         /* CMD_SAVE_LABELS  */
    CMD_ADD_LABEL = 325,           /* CMD_ADD_LABEL  */
    CMD_DEL_LABEL = 326,           /* CMD_DEL_LABEL  */
    CMD_SHOW_LABELS = 327,         /* CMD_SHOW_LABELS  */
    CMD_RECORD = 328,              /* CMD_RECORD  */
    CMD_MON_STOP = 329,            /* CMD_MON_STOP  */
    CMD_PLAYBACK = 330,            /* CMD_PLAYBACK  */
    CMD_CHAR_DISPLAY = 331,        /* CMD_CHAR_DISPLAY  */
    CMD_SPRITE_DISPLAY = 332,      /* CMD_SPRITE_DISPLAY  */
    CMD_TEXT_DISPLAY = 333,        /* CMD_TEXT_DISPLAY  */
    CMD_SCREENCODE_DISPLAY = 334,  /* CMD_SCREENCODE_DISPLAY  */
    CMD_ENTER_DATA = 335,          /* CMD_ENTER_DATA  */
    CMD_ENTER_BIN_DATA = 336,      /* CMD_ENTER_BIN_DATA  */
    CMD_KEYBUF = 337,              /* CMD_KEYBUF  */
    CMD_BLOAD = 338,               /* CMD_BLOAD  */
    CMD_BSAVE = 339,               /* CMD_BSAVE  */
    CMD_SCREEN = 340,              /* CMD_SCREEN  */
    CMD_UNTIL = 341,               /* CMD_UNTIL  */
    CMD_CPU = 342,                 /* CMD_CPU  */
    CMD_YYDEBUG = 343,             /* CMD_YYDEBUG  */
    CMD_BACKTRACE = 344,           /* CMD_BACKTRACE  */
    CMD_SCREENSHOT = 345,          /* CMD_SCREENSHOT  */
    CMD_PWD = 346,                 /* CMD_PWD  */
    CMD_DIR = 347,                 /* CMD_DIR  */
    CMD_RESOURCE_GET = 348,        /* CMD_RESOURCE_GET  */
    CMD_RESOURCE_SET = 349,        /* CMD_RESOURCE_SET  */
    CMD_ATTACH = 350,              /* CMD_ATTACH  */
    CMD_DETACH = 351,              /* CMD_DETACH  */
    CMD_MON_RESET = 352,           /* CMD_MON_RESET  */
    CMD_TAPECTRL = 353,            /* CMD_TAPECTRL  */
    CMD_CARTFREEZE = 354,          /* CMD_CARTFREEZE  */
    CMD_CPUHISTORY = 355,          /* CMD_CPUHISTORY  */
    CMD_MEMMAPZAP = 356,           /* CMD_MEMMAPZAP  */
    CMD_MEMMAPSHOW = 357,          /* CMD_MEMMAPSHOW  */
    CMD_MEMMAPSAVE = 358,          /* CMD_MEMMAPSAVE  */
    CMD_COMMENT = 359,             /* CMD_COMMENT  */
    CMD_LIST = 360,                /* CMD_LIST  */
    CMD_EXPORT = 361,              /* CMD_EXPORT  */
    CMD_AUTOSTART = 362,           /* CMD_AUTOSTART  */
    CMD_AUTOLOAD = 363,            /* CMD_AUTOLOAD  */
    CMD_LABEL_ASGN = 364,          /* CMD_LABEL_ASGN  */
    L_PAREN = 365,                 /* L_PAREN  */
    R_PAREN = 366,                 /* R_PAREN  */
    ARG_IMMEDIATE = 367,           /* ARG_IMMEDIATE  */
    REG_A = 368,                   /* REG_A  */
    REG_X = 369,                   /* REG_X  */
    REG_Y = 370,                   /* REG_Y  */
    COMMA = 371,                   /* COMMA  */
    INST_SEP = 372,                /* INST_SEP  */
    REG_B = 373,                   /* REG_B  */
    REG_C = 374,                   /* REG_C  */
    REG_D = 375,                   /* REG_D  */
    REG_E = 376,                   /* REG_E  */
    REG_H = 377,                   /* REG_H  */
    REG_L = 378,                   /* REG_L  */
    REG_AF = 379,                  /* REG_AF  */
    REG_BC = 380,                  /* REG_BC  */
    REG_DE = 381,                  /* REG_DE  */
    REG_HL = 382,                  /* REG_HL  */
    REG_IX = 383,                  /* REG_IX  */
    REG_IY = 384,                  /* REG_IY  */
    REG_SP = 385,                  /* REG_SP  */
    REG_IXH = 386,                 /* REG_IXH  */
    REG_IXL = 387,                 /* REG_IXL  */
    REG_IYH = 388,                 /* REG_IYH  */
    REG_IYL = 389,                 /* REG_IYL  */
    STRING = 390,                  /* STRING  */
    FILENAME = 391,                /* FILENAME  */
    R_O_L = 392,                   /* R_O_L  */
    OPCODE = 393,                  /* OPCODE  */
    LABEL = 394,                   /* LABEL  */
    BANKNAME = 395,                /* BANKNAME  */
    CPUTYPE = 396,                 /* CPUTYPE  */
    MON_REGISTER = 397,            /* MON_REGISTER  */
    COMPARE_OP = 398,              /* COMPARE_OP  */
    RADIX_TYPE = 399,              /* RADIX_TYPE  */
    INPUT_SPEC = 400,              /* INPUT_SPEC  */
    CMD_CHECKPT_ON = 401,          /* CMD_CHECKPT_ON  */
    CMD_CHECKPT_OFF = 402,         /* CMD_CHECKPT_OFF  */
    TOGGLE = 403,                  /* TOGGLE  */
    MASK = 404                     /* MASK  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define H_NUMBER 258
#define D_NUMBER 259
#define O_NUMBER 260
#define B_NUMBER 261
#define CONVERT_OP 262
#define B_DATA 263
#define H_RANGE_GUESS 264
#define D_NUMBER_GUESS 265
#define O_NUMBER_GUESS 266
#define B_NUMBER_GUESS 267
#define BAD_CMD 268
#define MEM_OP 269
#define IF 270
#define MEM_COMP 271
#define MEM_DISK8 272
#define MEM_DISK9 273
#define MEM_DISK10 274
#define MEM_DISK11 275
#define EQUALS 276
#define TRAIL 277
#define CMD_SEP 278
#define LABEL_ASGN_COMMENT 279
#define CMD_SIDEFX 280
#define CMD_RETURN 281
#define CMD_BLOCK_READ 282
#define CMD_BLOCK_WRITE 283
#define CMD_UP 284
#define CMD_DOWN 285
#define CMD_LOAD 286
#define CMD_SAVE 287
#define CMD_VERIFY 288
#define CMD_IGNORE 289
#define CMD_HUNT 290
#define CMD_FILL 291
#define CMD_MOVE 292
#define CMD_GOTO 293
#define CMD_REGISTERS 294
#define CMD_READSPACE 295
#define CMD_WRITESPACE 296
#define CMD_RADIX 297
#define CMD_MEM_DISPLAY 298
#define CMD_BREAK 299
#define CMD_TRACE 300
#define CMD_IO 301
#define CMD_BRMON 302
#define CMD_COMPARE 303
#define CMD_DUMP 304
#define CMD_UNDUMP 305
#define CMD_EXIT 306
#define CMD_DELETE 307
#define CMD_CONDITION 308
#define CMD_COMMAND 309
#define CMD_ASSEMBLE 310
#define CMD_DISASSEMBLE 311
#define CMD_NEXT 312
#define CMD_STEP 313
#define CMD_PRINT 314
#define CMD_DEVICE 315
#define CMD_HELP 316
#define CMD_WATCH 317
#define CMD_DISK 318
#define CMD_SYSTEM 319
#define CMD_QUIT 320
#define CMD_CHDIR 321
#define CMD_BANK 322
#define CMD_LOAD_LABELS 323
#define CMD_SAVE_LABELS 324
#define CMD_ADD_LABEL 325
#define CMD_DEL_LABEL 326
#define CMD_SHOW_LABELS 327
#define CMD_RECORD 328
#define CMD_MON_STOP 329
#define CMD_PLAYBACK 330
#define CMD_CHAR_DISPLAY 331
#define CMD_SPRITE_DISPLAY 332
#define CMD_TEXT_DISPLAY 333
#define CMD_SCREENCODE_DISPLAY 334
#define CMD_ENTER_DATA 335
#define CMD_ENTER_BIN_DATA 336
#define CMD_KEYBUF 337
#define CMD_BLOAD 338
#define CMD_BSAVE 339
#define CMD_SCREEN 340
#define CMD_UNTIL 341
#define CMD_CPU 342
#define CMD_YYDEBUG 343
#define CMD_BACKTRACE 344
#define CMD_SCREENSHOT 345
#define CMD_PWD 346
#define CMD_DIR 347
#define CMD_RESOURCE_GET 348
#define CMD_RESOURCE_SET 349
#define CMD_ATTACH 350
#define CMD_DETACH 351
#define CMD_MON_RESET 352
#define CMD_TAPECTRL 353
#define CMD_CARTFREEZE 354
#define CMD_CPUHISTORY 355
#define CMD_MEMMAPZAP 356
#define CMD_MEMMAPSHOW 357
#define CMD_MEMMAPSAVE 358
#define CMD_COMMENT 359
#define CMD_LIST 360
#define CMD_EXPORT 361
#define CMD_AUTOSTART 362
#define CMD_AUTOLOAD 363
#define CMD_LABEL_ASGN 364
#define L_PAREN 365
#define R_PAREN 366
#define ARG_IMMEDIATE 367
#define REG_A 368
#define REG_X 369
#define REG_Y 370
#define COMMA 371
#define INST_SEP 372
#define REG_B 373
#define REG_C 374
#define REG_D 375
#define REG_E 376
#define REG_H 377
#define REG_L 378
#define REG_AF 379
#define REG_BC 380
#define REG_DE 381
#define REG_HL 382
#define REG_IX 383
#define REG_IY 384
#define REG_SP 385
#define REG_IXH 386
#define REG_IXL 387
#define REG_IYH 388
#define REG_IYL 389
#define STRING 390
#define FILENAME 391
#define R_O_L 392
#define OPCODE 393
#define LABEL 394
#define BANKNAME 395
#define CPUTYPE 396
#define MON_REGISTER 397
#define COMPARE_OP 398
#define RADIX_TYPE 399
#define INPUT_SPEC 400
#define CMD_CHECKPT_ON 401
#define CMD_CHECKPT_OFF 402
#define TOGGLE 403
#define MASK 404

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 127 "mon_parse.y"

    MON_ADDR a;
    MON_ADDR range[2];
    int i;
    REG_ID reg;
    CONDITIONAL cond_op;
    cond_node_t *cond_node;
    RADIXTYPE rt;
    ACTION action;
    char *str;

#line 560 "mon_parse.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_MON_PARSE_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_H_NUMBER = 3,                   /* H_NUMBER  */
  YYSYMBOL_D_NUMBER = 4,                   /* D_NUMBER  */
  YYSYMBOL_O_NUMBER = 5,                   /* O_NUMBER  */
  YYSYMBOL_B_NUMBER = 6,                   /* B_NUMBER  */
  YYSYMBOL_CONVERT_OP = 7,                 /* CONVERT_OP  */
  YYSYMBOL_B_DATA = 8,                     /* B_DATA  */
  YYSYMBOL_H_RANGE_GUESS = 9,              /* H_RANGE_GUESS  */
  YYSYMBOL_D_NUMBER_GUESS = 10,            /* D_NUMBER_GUESS  */
  YYSYMBOL_O_NUMBER_GUESS = 11,            /* O_NUMBER_GUESS  */
  YYSYMBOL_B_NUMBER_GUESS = 12,            /* B_NUMBER_GUESS  */
  YYSYMBOL_BAD_CMD = 13,                   /* BAD_CMD  */
  YYSYMBOL_MEM_OP = 14,                    /* MEM_OP  */
  YYSYMBOL_IF = 15,                        /* IF  */
  YYSYMBOL_MEM_COMP = 16,                  /* MEM_COMP  */
  YYSYMBOL_MEM_DISK8 = 17,                 /* MEM_DISK8  */
  YYSYMBOL_MEM_DISK9 = 18,                 /* MEM_DISK9  */
  YYSYMBOL_MEM_DISK10 = 19,                /* MEM_DISK10  */
  YYSYMBOL_MEM_DISK11 = 20,                /* MEM_DISK11  */
  YYSYMBOL_EQUALS = 21,                    /* EQUALS  */
  YYSYMBOL_TRAIL = 22,                     /* TRAIL  */
  YYSYMBOL_CMD_SEP = 23,                   /* CMD_SEP  */
  YYSYMBOL_LABEL_ASGN_COMMENT = 24,        /* LABEL_ASGN_COMMENT  */
  YYSYMBOL_CMD_SIDEFX = 25,                /* CMD_SIDEFX  */
  YYSYMBOL_CMD_RETURN = 26,                /* CMD_RETURN  */
  YYSYMBOL_CMD_BLOCK_READ = 27,            /* CMD_BLOCK_READ  */
  YYSYMBOL_CMD_BLOCK_WRITE = 28,           /* CMD_BLOCK_WRITE  */
  YYSYMBOL_CMD_UP = 29,                    /* CMD_UP  */
  YYSYMBOL_CMD_DOWN = 30,                  /* CMD_DOWN  */
  YYSYMBOL_CMD_LOAD = 31,                  /* CMD_LOAD  */
  YYSYMBOL_CMD_SAVE = 32,                  /* CMD_SAVE  */
  YYSYMBOL_CMD_VERIFY = 33,                /* CMD_VERIFY  */
  YYSYMBOL_CMD_IGNORE = 34,                /* CMD_IGNORE  */
  YYSYMBOL_CMD_HUNT = 35,                  /* CMD_HUNT  */
  YYSYMBOL_CMD_FILL = 36,                  /* CMD_FILL  */
  YYSYMBOL_CMD_MOVE = 37,                  /* CMD_MOVE  */
  YYSYMBOL_CMD_GOTO = 38,                  /* CMD_GOTO  */
  YYSYMBOL_CMD_REGISTERS = 39,             /* CMD_REGISTERS  */
  YYSYMBOL_CMD_READSPACE = 40,             /* CMD_READSPACE  */
  YYSYMBOL_CMD_WRITESPACE = 41,            /* CMD_WRITESPACE  */
  YYSYMBOL_CMD_RADIX = 42,                 /* CMD_RADIX  */
  YYSYMBOL_CMD_MEM_DISPLAY = 43,           /* CMD_MEM_DISPLAY  */
  YYSYMBOL_CMD_BREAK = 44,                 /* CMD_BREAK  */
  YYSYMBOL_CMD_TRACE = 45,                 /* CMD_TRACE  */
  YYSYMBOL_CMD_IO = 46,                    /* CMD_IO  */
  YYSYMBOL_CMD_BRMON = 47,                 /* CMD_BRMON  */
  YYSYMBOL_CMD_COMPARE = 48,               /* CMD_COMPARE  */
  YYSYMBOL_CMD_DUMP = 49,                  /* CMD_DUMP  */
  YYSYMBOL_CMD_UNDUMP = 50,                /* CMD_UNDUMP  */
  YYSYMBOL_CMD_EXIT = 51,                  /* CMD_EXIT  */
  YYSYMBOL_CMD_DELETE = 52,                /* CMD_DELETE  */
  YYSYMBOL_CMD_CONDITION = 53,             /* CMD_CONDITION  */
  YYSYMBOL_CMD_COMMAND = 54,               /* CMD_COMMAND  */
  YYSYMBOL_CMD_ASSEMBLE = 55,              /* CMD_ASSEMBLE  */
  YYSYMBOL_CMD_DISASSEMBLE = 56,           /* CMD_DISASSEMBLE  */
  YYSYMBOL_CMD_NEXT = 57,                  /* CMD_NEXT  */
  YYSYMBOL_CMD_STEP = 58,                  /* CMD_STEP  */
  YYSYMBOL_CMD_PRINT = 59,                 /* CMD_PRINT  */
  YYSYMBOL_CMD_DEVICE = 60,                /* CMD_DEVICE  */
  YYSYMBOL_CMD_HELP = 61,                  /* CMD_HELP  */
  YYSYMBOL_CMD_WATCH = 62,                 /* CMD_WATCH  */
  YYSYMBOL_CMD_DISK = 63,                  /* CMD_DISK  */
  YYSYMBOL_CMD_SYSTEM = 64,                /* CMD_SYSTEM  */
  YYSYMBOL_CMD_QUIT = 65,                  /* CMD_QUIT  */
  YYSYMBOL_CMD_CHDIR = 66,                 /* CMD_CHDIR  */
  YYSYMBOL_CMD_BANK = 67,                  /* CMD_BANK  */
  YYSYMBOL_CMD_LOAD_LABELS = 68,           /* CMD_LOAD_LABELS  */
  YYSYMBOL_CMD_SAVE_LABELS = 69,           /* CMD_SAVE_LABELS  */
  YYSYMBOL_CMD_ADD_LABEL = 70,             /* CMD_ADD_LABEL  */
  YYSYMBOL_CMD_DEL_LABEL = 71,             /* CMD_DEL_LABEL  */
  YYSYMBOL_CMD_SHOW_LABELS = 72,           /* CMD_SHOW_LABELS  */
  YYSYMBOL_CMD_RECORD = 73,                /* CMD_RECORD  */
  YYSYMBOL_CMD_MON_STOP = 74,              /* CMD_MON_STOP  */
  YYSYMBOL_CMD_PLAYBACK = 75,              /* CMD_PLAYBACK  */
  YYSYMBOL_CMD_CHAR_DISPLAY = 76,          /* CMD_CHAR_DISPLAY  */
  YYSYMBOL_CMD_SPRITE_DISPLAY = 77,        /* CMD_SPRITE_DISPLAY  */
  YYSYMBOL_CMD_TEXT_DISPLAY = 78,          /* CMD_TEXT_DISPLAY  */
  YYSYMBOL_CMD_SCREENCODE_DISPLAY = 79,    /* CMD_SCREENCODE_DISPLAY  */
  YYSYMBOL_CMD_ENTER_DATA = 80,            /* CMD_ENTER_DATA  */
  YYSYMBOL_CMD_ENTER_BIN_DATA = 81,        /* CMD_ENTER_BIN_DATA  */
  YYSYMBOL_CMD_KEYBUF = 82,                /* CMD_KEYBUF  */
  YYSYMBOL_CMD_BLOAD = 83,                 /* CMD_BLOAD  */
  YYSYMBOL_CMD_BSAVE = 84,                 /* CMD_BSAVE  */
  YYSYMBOL_CMD_SCREEN = 85,                /* CMD_SCREEN  */
  YYSYMBOL_CMD_UNTIL = 86,                 /* CMD_UNTIL  */
  YYSYMBOL_CMD_CPU = 87,                   /* CMD_CPU  */
  YYSYMBOL_CMD_YYDEBUG = 88,               /* CMD_YYDEBUG  */
  YYSYMBOL_CMD_BACKTRACE = 89,             /* CMD_BACKTRACE  */
  YYSYMBOL_CMD_SCREENSHOT = 90,            /* CMD_SCREENSHOT  */
  YYSYMBOL_CMD_PWD = 91,                   /* CMD_PWD  */
  YYSYMBOL_CMD_DIR = 92,                   /* CMD_DIR  */
  YYSYMBOL_CMD_RESOURCE_GET = 93,          /* CMD_RESOURCE_GET  */
  YYSYMBOL_CMD_RESOURCE_SET = 94,          /* CMD_RESOURCE_SET  */
  YYSYMBOL_CMD_ATTACH = 95,                /* CMD_ATTACH  */
  YYSYMBOL_CMD_DETACH = 96,                /* CMD_DETACH  */
  YYSYMBOL_CMD_MON_RESET = 97,             /* CMD_MON_RESET  */
  YYSYMBOL_CMD_TAPECTRL = 98,              /* CMD_TAPECTRL  */
  YYSYMBOL_CMD_CARTFREEZE = 99,            /* CMD_CARTFREEZE  */
  YYSYMBOL_CMD_CPUHISTORY = 100,           /* CMD_CPUHISTORY  */
  YYSYMBOL_CMD_MEMMAPZAP = 101,            /* CMD_MEMMAPZAP  */
  YYSYMBOL_CMD_MEMMAPSHOW = 102,           /* CMD_MEMMAPSHOW  */
  YYSYMBOL_CMD_MEMMAPSAVE = 103,           /* CMD_MEMMAPSAVE  */
  YYSYMBOL_CMD_COMMENT = 104,              /* CMD_COMMENT  */
  YYSYMBOL_CMD_LIST = 105,                 /* CMD_LIST  */
  YYSYMBOL_CMD_EXPORT = 106,               /* CMD_EXPORT  */
  YYSYMBOL_CMD_AUTOSTART = 107,            /* CMD_AUTOSTART  */
  YYSYMBOL_CMD_AUTOLOAD = 108,             /* CMD_AUTOLOAD  */
  YYSYMBOL_CMD_LABEL_ASGN = 109,           /* CMD_LABEL_ASGN  */
  YYSYMBOL_L_PAREN = 110,                  /* L_PAREN  */
  YYSYMBOL_R_PAREN = 111,                  /* R_PAREN  */
  YYSYMBOL_ARG_IMMEDIATE = 112,            /* ARG_IMMEDIATE  */
  YYSYMBOL_REG_A = 113,                    /* REG_A  */
  YYSYMBOL_REG_X = 114,                    /* REG_X  */
  YYSYMBOL_REG_Y = 115,                    /* REG_Y  */
  YYSYMBOL_COMMA = 116,                    /* COMMA  */
  YYSYMBOL_INST_SEP = 117,                 /* INST_SEP  */
  YYSYMBOL_REG_B = 118,                    /* REG_B  */
  YYSYMBOL_REG_C = 119,                    /* REG_C  */
  YYSYMBOL_REG_D = 120,                    /* REG_D  */
  YYSYMBOL_REG_E = 121,                    /* REG_E  */
  YYSYMBOL_REG_H = 122,                    /* REG_H  */
  YYSYMBOL_REG_L = 123,                    /* REG_L  */
  YYSYMBOL_REG_AF = 124,                   /* REG_AF  */
  YYSYMBOL_REG_BC = 125,                   /* REG_BC  */
  YYSYMBOL_REG_DE = 126,                   /* REG_DE  */
  YYSYMBOL_REG_HL = 127,                   /* REG_HL  */
  YYSYMBOL_REG_IX = 128,                   /* REG_IX  */
  YYSYMBOL_REG_IY = 129,                   /* REG_IY  */
  YYSYMBOL_REG_SP = 130,                   /* REG_SP  */
  YYSYMBOL_REG_IXH = 131,                  /* REG_IXH  */
  YYSYMBOL_REG_IXL = 132,                  /* REG_IXL  */
  YYSYMBOL_REG_IYH = 133,                  /* REG_IYH  */
  YYSYMBOL_REG_IYL = 134,                  /* REG_IYL  */
  YYSYMBOL_STRING = 135,                   /* STRING  */
  YYSYMBOL_FILENAME = 136,                 /* FILENAME  */
  YYSYMBOL_R_O_L = 137,                    /* R_O_L  */
  YYSYMBOL_OPCODE = 138,                   /* OPCODE  */
  YYSYMBOL_LABEL = 139,                    /* LABEL  */
  YYSYMBOL_BANKNAME = 140,                 /* BANKNAME  */
  YYSYMBOL_CPUTYPE = 141,                  /* CPUTYPE  */
  YYSYMBOL_MON_REGISTER = 142,             /* MON_REGISTER  */
  YYSYMBOL_COMPARE_OP = 143,               /* COMPARE_OP  */
  YYSYMBOL_RADIX_TYPE = 144,               /* RADIX_TYPE  */
  YYSYMBOL_INPUT_SPEC = 145,               /* INPUT_SPEC  */
  YYSYMBOL_CMD_CHECKPT_ON = 146,           /* CMD_CHECKPT_ON  */
  YYSYMBOL_CMD_CHECKPT_OFF = 147,          /* CMD_CHECKPT_OFF  */
  YYSYMBOL_TOGGLE = 148,                   /* TOGGLE  */
  YYSYMBOL_MASK = 149,                     /* MASK  */
  YYSYMBOL_150_ = 150,                     /* '+'  */
  YYSYMBOL_151_ = 151,                     /* '-'  */
  YYSYMBOL_152_ = 152,                     /* '*'  */
  YYSYMBOL_153_ = 153,                     /* '/'  */
  YYSYMBOL_154_ = 154,                     /* '('  */
  YYSYMBOL_155_ = 155,                     /* ')'  */
  YYSYMBOL_YYACCEPT = 156,                 /* $accept  */
  YYSYMBOL_top_level = 157,                /* top_level  */
  YYSYMBOL_command_list = 158,             /* command_list  */
  YYSYMBOL_end_cmd = 159,                  /* end_cmd  */
  YYSYMBOL_command = 160,                  /* command  */
  YYSYMBOL_machine_state_rules = 161,      /* machine_state_rules  */
  YYSYMBOL_register_mod = 162,             /* register_mod  */
  YYSYMBOL_symbol_table_rules = 163,       /* symbol_table_rules  */
  YYSYMBOL_asm_rules = 164,                /* asm_rules  */
  YYSYMBOL_165_1 = 165,                    /* $@1  */
  YYSYMBOL_memory_rules = 166,             /* memory_rules  */
  YYSYMBOL_checkpoint_rules = 167,         /* checkpoint_rules  */
  YYSYMBOL_checkpoint_control_rules = 168, /* checkpoint_control_rules  */
  YYSYMBOL_monitor_state_rules = 169,      /* monitor_state_rules  */
  YYSYMBOL_monitor_misc_rules = 170,       /* monitor_misc_rules  */
  YYSYMBOL_disk_rules = 171,               /* disk_rules  */
  YYSYMBOL_cmd_file_rules = 172,           /* cmd_file_rules  */
  YYSYMBOL_data_entry_rules = 173,         /* data_entry_rules  */
  YYSYMBOL_monitor_debug_rules = 174,      /* monitor_debug_rules  */
  YYSYMBOL_rest_of_line = 175,             /* rest_of_line  */
  YYSYMBOL_opt_rest_of_line = 176,         /* opt_rest_of_line  */
  YYSYMBOL_filename = 177,                 /* filename  */
  YYSYMBOL_device_num = 178,               /* device_num  */
  YYSYMBOL_opt_mem_op = 179,               /* opt_mem_op  */
  YYSYMBOL_register = 180,                 /* register  */
  YYSYMBOL_reg_list = 181,                 /* reg_list  */
  YYSYMBOL_reg_asgn = 182,                 /* reg_asgn  */
  YYSYMBOL_checkpt_num = 183,              /* checkpt_num  */
  YYSYMBOL_address_opt_range = 184,        /* address_opt_range  */
  YYSYMBOL_address_range = 185,            /* address_range  */
  YYSYMBOL_opt_address = 186,              /* opt_address  */
  YYSYMBOL_address = 187,                  /* address  */
  YYSYMBOL_opt_sep = 188,                  /* opt_sep  */
  YYSYMBOL_memspace = 189,                 /* memspace  */
  YYSYMBOL_memloc = 190,                   /* memloc  */
  YYSYMBOL_memaddr = 191,                  /* memaddr  */
  YYSYMBOL_expression = 192,               /* expression  */
  YYSYMBOL_cond_expr = 193,                /* cond_expr  */
  YYSYMBOL_compare_operand = 194,          /* compare_operand  */
  YYSYMBOL_data_list = 195,                /* data_list  */
  YYSYMBOL_data_element = 196,             /* data_element  */
  YYSYMBOL_hunt_list = 197,                /* hunt_list  */
  YYSYMBOL_hunt_element = 198,             /* hunt_element  */
  YYSYMBOL_value = 199,                    /* value  */
  YYSYMBOL_d_number = 200,                 /* d_number  */
  YYSYMBOL_guess_default = 201,            /* guess_default  */
  YYSYMBOL_number = 202,                   /* number  */
  YYSYMBOL_assembly_instr_list = 203,      /* assembly_instr_list  */
  YYSYMBOL_assembly_instruction = 204,     /* assembly_instruction  */
  YYSYMBOL_post_assemble = 205,            /* post_assemble  */
  YYSYMBOL_asm_operand_mode = 206          /* asm_operand_mode  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  298
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1729

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  156
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  278
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  560

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   404


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     154,   155,   152,   150,     2,   151,     2,   153,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   186,   186,   187,   188,   191,   192,   195,   196,   197,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   215,   217,   219,   221,   223,   225,   227,
     229,   231,   233,   235,   237,   239,   241,   243,   245,   247,
     249,   251,   253,   255,   257,   259,   261,   264,   266,   268,
     271,   276,   281,   283,   285,   287,   289,   291,   293,   295,
     299,   306,   305,   308,   310,   312,   316,   318,   320,   322,
     324,   326,   328,   330,   332,   334,   336,   338,   340,   342,
     344,   346,   348,   350,   352,   354,   358,   362,   367,   371,
     376,   379,   383,   388,   392,   397,   400,   404,   409,   413,
     418,   421,   425,   430,   432,   434,   436,   438,   440,   442,
     444,   446,   450,   452,   457,   459,   477,   479,   481,   483,
     487,   489,   491,   493,   495,   497,   499,   501,   503,   505,
     507,   509,   511,   513,   515,   517,   519,   521,   523,   525,
     529,   531,   533,   535,   537,   539,   541,   543,   545,   547,
     549,   551,   553,   555,   557,   559,   561,   563,   565,   569,
     571,   573,   577,   579,   583,   587,   590,   591,   594,   595,
     598,   599,   602,   603,   606,   607,   610,   611,   614,   618,
     619,   622,   623,   626,   627,   629,   633,   634,   637,   642,
     647,   657,   658,   661,   662,   663,   664,   665,   668,   670,
     672,   673,   674,   675,   676,   677,   678,   681,   686,   688,
     690,   692,   696,   702,   710,   711,   714,   715,   718,   719,
     722,   723,   724,   727,   728,   731,   732,   733,   734,   737,
     738,   739,   742,   743,   744,   745,   746,   749,   750,   751,
     754,   764,   765,   768,   772,   777,   782,   787,   789,   791,
     793,   794,   795,   796,   797,   798,   799,   801,   803,   805,
     807,   808,   809,   810,   811,   812,   813,   814,   815,   816,
     817,   818,   819,   820,   821,   822,   823,   824,   825
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "H_NUMBER", "D_NUMBER",
  "O_NUMBER", "B_NUMBER", "CONVERT_OP", "B_DATA", "H_RANGE_GUESS",
  "D_NUMBER_GUESS", "O_NUMBER_GUESS", "B_NUMBER_GUESS", "BAD_CMD",
  "MEM_OP", "IF", "MEM_COMP", "MEM_DISK8", "MEM_DISK9", "MEM_DISK10",
  "MEM_DISK11", "EQUALS", "TRAIL", "CMD_SEP", "LABEL_ASGN_COMMENT",
  "CMD_SIDEFX", "CMD_RETURN", "CMD_BLOCK_READ", "CMD_BLOCK_WRITE",
  "CMD_UP", "CMD_DOWN", "CMD_LOAD", "CMD_SAVE", "CMD_VERIFY", "CMD_IGNORE",
  "CMD_HUNT", "CMD_FILL", "CMD_MOVE", "CMD_GOTO", "CMD_REGISTERS",
  "CMD_READSPACE", "CMD_WRITESPACE", "CMD_RADIX", "CMD_MEM_DISPLAY",
  "CMD_BREAK", "CMD_TRACE", "CMD_IO", "CMD_BRMON", "CMD_COMPARE",
  "CMD_DUMP", "CMD_UNDUMP", "CMD_EXIT", "CMD_DELETE", "CMD_CONDITION",
  "CMD_COMMAND", "CMD_ASSEMBLE", "CMD_DISASSEMBLE", "CMD_NEXT", "CMD_STEP",
  "CMD_PRINT", "CMD_DEVICE", "CMD_HELP", "CMD_WATCH", "CMD_DISK",
  "CMD_SYSTEM", "CMD_QUIT", "CMD_CHDIR", "CMD_BANK", "CMD_LOAD_LABELS",
  "CMD_SAVE_LABELS", "CMD_ADD_LABEL", "CMD_DEL_LABEL", "CMD_SHOW_LABELS",
  "CMD_RECORD", "CMD_MON_STOP", "CMD_PLAYBACK", "CMD_CHAR_DISPLAY",
  "CMD_SPRITE_DISPLAY", "CMD_TEXT_DISPLAY", "CMD_SCREENCODE_DISPLAY",
  "CMD_ENTER_DATA", "CMD_ENTER_BIN_DATA", "CMD_KEYBUF", "CMD_BLOAD",
  "CMD_BSAVE", "CMD_SCREEN", "CMD_UNTIL", "CMD_CPU", "CMD_YYDEBUG",
  "CMD_BACKTRACE", "CMD_SCREENSHOT", "CMD_PWD", "CMD_DIR",
  "CMD_RESOURCE_GET", "CMD_RESOURCE_SET", "CMD_ATTACH", "CMD_DETACH",
  "CMD_MON_RESET", "CMD_TAPECTRL", "CMD_CARTFREEZE", "CMD_CPUHISTORY",
  "CMD_MEMMAPZAP", "CMD_MEMMAPSHOW", "CMD_MEMMAPSAVE", "CMD_COMMENT",
  "CMD_LIST", "CMD_EXPORT", "CMD_AUTOSTART", "CMD_AUTOLOAD",
  "CMD_LABEL_ASGN", "L_PAREN", "R_PAREN", "ARG_IMMEDIATE", "REG_A",
  "REG_X", "REG_Y", "COMMA", "INST_SEP", "REG_B", "REG_C", "REG_D",
  "REG_E", "REG_H", "REG_L", "REG_AF", "REG_BC", "REG_DE", "REG_HL",
  "REG_IX", "REG_IY", "REG_SP", "REG_IXH", "REG_IXL", "REG_IYH", "REG_IYL",
  "STRING", "FILENAME", "R_O_L", "OPCODE", "LABEL", "BANKNAME", "CPUTYPE",
  "MON_REGISTER", "COMPARE_OP", "RADIX_TYPE", "INPUT_SPEC",
  "CMD_CHECKPT_ON", "CMD_CHECKPT_OFF", "TOGGLE", "MASK", "'+'", "'-'",
  "'*'", "'/'", "'('", "')'", "$accept", "top_level", "command_list",
  "end_cmd", "command", "machine_state_rules", "register_mod",
  "symbol_table_rules", "asm_rules", "$@1", "memory_rules",
  "checkpoint_rules", "checkpoint_control_rules", "monitor_state_rules",
  "monitor_misc_rules", "disk_rules", "cmd_file_rules", "data_entry_rules",
  "monitor_debug_rules", "rest_of_line", "opt_rest_of_line", "filename",
  "device_num", "opt_mem_op", "register", "reg_list", "reg_asgn",
  "checkpt_num", "address_opt_range", "address_range", "opt_address",
  "address", "opt_sep", "memspace", "memloc", "memaddr", "expression",
  "cond_expr", "compare_operand", "data_list", "data_element", "hunt_list",
  "hunt_element", "value", "d_number", "guess_default", "number",
  "assembly_instr_list", "assembly_instruction", "post_assemble",
  "asm_operand_mode", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-343)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-193)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1173,   884,  -343,  -343,    43,   297,   884,   884,   354,   354,
       1,     1,     1,   118,   925,   925,   925,  1572,   256,    87,
    1024,  1435,  1435,  1481,   925,     1,     1,   297,   973,   118,
     118,  1572,  1458,   354,   354,   884,   691,   212,  1435,  -128,
    -128,   297,  -128,   394,   475,   475,  1572,   560,   642,     1,
     297,     1,  1458,  1458,  1458,  1458,  1572,   297,  -104,     1,
       1,   297,  1458,   113,   297,   297,     1,   297,  -103,   -98,
     -96,     1,   884,   354,   -70,   297,   354,   297,   354,     1,
    -103,   629,   297,     1,     1,    32,  1595,   118,   118,    61,
    1296,  -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,
    -343,  -343,  -343,  -343,  -343,    41,  -343,  -343,  -343,  -343,
    -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,   884,
    -343,   -78,   131,  -343,  -343,  -343,  -343,  -343,  -343,   297,
    -343,  -343,   836,   836,  -343,  -343,   884,  -343,   884,  -343,
    -343,   717,   818,   717,  -343,  -343,  -343,  -343,  -343,   354,
    -343,  -343,  -343,   -70,   -70,   -70,  -343,  -343,  -343,   -70,
     -70,   297,   -70,  -343,    46,   221,  -343,    98,   297,  -343,
     -70,  -343,   297,  -343,   178,  -343,  -343,   925,   421,  -343,
     925,   426,  -343,   297,   -70,   297,   297,  -343,   339,  -343,
     297,    54,     7,   225,  -343,   297,  -343,   884,  -343,   884,
     131,   297,  -343,  -343,   297,  -343,   925,   489,   297,   297,
    -343,   297,   297,  -343,   164,   297,   -70,   297,   -70,   -70,
     297,   -70,  -343,   297,   297,  -343,   297,  -343,   297,  -343,
     297,  -343,   297,  -343,   297,   904,  -343,   297,   717,   717,
    -343,  -343,   297,   297,  -343,  -343,  -343,   354,  -343,  -343,
     297,   297,   -55,   884,   131,  -343,   884,   884,  -343,  -343,
     884,  -343,  -343,   884,   -70,   297,   381,  -343,   297,   158,
    -343,   958,   958,  1572,  1047,  1106,  -343,  -343,  -343,  -343,
    -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,
    -343,  -343,  -343,  -343,   -26,  -343,   297,   297,  -343,  -343,
    -343,   100,  -343,   884,   884,   884,   884,  -343,  -343,    18,
     988,   131,   131,  -343,   304,  1288,  1505,  1550,  -343,   884,
     311,  1572,  1096,   904,  1572,  -343,  1106,  1106,   461,  -343,
    -343,  -343,   925,  -343,   514,  1403,  -343,   655,  1403,  -343,
    -343,  1572,  -343,  -343,  -343,  1403,   297,   -51,  -343,   -38,
    -343,   131,   131,  -343,  -343,  -343,   681,  1403,  -343,  -343,
    -343,  -343,  -343,  -343,   -27,  -343,     1,  -343,     1,   -37,
    -343,   -14,  -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,
     614,  -343,  -343,  -343,   304,  1530,  -343,  -343,  -343,   884,
    -343,  -343,   297,   131,  -343,   131,   131,   131,   863,   884,
    -343,  -343,  -343,  1106,  -343,  1106,   330,    20,    28,    30,
      37,    38,    44,  -110,  -343,   -89,  -343,  -343,  -343,  -343,
      22,    22,  -343,  -343,   297,  1572,   297,  -343,  -343,   297,
    -343,   297,  -343,   297,   131,  -343,  -343,   549,  -343,  -343,
    -343,  -343,  -343,   614,   297,  -343,  -343,   297,  1403,  -343,
    1403,  -343,    81,  -343,  -343,  1403,  -343,    81,   297,    81,
    -343,   297,    26,    49,   297,  -343,  -343,  1403,  -343,    81,
     297,   297,   297,   297,   297,  -343,   904,   297,  -343,   297,
     131,  -343,  -343,  -343,  -343,  -343,  -343,   297,   131,   297,
     297,   297,  -343,  -343,  -343,  -343,  -343,  -343,  -343,    45,
      63,  -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,
    -343,  -343,  -343,  -343,  -343,    81,    29,  1078,  -343,    81,
    -343,  -343,  -343,  -343,   -38,   -38,  -343,    81,  -343,  -343,
    -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,
    -343,  -343,  -343,   -32,    73,  -343,  -343,  -343,  -343,  -343,
    -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,     0,    22,     4,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   167,     0,
       0,     0,     0,     0,   192,     0,     0,     0,     0,     0,
     167,     0,     0,     0,     0,     0,   260,     0,     0,     0,
       2,     5,    10,    46,    11,    13,    12,    14,    15,    16,
      17,    18,    19,    20,    21,     0,   232,   233,   234,   235,
     231,   230,   229,   193,   194,   195,   196,   197,   174,     0,
     224,     0,     0,   206,   236,   223,     9,     8,     7,     0,
     113,    34,     0,     0,   191,    41,     0,    43,     0,   169,
     168,     0,     0,     0,   180,   225,   228,   227,   226,     0,
     179,   184,   190,   192,   192,   192,   188,   198,   199,   192,
     192,     0,   192,    47,     0,     0,   177,     0,     0,   115,
     192,    72,     0,   181,   192,   172,    90,     0,     0,   100,
       0,     0,    28,     0,   192,     0,     0,   119,     9,   108,
       0,     0,     0,     0,    65,     0,    39,     0,    37,     0,
       0,     0,   165,   122,     0,    95,     0,     0,     0,     0,
     118,     0,     0,    23,     0,     0,   192,     0,   192,   192,
       0,   192,    58,     0,     0,   160,     0,    74,     0,    76,
       0,    78,     0,    80,     0,     0,   163,     0,     0,     0,
      45,   102,     0,     0,    30,   164,   128,     0,   130,   166,
       0,     0,     0,     0,     0,   135,     0,     0,   138,    32,
       0,    81,    82,     0,   192,     0,     9,   151,     0,   170,
     117,     0,     0,     0,     0,     0,   261,   262,   263,   264,
     265,   266,   269,   272,   273,   274,   275,   276,   277,   278,
     267,   270,   268,   271,   244,   240,     0,     0,     1,     6,
       3,     0,   175,     0,     0,     0,     0,   125,   112,   192,
       0,     0,     0,   171,   192,   143,     0,     0,   105,     0,
       0,     0,     0,     0,     0,    27,     0,     0,     0,    49,
      48,   114,     0,    71,     0,     0,    86,     0,     0,    96,
      29,     0,    35,    36,   107,     0,     0,     0,    63,     0,
      64,     0,     0,   121,   116,   123,     0,     0,    91,   120,
     124,   126,    25,    24,     0,    51,     0,    53,     0,     0,
      55,     0,    57,   159,   161,    73,    75,    77,    79,   217,
       0,   215,   216,   127,   192,     0,   101,    31,   131,     0,
     129,   133,     0,     0,   154,     0,     0,     0,     0,     0,
     139,   152,   155,     0,   157,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   243,     0,   103,   104,   205,   204,
     200,   201,   202,   203,     0,     0,     0,    42,    44,     0,
     144,     0,   148,     0,     0,   222,   221,     0,   219,   220,
     183,   185,   189,     0,     0,   178,   176,     0,     0,    88,
       0,   212,     0,   211,   213,     0,    98,     0,     0,     0,
     111,     0,   242,   241,     0,    40,    38,     0,    93,     0,
       0,     0,     0,     0,     0,   162,     0,     0,   146,     0,
       0,   134,   153,   136,   137,    33,    83,     0,     0,     0,
       0,     0,    59,   250,   251,   252,   253,   254,   255,   247,
       0,   245,   246,   149,   186,   150,   140,   142,   147,   106,
      69,   218,    68,    66,    70,     0,     0,     0,    87,     0,
      97,    67,   109,   110,     0,   239,    62,     0,    92,    26,
      50,    52,    54,    56,   214,   141,   145,   132,    84,    85,
     156,   158,    60,     0,     0,    89,   210,   209,   208,   207,
      99,   237,   238,    94,   256,   249,   257,   258,   259,   248
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -343,  -343,  -343,    -5,    99,  -343,  -343,  -343,  -343,  -343,
    -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,    47,
     112,    67,   192,   -17,    80,  -343,  -134,   129,    53,    -4,
    -290,   272,   532,   746,  -271,  -343,   557,  -303,  -343,  -126,
    -278,  -343,  -232,  -343,  -343,  -343,   264,  -343,  -342,  -343,
    -343
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    89,    90,   130,    91,    92,    93,    94,    95,   349,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   204,
     250,   141,   268,   177,   120,   165,   166,   149,   172,   173,
     424,   174,   425,   121,   156,   157,   269,   452,   453,   380,
     381,   437,   438,   123,   150,   124,   158,   462,   105,   464,
     295
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     131,   499,   139,   135,   137,   180,   500,   463,   346,   202,
     153,   159,   160,   163,   169,   171,   176,   179,   182,  -187,
     184,   206,   187,   189,   429,   501,   502,   194,   196,   198,
     546,   237,   203,   205,   249,   457,   210,   251,   213,   252,
    -187,  -187,   459,   222,   126,   225,   134,   227,   229,   231,
     233,   442,   236,   273,   469,   442,   240,   241,   244,   245,
     246,   298,   248,   300,   302,   127,   128,   327,   255,   345,
     258,   259,   261,   262,   178,   181,   267,   270,   142,   143,
     392,   554,   126,   555,   461,   195,   208,   209,   126,   211,
     415,   207,   185,   186,   477,   556,   557,   558,   164,   126,
      86,   418,   473,   127,   128,   228,   230,   232,   234,   127,
     128,   215,   217,   470,   126,   242,   224,   307,   226,   144,
     127,   128,   145,   134,   308,   474,   238,   239,   146,   147,
     148,   493,   126,   247,   134,   127,   128,   140,   253,   494,
     547,   495,  -192,   524,   318,   515,   264,   516,   496,   497,
     271,   272,   519,   127,   128,   498,   325,   190,   191,   192,
     329,   543,   330,   331,   527,   126,   525,   333,   303,   304,
     305,   306,   517,   336,   305,   306,   339,   544,   340,  -182,
     342,   343,   551,   552,   559,   344,   127,   128,   348,   299,
     350,   129,   265,  -182,   446,   353,   354,   443,   534,   355,
    -182,  -182,   358,   359,   360,   511,   361,   362,     0,   363,
     365,     0,   367,   126,   549,   370,   296,   297,   372,   373,
       0,   374,   126,   375,   517,   376,   126,   377,     0,   378,
     334,   168,   383,   337,   127,   128,     0,   386,   387,     0,
     302,     0,   388,   127,   128,   390,   391,   127,   128,   394,
     303,   304,   305,   306,   243,   419,     0,   126,     0,   356,
     400,     0,     0,   401,     0,   125,   402,   404,     0,     0,
     125,   125,   113,   114,   115,   116,   117,     0,   127,   128,
     134,   303,   304,   305,   306,     0,   154,   154,   154,   161,
       0,   416,   417,     0,   134,   183,   154,     0,   126,   125,
       0,     0,     0,   193,  -192,  -187,   427,   428,   303,   304,
     305,   306,   431,     0,   106,   107,   108,   109,   219,   127,
     128,   110,   111,   112,     0,     0,  -187,  -187,   235,   449,
       0,   126,   456,   314,   316,   317,   125,   328,     0,     0,
    -180,   460,     0,     0,     0,   125,   465,   466,     0,   202,
     294,   468,   127,   128,   491,   126,     0,  -192,  -192,  -192,
    -192,  -180,  -180,   -61,  -192,  -192,  -192,     0,     0,     0,
    -192,  -192,  -192,  -192,  -192,   475,   127,   128,     0,     0,
       0,   479,  -171,   125,     0,   447,     0,   481,   482,     0,
     483,   484,   485,   486,     0,   126,   125,   125,   118,     0,
     125,   492,   125,  -171,  -171,   125,   125,   125,   164,     0,
     113,   114,   115,   116,   117,   451,   127,   128,   451,   503,
     134,   505,   126,     0,   506,   451,   507,   126,   508,   509,
     384,   385,   510,   471,     0,   472,   335,   451,   512,   513,
       0,   338,   514,   127,   128,     0,   435,   518,   127,   128,
       0,   487,   520,   521,   522,     0,   523,     0,     0,   526,
     436,   125,     0,   125,   528,   529,   530,   531,   532,   533,
     134,     0,   535,     0,   536,   537,   139,   113,   114,   115,
     116,   117,   538,   539,   540,   541,   542,     0,     0,     0,
     126,   113,   114,   115,   116,   117,  -192,     0,     0,   382,
       0,     0,   125,   125,   357,     0,     0,     0,  -192,     0,
     545,   127,   128,     0,   550,   126,     0,   125,     0,     0,
     125,   125,   553,     0,   125,     0,     0,   125,   451,   448,
     451,     0,     0,     0,   212,   451,   127,   128,   413,   414,
     136,   138,     0,     0,     0,   406,     0,   451,     0,     0,
     126,     0,   106,   107,   108,   109,     0,     0,   122,   110,
     111,   112,     0,   132,   133,   197,   199,   125,   125,   125,
     125,   127,   128,     0,     0,     0,   113,   114,   115,   116,
     117,     0,   426,   125,   439,     0,     0,   382,   154,   433,
       0,   445,   200,   440,     0,     0,   444,   451,     0,   454,
       0,     0,   454,   118,     0,   256,   257,     0,   260,   454,
     263,   140,     0,   458,     0,   126,     0,  -192,  -192,  -192,
    -192,   454,     0,     0,  -192,  -192,  -192,     0,     0,   254,
     266,     0,   106,   107,   108,   109,   127,   128,     0,   110,
     111,   112,     0,   126,     0,   113,   114,   115,   116,   117,
       0,   127,   128,   125,     0,     0,   126,   154,   113,   114,
     115,   116,   117,   125,   127,   128,     0,   489,     0,   490,
     455,     0,     0,     0,     0,     0,   301,   127,   128,     0,
       0,   319,   126,     0,   435,   320,   321,   322,     0,   309,
     310,   323,   324,   311,   326,   312,   467,   504,   436,   220,
       0,   439,   332,   127,   128,     0,   321,   113,   114,   115,
     116,   117,   454,     0,   454,     0,   341,     0,   313,   454,
     106,   107,   108,   109,   347,     0,     0,   110,   111,   112,
     134,   454,     0,   113,   114,   115,   116,   117,     0,     0,
     382,     0,     0,     0,     0,     0,   364,     0,   366,  -192,
     368,   369,     0,   371,   351,     0,   352,     0,     0,     0,
     155,   155,   155,   162,   167,     0,   155,   155,   155,   162,
     155,   118,     0,     0,     0,     0,     0,   162,   155,   389,
       0,   454,   201,   119,   155,     0,     0,     0,     0,   214,
     216,   218,   162,   221,   223,     0,   399,     0,   155,   155,
     155,   155,   162,   403,   405,     0,     0,     0,   155,     0,
     393,     0,     0,   395,   396,     0,     0,   397,     0,   315,
     398,   106,   107,   108,   109,     0,     0,     0,   110,   111,
     112,     0,     0,     0,   113,   114,   115,   116,   117,   106,
     107,   108,   109,     0,     0,     0,   110,   111,   112,     0,
       0,     0,   113,   114,   115,   116,   117,     0,     0,   118,
     420,   421,   422,   423,   126,     0,   106,   107,   108,   109,
       0,   119,   151,   110,   111,   112,   434,     0,     0,   113,
     114,   115,   116,   117,     0,   127,   128,   106,   107,   108,
     109,     0,     0,     0,   110,   111,   112,     0,     0,     0,
     113,   114,   115,   116,   117,     0,     0,   106,   107,   108,
     109,     0,   476,     0,   110,   111,   112,     0,     0,     0,
       0,     0,     0,   155,     0,     0,   155,     0,   106,   107,
     108,   109,     0,     0,   151,   110,   111,   112,     0,     0,
       0,   113,   114,   115,   116,   117,   480,     0,     0,     0,
       0,     0,   155,     0,     0,     0,   488,     0,     0,   126,
     118,  -192,  -192,  -192,  -192,     0,     0,     0,  -192,  -192,
    -192,     0,   119,     0,   188,   476,     0,   145,   118,     0,
     127,   128,     0,   146,   147,   148,   303,   304,   305,   306,
     119,   106,   107,   108,   109,   127,   128,     0,   110,   111,
     112,     0,   152,     0,   113,   114,   115,   116,   117,     0,
       0,     0,     0,   303,   304,   305,   306,     0,     0,   162,
       0,     0,     0,     0,     0,   126,   118,   106,   107,   108,
     109,     0,     0,   151,   110,   111,   112,     0,   119,   379,
     113,   114,   115,   116,   117,     0,   127,   128,     0,     0,
     106,   107,   108,   109,     0,     0,   162,   110,   111,   112,
       0,     0,   155,   162,   152,     0,     0,   162,     0,     0,
     162,     0,     0,     0,   134,     0,     0,     0,   155,   548,
       0,   106,   107,   108,   109,     0,     0,   162,   110,   111,
     112,     0,     0,     0,   113,   114,   115,   116,   117,   106,
     107,   108,   109,     0,     0,   441,   110,   111,   112,   106,
     107,   108,   109,     0,     0,     0,   110,   111,   112,     0,
       0,     0,     0,     0,     0,     0,     0,   152,     0,     0,
       0,   155,     0,     0,     0,     0,     0,     0,   303,   304,
     305,   306,     0,     0,   155,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   152,     0,     0,     0,     0,   170,     0,
       0,   162,   407,   408,   409,   410,   411,   412,     0,     0,
       1,     0,     0,     0,     0,     0,     2,     0,   450,     0,
       0,     0,     0,     0,     0,     3,     0,     0,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,     0,     0,    19,    20,    21,    22,    23,
     118,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,     0,     0,     0,     0,     0,     0,  -171,
       0,  -171,  -171,  -171,  -171,     0,     0,  -171,  -171,  -171,
    -171,     0,     0,     1,  -171,  -171,  -171,  -171,  -171,     2,
       0,    86,     0,     0,     0,     0,     0,     0,     0,    87,
      88,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,     0,     0,    19,    20,
      21,    22,    23,     0,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,   106,   107,   108,   109,
       0,     0,     0,   110,   111,   112,     0,     0,     0,   113,
     114,   115,   116,   117,     0,     0,     0,  -171,     0,     0,
       0,     0,     0,     0,     0,     0,   126,     0,   106,   107,
     108,   109,    87,    88,   151,   110,   111,   112,     0,   175,
       0,   113,   114,   115,   116,   117,     0,   127,   128,   126,
       0,   106,   107,   108,   109,     0,     0,   151,   110,   111,
     112,     0,     0,     0,   113,   114,   115,   116,   117,     0,
     127,   128,   126,     0,   106,   107,   108,   109,     0,     0,
       0,   110,   111,   112,     0,     0,     0,   113,   114,   115,
     116,   117,     0,   127,   128,     0,   430,     0,   106,   107,
     108,   109,     0,   450,   151,   110,   111,   112,     0,     0,
       0,   113,   114,   115,   116,   117,     0,     0,     0,     0,
       0,   478,     0,   106,   107,   108,   109,     0,     0,   151,
     110,   111,   112,     0,     0,   118,   113,   114,   115,   116,
     117,   432,     0,   106,   107,   108,   109,     0,     0,     0,
     110,   111,   112,     0,     0,     0,   113,   114,   115,   116,
     117,     0,     0,     0,   152,   106,   107,   108,   109,     0,
       0,     0,   110,   111,   112,     0,     0,     0,   113,   114,
     115,   116,   117,     0,     0,     0,     0,   152,   106,   107,
     108,   109,     0,     0,     0,   110,   111,   112,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     152,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   152,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   152,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   152,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   274,     0,   275,   276,     0,
       0,   152,     0,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293
};

static const yytype_int16 yycheck[] =
{
       5,   111,     1,     8,     9,    22,   116,   349,     1,   137,
      14,    15,    16,    18,    19,    20,    21,    22,    23,     1,
      24,    38,    27,    28,   314,   114,   115,    32,    33,    34,
       1,   135,    37,    38,   137,   338,    41,   135,    43,   135,
      22,    23,   345,    48,     1,    50,   116,    52,    53,    54,
      55,   322,    57,    21,   357,   326,    61,    62,    63,    64,
      65,     0,    67,    22,   142,    22,    23,    21,    73,    15,
      75,    76,    77,    78,    21,    22,    81,    82,    11,    12,
     135,   113,     1,   115,   135,    32,    39,    40,     1,    42,
     116,    38,    25,    26,   384,   127,   128,   129,    18,     1,
     138,     1,   139,    22,    23,    52,    53,    54,    55,    22,
      23,    44,    45,   140,     1,    62,    49,   122,    51,     1,
      22,    23,     4,   116,   129,   139,    59,    60,    10,    11,
      12,   111,     1,    66,   116,    22,    23,   136,    71,   111,
     111,   111,   135,   117,   149,   448,    79,   450,   111,   111,
      83,    84,   455,    22,    23,   111,   161,    28,    29,    30,
     165,   116,   167,   168,   467,     1,   117,   172,   150,   151,
     152,   153,   143,   178,   152,   153,   181,   114,   183,     1,
     185,   186,   524,   525,   111,   190,    22,    23,   193,    90,
     195,   148,    80,    15,   328,   200,   201,   323,   476,   204,
      22,    23,   207,   208,   209,   437,   211,   212,    -1,   214,
     215,    -1,   217,     1,   517,   220,    87,    88,   223,   224,
      -1,   226,     1,   228,   143,   230,     1,   232,    -1,   234,
     177,   144,   237,   180,    22,    23,    -1,   242,   243,    -1,
     142,    -1,   247,    22,    23,   250,   251,    22,    23,   254,
     150,   151,   152,   153,   141,   155,    -1,     1,    -1,   206,
     265,    -1,    -1,   268,    -1,     1,   271,   272,    -1,    -1,
       6,     7,    16,    17,    18,    19,    20,    -1,    22,    23,
     116,   150,   151,   152,   153,    -1,    14,    15,    16,    17,
      -1,   296,   297,    -1,   116,    23,    24,    -1,     1,    35,
      -1,    -1,    -1,    31,   140,     1,   311,   312,   150,   151,
     152,   153,   316,    -1,     3,     4,     5,     6,    46,    22,
      23,    10,    11,    12,    -1,    -1,    22,    23,    56,   334,
      -1,     1,   337,   141,   142,   143,    72,   116,    -1,    -1,
       1,   346,    -1,    -1,    -1,    81,   351,   352,    -1,   137,
      86,   356,    22,    23,    24,     1,    -1,     3,     4,     5,
       6,    22,    23,   138,    10,    11,    12,    -1,    -1,    -1,
      16,    17,    18,    19,    20,   380,    22,    23,    -1,    -1,
      -1,   385,     1,   119,    -1,   332,    -1,   392,   393,    -1,
     395,   396,   397,   398,    -1,     1,   132,   133,   142,    -1,
     136,   406,   138,    22,    23,   141,   142,   143,   328,    -1,
      16,    17,    18,    19,    20,   335,    22,    23,   338,   424,
     116,   426,     1,    -1,   429,   345,   431,     1,   433,   434,
     238,   239,   437,   366,    -1,   368,    15,   357,   443,   444,
      -1,    15,   447,    22,    23,    -1,   135,   452,    22,    23,
      -1,   398,   457,   458,   459,    -1,   461,    -1,    -1,   464,
     149,   197,    -1,   199,   469,   470,   471,   472,   473,   474,
     116,    -1,   477,    -1,   479,   480,     1,    16,    17,    18,
      19,    20,   487,   488,   489,   490,   491,    -1,    -1,    -1,
       1,    16,    17,    18,    19,    20,   142,    -1,    -1,   235,
      -1,    -1,   238,   239,    15,    -1,    -1,    -1,   154,    -1,
     515,    22,    23,    -1,   519,     1,    -1,   253,    -1,    -1,
     256,   257,   527,    -1,   260,    -1,    -1,   263,   448,    15,
     450,    -1,    -1,    -1,   140,   455,    22,    23,   274,   275,
       8,     9,    -1,    -1,    -1,   273,    -1,   467,    -1,    -1,
       1,    -1,     3,     4,     5,     6,    -1,    -1,     1,    10,
      11,    12,    -1,     6,     7,    33,    34,   303,   304,   305,
     306,    22,    23,    -1,    -1,    -1,    16,    17,    18,    19,
      20,    -1,   310,   319,   320,    -1,    -1,   323,   316,   317,
      -1,   327,    35,   321,    -1,    -1,   324,   517,    -1,   335,
      -1,    -1,   338,   142,    -1,    73,    74,    -1,    76,   345,
      78,   136,    -1,   341,    -1,     1,    -1,     3,     4,     5,
       6,   357,    -1,    -1,    10,    11,    12,    -1,    -1,    72,
       1,    -1,     3,     4,     5,     6,    22,    23,    -1,    10,
      11,    12,    -1,     1,    -1,    16,    17,    18,    19,    20,
      -1,    22,    23,   389,    -1,    -1,     1,   385,    16,    17,
      18,    19,    20,   399,    22,    23,    -1,   403,    -1,   405,
      15,    -1,    -1,    -1,    -1,    -1,   119,    22,    23,    -1,
      -1,   149,     1,    -1,   135,   153,   154,   155,    -1,   132,
     133,   159,   160,   136,   162,   138,    15,   425,   149,   139,
      -1,   437,   170,    22,    23,    -1,   174,    16,    17,    18,
      19,    20,   448,    -1,   450,    -1,   184,    -1,     1,   455,
       3,     4,     5,     6,   192,    -1,    -1,    10,    11,    12,
     116,   467,    -1,    16,    17,    18,    19,    20,    -1,    -1,
     476,    -1,    -1,    -1,    -1,    -1,   214,    -1,   216,   135,
     218,   219,    -1,   221,   197,    -1,   199,    -1,    -1,    -1,
      14,    15,    16,    17,    18,    -1,    20,    21,    22,    23,
      24,   142,    -1,    -1,    -1,    -1,    -1,    31,    32,   247,
      -1,   517,    36,   154,    38,    -1,    -1,    -1,    -1,    43,
      44,    45,    46,    47,    48,    -1,   264,    -1,    52,    53,
      54,    55,    56,   271,   272,    -1,    -1,    -1,    62,    -1,
     253,    -1,    -1,   256,   257,    -1,    -1,   260,    -1,     1,
     263,     3,     4,     5,     6,    -1,    -1,    -1,    10,    11,
      12,    -1,    -1,    -1,    16,    17,    18,    19,    20,     3,
       4,     5,     6,    -1,    -1,    -1,    10,    11,    12,    -1,
      -1,    -1,    16,    17,    18,    19,    20,    -1,    -1,   142,
     303,   304,   305,   306,     1,    -1,     3,     4,     5,     6,
      -1,   154,     9,    10,    11,    12,   319,    -1,    -1,    16,
      17,    18,    19,    20,    -1,    22,    23,     3,     4,     5,
       6,    -1,    -1,    -1,    10,    11,    12,    -1,    -1,    -1,
      16,    17,    18,    19,    20,    -1,    -1,     3,     4,     5,
       6,    -1,   380,    -1,    10,    11,    12,    -1,    -1,    -1,
      -1,    -1,    -1,   177,    -1,    -1,   180,    -1,     3,     4,
       5,     6,    -1,    -1,     9,    10,    11,    12,    -1,    -1,
      -1,    16,    17,    18,    19,    20,   389,    -1,    -1,    -1,
      -1,    -1,   206,    -1,    -1,    -1,   399,    -1,    -1,     1,
     142,     3,     4,     5,     6,    -1,    -1,    -1,    10,    11,
      12,    -1,   154,    -1,     1,   443,    -1,     4,   142,    -1,
      22,    23,    -1,    10,    11,    12,   150,   151,   152,   153,
     154,     3,     4,     5,     6,    22,    23,    -1,    10,    11,
      12,    -1,   139,    -1,    16,    17,    18,    19,    20,    -1,
      -1,    -1,    -1,   150,   151,   152,   153,    -1,    -1,   273,
      -1,    -1,    -1,    -1,    -1,     1,   142,     3,     4,     5,
       6,    -1,    -1,     9,    10,    11,    12,    -1,   154,   135,
      16,    17,    18,    19,    20,    -1,    22,    23,    -1,    -1,
       3,     4,     5,     6,    -1,    -1,   310,    10,    11,    12,
      -1,    -1,   316,   317,   139,    -1,    -1,   321,    -1,    -1,
     324,    -1,    -1,    -1,   116,    -1,    -1,    -1,   332,     1,
      -1,     3,     4,     5,     6,    -1,    -1,   341,    10,    11,
      12,    -1,    -1,    -1,    16,    17,    18,    19,    20,     3,
       4,     5,     6,    -1,    -1,     9,    10,    11,    12,     3,
       4,     5,     6,    -1,    -1,    -1,    10,    11,    12,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   139,    -1,    -1,
      -1,   385,    -1,    -1,    -1,    -1,    -1,    -1,   150,   151,
     152,   153,    -1,    -1,   398,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   139,    -1,    -1,    -1,    -1,   144,    -1,
      -1,   425,   125,   126,   127,   128,   129,   130,    -1,    -1,
       7,    -1,    -1,    -1,    -1,    -1,    13,    -1,   110,    -1,
      -1,    -1,    -1,    -1,    -1,    22,    -1,    -1,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    -1,    -1,    42,    43,    44,    45,    46,
     142,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      -1,     3,     4,     5,     6,    -1,    -1,     9,    10,    11,
      12,    -1,    -1,     7,    16,    17,    18,    19,    20,    13,
      -1,   138,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   146,
     147,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    -1,    -1,    42,    43,
      44,    45,    46,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,     3,     4,     5,     6,
      -1,    -1,    -1,    10,    11,    12,    -1,    -1,    -1,    16,
      17,    18,    19,    20,    -1,    -1,    -1,   139,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,     3,     4,
       5,     6,   146,   147,     9,    10,    11,    12,    -1,    14,
      -1,    16,    17,    18,    19,    20,    -1,    22,    23,     1,
      -1,     3,     4,     5,     6,    -1,    -1,     9,    10,    11,
      12,    -1,    -1,    -1,    16,    17,    18,    19,    20,    -1,
      22,    23,     1,    -1,     3,     4,     5,     6,    -1,    -1,
      -1,    10,    11,    12,    -1,    -1,    -1,    16,    17,    18,
      19,    20,    -1,    22,    23,    -1,     1,    -1,     3,     4,
       5,     6,    -1,   110,     9,    10,    11,    12,    -1,    -1,
      -1,    16,    17,    18,    19,    20,    -1,    -1,    -1,    -1,
      -1,     1,    -1,     3,     4,     5,     6,    -1,    -1,     9,
      10,    11,    12,    -1,    -1,   142,    16,    17,    18,    19,
      20,     1,    -1,     3,     4,     5,     6,    -1,    -1,    -1,
      10,    11,    12,    -1,    -1,    -1,    16,    17,    18,    19,
      20,    -1,    -1,    -1,   139,     3,     4,     5,     6,    -1,
      -1,    -1,    10,    11,    12,    -1,    -1,    -1,    16,    17,
      18,    19,    20,    -1,    -1,    -1,    -1,   139,     3,     4,
       5,     6,    -1,    -1,    -1,    10,    11,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     139,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   139,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   139,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   139,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   110,    -1,   112,   113,    -1,
      -1,   139,    -1,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,    13,    22,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    42,
      43,    44,    45,    46,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   138,   146,   147,   157,
     158,   160,   161,   162,   163,   164,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   204,     3,     4,     5,     6,
      10,    11,    12,    16,    17,    18,    19,    20,   142,   154,
     180,   189,   192,   199,   201,   202,     1,    22,    23,   148,
     159,   159,   192,   192,   116,   159,   188,   159,   188,     1,
     136,   177,   177,   177,     1,     4,    10,    11,    12,   183,
     200,     9,   139,   185,   187,   189,   190,   191,   202,   185,
     185,   187,   189,   159,   180,   181,   182,   189,   144,   159,
     144,   159,   184,   185,   187,    14,   159,   179,   184,   159,
     179,   184,   159,   187,   185,   177,   177,   159,     1,   159,
     183,   183,   183,   187,   159,   184,   159,   188,   159,   188,
     192,   189,   137,   159,   175,   159,   179,   184,   175,   175,
     159,   175,   140,   159,   189,   177,   189,   177,   189,   187,
     139,   189,   159,   189,   177,   159,   177,   159,   184,   159,
     184,   159,   184,   159,   184,   187,   159,   135,   177,   177,
     159,   159,   184,   141,   159,   159,   159,   177,   159,   137,
     176,   135,   135,   177,   192,   159,   188,   188,   159,   159,
     188,   159,   159,   188,   177,   176,     1,   159,   178,   192,
     159,   177,   177,    21,   110,   112,   113,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   202,   206,   183,   183,     0,   160,
      22,   192,   142,   150,   151,   152,   153,   159,   159,   192,
     192,   192,   192,     1,   178,     1,   178,   178,   159,   188,
     188,   188,   188,   188,   188,   159,   188,    21,   116,   159,
     159,   159,   188,   159,   184,    15,   159,   184,    15,   159,
     159,   188,   159,   159,   159,    15,     1,   188,   159,   165,
     159,   192,   192,   159,   159,   159,   184,    15,   159,   159,
     159,   159,   159,   159,   188,   159,   188,   159,   188,   188,
     159,   188,   159,   159,   159,   159,   159,   159,   159,   135,
     195,   196,   202,   159,   178,   178,   159,   159,   159,   188,
     159,   159,   135,   192,   159,   192,   192,   192,   192,   188,
     159,   159,   159,   188,   159,   188,   187,   125,   126,   127,
     128,   129,   130,   202,   202,   116,   159,   159,     1,   155,
     192,   192,   192,   192,   186,   188,   187,   159,   159,   186,
       1,   185,     1,   187,   192,   135,   149,   197,   198,   202,
     187,     9,   190,   195,   187,   202,   182,   184,    15,   159,
     110,   180,   193,   194,   202,    15,   159,   193,   187,   193,
     159,   135,   203,   204,   205,   159,   159,    15,   159,   193,
     140,   177,   177,   139,   139,   159,   188,   186,     1,   185,
     192,   159,   159,   159,   159,   159,   159,   184,   192,   202,
     202,    24,   159,   111,   111,   111,   111,   111,   111,   111,
     116,   114,   115,   159,   187,   159,   159,   159,   159,   159,
     159,   198,   159,   159,   159,   193,   193,   143,   159,   193,
     159,   159,   159,   159,   117,   117,   159,   193,   159,   159,
     159,   159,   159,   159,   196,   159,   159,   159,   159,   159,
     159,   159,   159,   116,   114,   159,     1,   111,     1,   193,
     159,   204,   204,   159,   113,   115,   127,   128,   129,   111
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,   156,   157,   157,   157,   158,   158,   159,   159,   159,
     160,   160,   160,   160,   160,   160,   160,   160,   160,   160,
     160,   160,   160,   161,   161,   161,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   162,   162,   162,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   165,   164,   164,   164,   164,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   167,   167,   167,   167,
     167,   167,   167,   167,   167,   167,   167,   167,   167,   167,
     167,   167,   167,   168,   168,   168,   168,   168,   168,   168,
     168,   168,   169,   169,   169,   169,   169,   169,   169,   169,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   172,
     172,   172,   173,   173,   174,   175,   176,   176,   177,   177,
     178,   178,   179,   179,   180,   180,   181,   181,   182,   183,
     183,   184,   184,   185,   185,   185,   186,   186,   187,   187,
     187,   188,   188,   189,   189,   189,   189,   189,   190,   191,
     192,   192,   192,   192,   192,   192,   192,   193,   193,   193,
     193,   193,   194,   194,   195,   195,   196,   196,   197,   197,
     198,   198,   198,   199,   199,   200,   200,   200,   200,   201,
     201,   201,   202,   202,   202,   202,   202,   203,   203,   203,
     204,   205,   205,   206,   206,   206,   206,   206,   206,   206,
     206,   206,   206,   206,   206,   206,   206,   206,   206,   206,
     206,   206,   206,   206,   206,   206,   206,   206,   206,   206,
     206,   206,   206,   206,   206,   206,   206,   206,   206
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     3,     3,     5,     3,     2,     3,
       2,     3,     2,     4,     2,     3,     3,     2,     4,     2,
       4,     2,     4,     2,     4,     2,     1,     2,     3,     3,
       5,     3,     5,     3,     5,     3,     5,     3,     2,     4,
       5,     0,     5,     3,     3,     2,     5,     5,     5,     5,
       5,     3,     2,     3,     2,     3,     2,     3,     2,     3,
       2,     2,     2,     4,     5,     5,     3,     5,     4,     6,
       2,     3,     5,     4,     6,     2,     3,     5,     4,     6,
       2,     3,     2,     3,     3,     3,     5,     3,     2,     5,
       5,     4,     3,     2,     3,     2,     3,     2,     2,     2,
       3,     3,     2,     3,     3,     3,     3,     3,     2,     3,
       2,     3,     5,     3,     4,     2,     4,     4,     2,     3,
       5,     5,     5,     3,     4,     5,     4,     5,     4,     5,
       5,     2,     3,     4,     3,     3,     5,     3,     5,     3,
       2,     3,     4,     2,     2,     1,     1,     0,     1,     1,
       1,     1,     1,     0,     1,     2,     3,     1,     3,     1,
       1,     1,     1,     3,     1,     3,     2,     0,     1,     3,
       1,     1,     0,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     1,     3,     3,     3,
       3,     1,     1,     1,     3,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     2,
       2,     1,     1,     2,     1,     3,     3,     3,     5,     5,
       3,     3,     3,     3,     3,     3,     5,     5,     5,     5,
       0,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* top_level: command_list  */
#line 186 "mon_parse.y"
                        { (yyval.i) = 0; }
#line 2388 "mon_parse.c"
    break;

  case 3: /* top_level: assembly_instruction TRAIL  */
#line 187 "mon_parse.y"
                                      { (yyval.i) = 0; }
#line 2394 "mon_parse.c"
    break;

  case 4: /* top_level: TRAIL  */
#line 188 "mon_parse.y"
                 { new_cmd = 1; asm_mode = 0;  (yyval.i) = 0; }
#line 2400 "mon_parse.c"
    break;

  case 9: /* end_cmd: error  */
#line 197 "mon_parse.y"
               { return ERR_EXPECT_END_CMD; }
#line 2406 "mon_parse.c"
    break;

  case 22: /* command: BAD_CMD  */
#line 212 "mon_parse.y"
                 { return ERR_BAD_CMD; }
#line 2412 "mon_parse.c"
    break;

  case 23: /* machine_state_rules: CMD_BANK end_cmd  */
#line 216 "mon_parse.y"
                     { mon_bank(e_default_space, NULL); }
#line 2418 "mon_parse.c"
    break;

  case 24: /* machine_state_rules: CMD_BANK memspace end_cmd  */
#line 218 "mon_parse.y"
                     { mon_bank((yyvsp[-1].i), NULL); }
#line 2424 "mon_parse.c"
    break;

  case 25: /* machine_state_rules: CMD_BANK BANKNAME end_cmd  */
#line 220 "mon_parse.y"
                     { mon_bank(e_default_space, (yyvsp[-1].str)); }
#line 2430 "mon_parse.c"
    break;

  case 26: /* machine_state_rules: CMD_BANK memspace opt_sep BANKNAME end_cmd  */
#line 222 "mon_parse.y"
                     { mon_bank((yyvsp[-3].i), (yyvsp[-1].str)); }
#line 2436 "mon_parse.c"
    break;

  case 27: /* machine_state_rules: CMD_GOTO address end_cmd  */
#line 224 "mon_parse.y"
                     { mon_jump((yyvsp[-1].a)); }
#line 2442 "mon_parse.c"
    break;

  case 28: /* machine_state_rules: CMD_IO end_cmd  */
#line 226 "mon_parse.y"
                     { mon_display_io_regs(0); }
#line 2448 "mon_parse.c"
    break;

  case 29: /* machine_state_rules: CMD_IO address end_cmd  */
#line 228 "mon_parse.y"
                     { mon_display_io_regs((yyvsp[-1].a)); }
#line 2454 "mon_parse.c"
    break;

  case 30: /* machine_state_rules: CMD_CPU end_cmd  */
#line 230 "mon_parse.y"
                     { monitor_cpu_type_set(""); }
#line 2460 "mon_parse.c"
    break;

  case 31: /* machine_state_rules: CMD_CPU CPUTYPE end_cmd  */
#line 232 "mon_parse.y"
                     { monitor_cpu_type_set((yyvsp[-1].str)); }
#line 2466 "mon_parse.c"
    break;

  case 32: /* machine_state_rules: CMD_CPUHISTORY end_cmd  */
#line 234 "mon_parse.y"
                     { mon_cpuhistory(-1); }
#line 2472 "mon_parse.c"
    break;

  case 33: /* machine_state_rules: CMD_CPUHISTORY opt_sep expression end_cmd  */
#line 236 "mon_parse.y"
                     { mon_cpuhistory((yyvsp[-1].i)); }
#line 2478 "mon_parse.c"
    break;

  case 34: /* machine_state_rules: CMD_RETURN end_cmd  */
#line 238 "mon_parse.y"
                     { mon_instruction_return(); }
#line 2484 "mon_parse.c"
    break;

  case 35: /* machine_state_rules: CMD_DUMP filename end_cmd  */
#line 240 "mon_parse.y"
                     { machine_write_snapshot((yyvsp[-1].str),0,0,0); /* FIXME */ }
#line 2490 "mon_parse.c"
    break;

  case 36: /* machine_state_rules: CMD_UNDUMP filename end_cmd  */
#line 242 "mon_parse.y"
                     { machine_read_snapshot((yyvsp[-1].str), 0); }
#line 2496 "mon_parse.c"
    break;

  case 37: /* machine_state_rules: CMD_STEP end_cmd  */
#line 244 "mon_parse.y"
                     { mon_instructions_step(-1); }
#line 2502 "mon_parse.c"
    break;

  case 38: /* machine_state_rules: CMD_STEP opt_sep expression end_cmd  */
#line 246 "mon_parse.y"
                     { mon_instructions_step((yyvsp[-1].i)); }
#line 2508 "mon_parse.c"
    break;

  case 39: /* machine_state_rules: CMD_NEXT end_cmd  */
#line 248 "mon_parse.y"
                     { mon_instructions_next(-1); }
#line 2514 "mon_parse.c"
    break;

  case 40: /* machine_state_rules: CMD_NEXT opt_sep expression end_cmd  */
#line 250 "mon_parse.y"
                     { mon_instructions_next((yyvsp[-1].i)); }
#line 2520 "mon_parse.c"
    break;

  case 41: /* machine_state_rules: CMD_UP end_cmd  */
#line 252 "mon_parse.y"
                     { mon_stack_up(-1); }
#line 2526 "mon_parse.c"
    break;

  case 42: /* machine_state_rules: CMD_UP opt_sep expression end_cmd  */
#line 254 "mon_parse.y"
                     { mon_stack_up((yyvsp[-1].i)); }
#line 2532 "mon_parse.c"
    break;

  case 43: /* machine_state_rules: CMD_DOWN end_cmd  */
#line 256 "mon_parse.y"
                     { mon_stack_down(-1); }
#line 2538 "mon_parse.c"
    break;

  case 44: /* machine_state_rules: CMD_DOWN opt_sep expression end_cmd  */
#line 258 "mon_parse.y"
                     { mon_stack_down((yyvsp[-1].i)); }
#line 2544 "mon_parse.c"
    break;

  case 45: /* machine_state_rules: CMD_SCREEN end_cmd  */
#line 260 "mon_parse.y"
                     { mon_display_screen(); }
#line 2550 "mon_parse.c"
    break;

  case 47: /* register_mod: CMD_REGISTERS end_cmd  */
#line 265 "mon_parse.y"
              { (monitor_cpu_for_memspace[default_memspace]->mon_register_print)(default_memspace); }
#line 2556 "mon_parse.c"
    break;

  case 48: /* register_mod: CMD_REGISTERS memspace end_cmd  */
#line 267 "mon_parse.y"
              { (monitor_cpu_for_memspace[(yyvsp[-1].i)]->mon_register_print)((yyvsp[-1].i)); }
#line 2562 "mon_parse.c"
    break;

  case 50: /* symbol_table_rules: CMD_LOAD_LABELS memspace opt_sep filename end_cmd  */
#line 272 "mon_parse.y"
                    {
                        /* What about the memspace? */
                        mon_playback_init((yyvsp[-1].str));
                    }
#line 2571 "mon_parse.c"
    break;

  case 51: /* symbol_table_rules: CMD_LOAD_LABELS filename end_cmd  */
#line 277 "mon_parse.y"
                    {
                        /* What about the memspace? */
                        mon_playback_init((yyvsp[-1].str));
                    }
#line 2580 "mon_parse.c"
    break;

  case 52: /* symbol_table_rules: CMD_SAVE_LABELS memspace opt_sep filename end_cmd  */
#line 282 "mon_parse.y"
                    { mon_save_symbols((yyvsp[-3].i), (yyvsp[-1].str)); }
#line 2586 "mon_parse.c"
    break;

  case 53: /* symbol_table_rules: CMD_SAVE_LABELS filename end_cmd  */
#line 284 "mon_parse.y"
                    { mon_save_symbols(e_default_space, (yyvsp[-1].str)); }
#line 2592 "mon_parse.c"
    break;

  case 54: /* symbol_table_rules: CMD_ADD_LABEL address opt_sep LABEL end_cmd  */
#line 286 "mon_parse.y"
                    { mon_add_name_to_symbol_table((yyvsp[-3].a), (yyvsp[-1].str)); }
#line 2598 "mon_parse.c"
    break;

  case 55: /* symbol_table_rules: CMD_DEL_LABEL LABEL end_cmd  */
#line 288 "mon_parse.y"
                    { mon_remove_name_from_symbol_table(e_default_space, (yyvsp[-1].str)); }
#line 2604 "mon_parse.c"
    break;

  case 56: /* symbol_table_rules: CMD_DEL_LABEL memspace opt_sep LABEL end_cmd  */
#line 290 "mon_parse.y"
                    { mon_remove_name_from_symbol_table((yyvsp[-3].i), (yyvsp[-1].str)); }
#line 2610 "mon_parse.c"
    break;

  case 57: /* symbol_table_rules: CMD_SHOW_LABELS memspace end_cmd  */
#line 292 "mon_parse.y"
                    { mon_print_symbol_table((yyvsp[-1].i)); }
#line 2616 "mon_parse.c"
    break;

  case 58: /* symbol_table_rules: CMD_SHOW_LABELS end_cmd  */
#line 294 "mon_parse.y"
                    { mon_print_symbol_table(e_default_space); }
#line 2622 "mon_parse.c"
    break;

  case 59: /* symbol_table_rules: CMD_LABEL_ASGN EQUALS address end_cmd  */
#line 296 "mon_parse.y"
                    {
                        mon_add_name_to_symbol_table((yyvsp[-1].a), mon_prepend_dot_to_name((yyvsp[-3].str)));
                    }
#line 2630 "mon_parse.c"
    break;

  case 60: /* symbol_table_rules: CMD_LABEL_ASGN EQUALS address LABEL_ASGN_COMMENT end_cmd  */
#line 300 "mon_parse.y"
                    {
                        mon_add_name_to_symbol_table((yyvsp[-2].a), mon_prepend_dot_to_name((yyvsp[-4].str)));
                    }
#line 2638 "mon_parse.c"
    break;

  case 61: /* $@1: %empty  */
#line 306 "mon_parse.y"
           { mon_start_assemble_mode((yyvsp[0].a), NULL); }
#line 2644 "mon_parse.c"
    break;

  case 62: /* asm_rules: CMD_ASSEMBLE address $@1 post_assemble end_cmd  */
#line 307 "mon_parse.y"
           { }
#line 2650 "mon_parse.c"
    break;

  case 63: /* asm_rules: CMD_ASSEMBLE address end_cmd  */
#line 309 "mon_parse.y"
           { mon_start_assemble_mode((yyvsp[-1].a), NULL); }
#line 2656 "mon_parse.c"
    break;

  case 64: /* asm_rules: CMD_DISASSEMBLE address_opt_range end_cmd  */
#line 311 "mon_parse.y"
           { mon_disassemble_lines((yyvsp[-1].range)[0], (yyvsp[-1].range)[1]); }
#line 2662 "mon_parse.c"
    break;

  case 65: /* asm_rules: CMD_DISASSEMBLE end_cmd  */
#line 313 "mon_parse.y"
           { mon_disassemble_lines(BAD_ADDR, BAD_ADDR); }
#line 2668 "mon_parse.c"
    break;

  case 66: /* memory_rules: CMD_MOVE address_range opt_sep address end_cmd  */
#line 317 "mon_parse.y"
              { mon_memory_move((yyvsp[-3].range)[0], (yyvsp[-3].range)[1], (yyvsp[-1].a)); }
#line 2674 "mon_parse.c"
    break;

  case 67: /* memory_rules: CMD_COMPARE address_range opt_sep address end_cmd  */
#line 319 "mon_parse.y"
              { mon_memory_compare((yyvsp[-3].range)[0], (yyvsp[-3].range)[1], (yyvsp[-1].a)); }
#line 2680 "mon_parse.c"
    break;

  case 68: /* memory_rules: CMD_FILL address_range opt_sep data_list end_cmd  */
#line 321 "mon_parse.y"
              { mon_memory_fill((yyvsp[-3].range)[0], (yyvsp[-3].range)[1],(unsigned char *)(yyvsp[-1].str)); }
#line 2686 "mon_parse.c"
    break;

  case 69: /* memory_rules: CMD_HUNT address_range opt_sep hunt_list end_cmd  */
#line 323 "mon_parse.y"
              { mon_memory_hunt((yyvsp[-3].range)[0], (yyvsp[-3].range)[1],(unsigned char *)(yyvsp[-1].str)); }
#line 2692 "mon_parse.c"
    break;

  case 70: /* memory_rules: CMD_MEM_DISPLAY RADIX_TYPE opt_sep address_opt_range end_cmd  */
#line 325 "mon_parse.y"
              { mon_memory_display((yyvsp[-3].rt), (yyvsp[-1].range)[0], (yyvsp[-1].range)[1], DF_PETSCII); }
#line 2698 "mon_parse.c"
    break;

  case 71: /* memory_rules: CMD_MEM_DISPLAY address_opt_range end_cmd  */
#line 327 "mon_parse.y"
              { mon_memory_display(default_radix, (yyvsp[-1].range)[0], (yyvsp[-1].range)[1], DF_PETSCII); }
#line 2704 "mon_parse.c"
    break;

  case 72: /* memory_rules: CMD_MEM_DISPLAY end_cmd  */
#line 329 "mon_parse.y"
              { mon_memory_display(default_radix, BAD_ADDR, BAD_ADDR, DF_PETSCII); }
#line 2710 "mon_parse.c"
    break;

  case 73: /* memory_rules: CMD_CHAR_DISPLAY address_opt_range end_cmd  */
#line 331 "mon_parse.y"
              { mon_memory_display_data((yyvsp[-1].range)[0], (yyvsp[-1].range)[1], 8, 8); }
#line 2716 "mon_parse.c"
    break;

  case 74: /* memory_rules: CMD_CHAR_DISPLAY end_cmd  */
#line 333 "mon_parse.y"
              { mon_memory_display_data(BAD_ADDR, BAD_ADDR, 8, 8); }
#line 2722 "mon_parse.c"
    break;

  case 75: /* memory_rules: CMD_SPRITE_DISPLAY address_opt_range end_cmd  */
#line 335 "mon_parse.y"
              { mon_memory_display_data((yyvsp[-1].range)[0], (yyvsp[-1].range)[1], 24, 21); }
#line 2728 "mon_parse.c"
    break;

  case 76: /* memory_rules: CMD_SPRITE_DISPLAY end_cmd  */
#line 337 "mon_parse.y"
              { mon_memory_display_data(BAD_ADDR, BAD_ADDR, 24, 21); }
#line 2734 "mon_parse.c"
    break;

  case 77: /* memory_rules: CMD_TEXT_DISPLAY address_opt_range end_cmd  */
#line 339 "mon_parse.y"
              { mon_memory_display(0, (yyvsp[-1].range)[0], (yyvsp[-1].range)[1], DF_PETSCII); }
#line 2740 "mon_parse.c"
    break;

  case 78: /* memory_rules: CMD_TEXT_DISPLAY end_cmd  */
#line 341 "mon_parse.y"
              { mon_memory_display(0, BAD_ADDR, BAD_ADDR, DF_PETSCII); }
#line 2746 "mon_parse.c"
    break;

  case 79: /* memory_rules: CMD_SCREENCODE_DISPLAY address_opt_range end_cmd  */
#line 343 "mon_parse.y"
              { mon_memory_display(0, (yyvsp[-1].range)[0], (yyvsp[-1].range)[1], DF_SCREEN_CODE); }
#line 2752 "mon_parse.c"
    break;

  case 80: /* memory_rules: CMD_SCREENCODE_DISPLAY end_cmd  */
#line 345 "mon_parse.y"
              { mon_memory_display(0, BAD_ADDR, BAD_ADDR, DF_SCREEN_CODE); }
#line 2758 "mon_parse.c"
    break;

  case 81: /* memory_rules: CMD_MEMMAPZAP end_cmd  */
#line 347 "mon_parse.y"
              { mon_memmap_zap(); }
#line 2764 "mon_parse.c"
    break;

  case 82: /* memory_rules: CMD_MEMMAPSHOW end_cmd  */
#line 349 "mon_parse.y"
              { mon_memmap_show(-1,BAD_ADDR,BAD_ADDR); }
#line 2770 "mon_parse.c"
    break;

  case 83: /* memory_rules: CMD_MEMMAPSHOW opt_sep expression end_cmd  */
#line 351 "mon_parse.y"
              { mon_memmap_show((yyvsp[-1].i),BAD_ADDR,BAD_ADDR); }
#line 2776 "mon_parse.c"
    break;

  case 84: /* memory_rules: CMD_MEMMAPSHOW opt_sep expression address_opt_range end_cmd  */
#line 353 "mon_parse.y"
              { mon_memmap_show((yyvsp[-2].i),(yyvsp[-1].range)[0],(yyvsp[-1].range)[1]); }
#line 2782 "mon_parse.c"
    break;

  case 85: /* memory_rules: CMD_MEMMAPSAVE filename opt_sep expression end_cmd  */
#line 355 "mon_parse.y"
              { mon_memmap_save((yyvsp[-3].str),(yyvsp[-1].i)); }
#line 2788 "mon_parse.c"
    break;

  case 86: /* checkpoint_rules: CMD_BREAK address_opt_range end_cmd  */
#line 359 "mon_parse.y"
                  {
                      mon_breakpoint_add_checkpoint((yyvsp[-1].range)[0], (yyvsp[-1].range)[1], TRUE, e_exec, FALSE);
                  }
#line 2796 "mon_parse.c"
    break;

  case 87: /* checkpoint_rules: CMD_BREAK address_opt_range IF cond_expr end_cmd  */
#line 363 "mon_parse.y"
                  {
                      temp = mon_breakpoint_add_checkpoint((yyvsp[-3].range)[0], (yyvsp[-3].range)[1], TRUE, e_exec, FALSE);
                      mon_breakpoint_set_checkpoint_condition(temp, (yyvsp[-1].cond_node));
                  }
#line 2805 "mon_parse.c"
    break;

  case 88: /* checkpoint_rules: CMD_BREAK opt_mem_op address_opt_range end_cmd  */
#line 368 "mon_parse.y"
                  {
                      mon_breakpoint_add_checkpoint((yyvsp[-1].range)[0], (yyvsp[-1].range)[1], TRUE, (yyvsp[-2].i), FALSE);
                  }
#line 2813 "mon_parse.c"
    break;

  case 89: /* checkpoint_rules: CMD_BREAK opt_mem_op address_opt_range IF cond_expr end_cmd  */
#line 372 "mon_parse.y"
                  {
                      temp = mon_breakpoint_add_checkpoint((yyvsp[-3].range)[0], (yyvsp[-3].range)[1], TRUE, (yyvsp[-4].i), FALSE);
                      mon_breakpoint_set_checkpoint_condition(temp, (yyvsp[-1].cond_node));
                  }
#line 2822 "mon_parse.c"
    break;

  case 90: /* checkpoint_rules: CMD_BREAK end_cmd  */
#line 377 "mon_parse.y"
                  { mon_breakpoint_print_checkpoints(); }
#line 2828 "mon_parse.c"
    break;

  case 91: /* checkpoint_rules: CMD_WATCH address_opt_range end_cmd  */
#line 380 "mon_parse.y"
                  {
                      mon_breakpoint_add_checkpoint((yyvsp[-1].range)[0], (yyvsp[-1].range)[1], TRUE, e_load | e_store, FALSE);
                  }
#line 2836 "mon_parse.c"
    break;

  case 92: /* checkpoint_rules: CMD_WATCH address_opt_range IF cond_expr end_cmd  */
#line 384 "mon_parse.y"
                  {
                      temp = mon_breakpoint_add_checkpoint((yyvsp[-3].range)[0], (yyvsp[-3].range)[1], TRUE, e_load | e_store, FALSE);
                      mon_breakpoint_set_checkpoint_condition(temp, (yyvsp[-1].cond_node));
                  }
#line 2845 "mon_parse.c"
    break;

  case 93: /* checkpoint_rules: CMD_WATCH opt_mem_op address_opt_range end_cmd  */
#line 389 "mon_parse.y"
                  {
                      mon_breakpoint_add_checkpoint((yyvsp[-1].range)[0], (yyvsp[-1].range)[1], TRUE, (yyvsp[-2].i), FALSE);
                  }
#line 2853 "mon_parse.c"
    break;

  case 94: /* checkpoint_rules: CMD_WATCH opt_mem_op address_opt_range IF cond_expr end_cmd  */
#line 393 "mon_parse.y"
                  {
                      temp = mon_breakpoint_add_checkpoint((yyvsp[-3].range)[0], (yyvsp[-3].range)[1], TRUE, (yyvsp[-4].i), FALSE);
                      mon_breakpoint_set_checkpoint_condition(temp, (yyvsp[-1].cond_node));
                  }
#line 2862 "mon_parse.c"
    break;

  case 95: /* checkpoint_rules: CMD_WATCH end_cmd  */
#line 398 "mon_parse.y"
                  { mon_breakpoint_print_checkpoints(); }
#line 2868 "mon_parse.c"
    break;

  case 96: /* checkpoint_rules: CMD_TRACE address_opt_range end_cmd  */
#line 401 "mon_parse.y"
                  {
                      mon_breakpoint_add_checkpoint((yyvsp[-1].range)[0], (yyvsp[-1].range)[1], FALSE, e_load | e_store | e_exec, FALSE);
                  }
#line 2876 "mon_parse.c"
    break;

  case 97: /* checkpoint_rules: CMD_TRACE address_opt_range IF cond_expr end_cmd  */
#line 405 "mon_parse.y"
                  {
                      temp = mon_breakpoint_add_checkpoint((yyvsp[-3].range)[0], (yyvsp[-3].range)[1], FALSE, e_load | e_store | e_exec, FALSE);
                      mon_breakpoint_set_checkpoint_condition(temp, (yyvsp[-1].cond_node));
                  }
#line 2885 "mon_parse.c"
    break;

  case 98: /* checkpoint_rules: CMD_TRACE opt_mem_op address_opt_range end_cmd  */
#line 410 "mon_parse.y"
                  {
                      mon_breakpoint_add_checkpoint((yyvsp[-1].range)[0], (yyvsp[-1].range)[1], FALSE, (yyvsp[-2].i), FALSE);
                  }
#line 2893 "mon_parse.c"
    break;

  case 99: /* checkpoint_rules: CMD_TRACE opt_mem_op address_opt_range IF cond_expr end_cmd  */
#line 414 "mon_parse.y"
                  {
                      temp = mon_breakpoint_add_checkpoint((yyvsp[-3].range)[0], (yyvsp[-3].range)[1], FALSE, (yyvsp[-4].i), FALSE);
                      mon_breakpoint_set_checkpoint_condition(temp, (yyvsp[-1].cond_node));
                  }
#line 2902 "mon_parse.c"
    break;

  case 100: /* checkpoint_rules: CMD_TRACE end_cmd  */
#line 419 "mon_parse.y"
                  { mon_breakpoint_print_checkpoints(); }
#line 2908 "mon_parse.c"
    break;

  case 101: /* checkpoint_rules: CMD_UNTIL address_opt_range end_cmd  */
#line 422 "mon_parse.y"
                  {
                      mon_breakpoint_add_checkpoint((yyvsp[-1].range)[0], (yyvsp[-1].range)[1], TRUE, e_exec, TRUE);
                  }
#line 2916 "mon_parse.c"
    break;

  case 102: /* checkpoint_rules: CMD_UNTIL end_cmd  */
#line 426 "mon_parse.y"
                  { mon_breakpoint_print_checkpoints(); }
#line 2922 "mon_parse.c"
    break;

  case 103: /* checkpoint_control_rules: CMD_CHECKPT_ON checkpt_num end_cmd  */
#line 431 "mon_parse.y"
                          { mon_breakpoint_switch_checkpoint(e_ON, (yyvsp[-1].i)); }
#line 2928 "mon_parse.c"
    break;

  case 104: /* checkpoint_control_rules: CMD_CHECKPT_OFF checkpt_num end_cmd  */
#line 433 "mon_parse.y"
                          { mon_breakpoint_switch_checkpoint(e_OFF, (yyvsp[-1].i)); }
#line 2934 "mon_parse.c"
    break;

  case 105: /* checkpoint_control_rules: CMD_IGNORE checkpt_num end_cmd  */
#line 435 "mon_parse.y"
                          { mon_breakpoint_set_ignore_count((yyvsp[-1].i), -1); }
#line 2940 "mon_parse.c"
    break;

  case 106: /* checkpoint_control_rules: CMD_IGNORE checkpt_num opt_sep expression end_cmd  */
#line 437 "mon_parse.y"
                          { mon_breakpoint_set_ignore_count((yyvsp[-3].i), (yyvsp[-1].i)); }
#line 2946 "mon_parse.c"
    break;

  case 107: /* checkpoint_control_rules: CMD_DELETE checkpt_num end_cmd  */
#line 439 "mon_parse.y"
                          { mon_breakpoint_delete_checkpoint((yyvsp[-1].i)); }
#line 2952 "mon_parse.c"
    break;

  case 108: /* checkpoint_control_rules: CMD_DELETE end_cmd  */
#line 441 "mon_parse.y"
                          { mon_breakpoint_delete_checkpoint(-1); }
#line 2958 "mon_parse.c"
    break;

  case 109: /* checkpoint_control_rules: CMD_CONDITION checkpt_num IF cond_expr end_cmd  */
#line 443 "mon_parse.y"
                          { mon_breakpoint_set_checkpoint_condition((yyvsp[-3].i), (yyvsp[-1].cond_node)); }
#line 2964 "mon_parse.c"
    break;

  case 110: /* checkpoint_control_rules: CMD_COMMAND checkpt_num opt_sep STRING end_cmd  */
#line 445 "mon_parse.y"
                          { mon_breakpoint_set_checkpoint_command((yyvsp[-3].i), (yyvsp[-1].str)); }
#line 2970 "mon_parse.c"
    break;

  case 111: /* checkpoint_control_rules: CMD_COMMAND checkpt_num error end_cmd  */
#line 447 "mon_parse.y"
                          { return ERR_EXPECT_STRING; }
#line 2976 "mon_parse.c"
    break;

  case 112: /* monitor_state_rules: CMD_SIDEFX TOGGLE end_cmd  */
#line 451 "mon_parse.y"
                     { sidefx = (((yyvsp[-1].action) == e_TOGGLE) ? (sidefx ^ 1) : (yyvsp[-1].action)); }
#line 2982 "mon_parse.c"
    break;

  case 113: /* monitor_state_rules: CMD_SIDEFX end_cmd  */
#line 453 "mon_parse.y"
                     {
                         mon_out("I/O side effects are %s\n",
                                   sidefx ? "enabled" : "disabled");
                     }
#line 2991 "mon_parse.c"
    break;

  case 114: /* monitor_state_rules: CMD_RADIX RADIX_TYPE end_cmd  */
#line 458 "mon_parse.y"
                     { default_radix = (yyvsp[-1].rt); }
#line 2997 "mon_parse.c"
    break;

  case 115: /* monitor_state_rules: CMD_RADIX end_cmd  */
#line 460 "mon_parse.y"
                     {
                         const char *p;

                         if (default_radix == e_hexadecimal)
                             p = "Hexadecimal";
                         else if (default_radix == e_decimal)
                             p = "Decimal";
                         else if (default_radix == e_octal)
                             p = "Octal";
                         else if (default_radix == e_binary)
                             p = "Binary";
                         else
                             p = "Unknown";

                         mon_out("Default radix is %s\n", p);
                     }
#line 3018 "mon_parse.c"
    break;

  case 116: /* monitor_state_rules: CMD_DEVICE memspace end_cmd  */
#line 478 "mon_parse.y"
                     { monitor_change_device((yyvsp[-1].i)); }
#line 3024 "mon_parse.c"
    break;

  case 117: /* monitor_state_rules: CMD_EXPORT end_cmd  */
#line 480 "mon_parse.y"
                     { mon_export(); }
#line 3030 "mon_parse.c"
    break;

  case 118: /* monitor_state_rules: CMD_QUIT end_cmd  */
#line 482 "mon_parse.y"
                     { mon_quit(); YYACCEPT; }
#line 3036 "mon_parse.c"
    break;

  case 119: /* monitor_state_rules: CMD_EXIT end_cmd  */
#line 484 "mon_parse.y"
                     { exit_mon = 1; YYACCEPT; }
#line 3042 "mon_parse.c"
    break;

  case 120: /* monitor_misc_rules: CMD_DISK rest_of_line end_cmd  */
#line 488 "mon_parse.y"
                    { mon_drive_execute_disk_cmd((yyvsp[-1].str)); }
#line 3048 "mon_parse.c"
    break;

  case 121: /* monitor_misc_rules: CMD_PRINT expression end_cmd  */
#line 490 "mon_parse.y"
                    { mon_out("\t%d\n",(yyvsp[-1].i)); }
#line 3054 "mon_parse.c"
    break;

  case 122: /* monitor_misc_rules: CMD_HELP end_cmd  */
#line 492 "mon_parse.y"
                    { mon_command_print_help(NULL); }
#line 3060 "mon_parse.c"
    break;

  case 123: /* monitor_misc_rules: CMD_HELP rest_of_line end_cmd  */
#line 494 "mon_parse.y"
                    { mon_command_print_help((yyvsp[-1].str)); }
#line 3066 "mon_parse.c"
    break;

  case 124: /* monitor_misc_rules: CMD_SYSTEM rest_of_line end_cmd  */
#line 496 "mon_parse.y"
                    { printf("SYSTEM COMMAND: %s\n",(yyvsp[-1].str)); }
#line 3072 "mon_parse.c"
    break;

  case 125: /* monitor_misc_rules: CONVERT_OP expression end_cmd  */
#line 498 "mon_parse.y"
                    { mon_print_convert((yyvsp[-1].i)); }
#line 3078 "mon_parse.c"
    break;

  case 126: /* monitor_misc_rules: CMD_CHDIR rest_of_line end_cmd  */
#line 500 "mon_parse.y"
                    { mon_change_dir((yyvsp[-1].str)); }
#line 3084 "mon_parse.c"
    break;

  case 127: /* monitor_misc_rules: CMD_KEYBUF STRING end_cmd  */
#line 502 "mon_parse.y"
                    { mon_keyboard_feed((yyvsp[-1].str)); }
#line 3090 "mon_parse.c"
    break;

  case 128: /* monitor_misc_rules: CMD_BACKTRACE end_cmd  */
#line 504 "mon_parse.y"
                    { mon_backtrace(); }
#line 3096 "mon_parse.c"
    break;

  case 129: /* monitor_misc_rules: CMD_DIR opt_rest_of_line end_cmd  */
#line 506 "mon_parse.y"
                     { mon_show_dir((yyvsp[-1].str)); }
#line 3102 "mon_parse.c"
    break;

  case 130: /* monitor_misc_rules: CMD_PWD end_cmd  */
#line 508 "mon_parse.y"
                     { mon_show_pwd(); }
#line 3108 "mon_parse.c"
    break;

  case 131: /* monitor_misc_rules: CMD_SCREENSHOT filename end_cmd  */
#line 510 "mon_parse.y"
                    { mon_screenshot_save((yyvsp[-1].str),-1); }
#line 3114 "mon_parse.c"
    break;

  case 132: /* monitor_misc_rules: CMD_SCREENSHOT filename opt_sep expression end_cmd  */
#line 512 "mon_parse.y"
                    { mon_screenshot_save((yyvsp[-3].str),(yyvsp[-1].i)); }
#line 3120 "mon_parse.c"
    break;

  case 133: /* monitor_misc_rules: CMD_RESOURCE_GET STRING end_cmd  */
#line 514 "mon_parse.y"
                    { mon_resource_get((yyvsp[-1].str)); }
#line 3126 "mon_parse.c"
    break;

  case 134: /* monitor_misc_rules: CMD_RESOURCE_SET STRING STRING end_cmd  */
#line 516 "mon_parse.y"
                    { mon_resource_set((yyvsp[-2].str),(yyvsp[-1].str)); }
#line 3132 "mon_parse.c"
    break;

  case 135: /* monitor_misc_rules: CMD_MON_RESET end_cmd  */
#line 518 "mon_parse.y"
                    { mon_reset_machine(-1); }
#line 3138 "mon_parse.c"
    break;

  case 136: /* monitor_misc_rules: CMD_MON_RESET opt_sep expression end_cmd  */
#line 520 "mon_parse.y"
                    { mon_reset_machine((yyvsp[-1].i)); }
#line 3144 "mon_parse.c"
    break;

  case 137: /* monitor_misc_rules: CMD_TAPECTRL opt_sep expression end_cmd  */
#line 522 "mon_parse.y"
                    { mon_tape_ctrl((yyvsp[-1].i)); }
#line 3150 "mon_parse.c"
    break;

  case 138: /* monitor_misc_rules: CMD_CARTFREEZE end_cmd  */
#line 524 "mon_parse.y"
                    { mon_cart_freeze(); }
#line 3156 "mon_parse.c"
    break;

  case 139: /* monitor_misc_rules: CMD_COMMENT opt_rest_of_line end_cmd  */
#line 526 "mon_parse.y"
                     { }
#line 3162 "mon_parse.c"
    break;

  case 140: /* disk_rules: CMD_LOAD filename device_num opt_address end_cmd  */
#line 530 "mon_parse.y"
            { mon_file_load((yyvsp[-3].str), (yyvsp[-2].i), (yyvsp[-1].a), FALSE); }
#line 3168 "mon_parse.c"
    break;

  case 141: /* disk_rules: CMD_BLOAD filename device_num opt_address end_cmd  */
#line 532 "mon_parse.y"
            { mon_file_load((yyvsp[-3].str), (yyvsp[-2].i), (yyvsp[-1].a), TRUE); }
#line 3174 "mon_parse.c"
    break;

  case 142: /* disk_rules: CMD_SAVE filename device_num address_range end_cmd  */
#line 534 "mon_parse.y"
            { mon_file_save((yyvsp[-3].str), (yyvsp[-2].i), (yyvsp[-1].range)[0], (yyvsp[-1].range)[1], FALSE); }
#line 3180 "mon_parse.c"
    break;

  case 143: /* disk_rules: CMD_SAVE filename error  */
#line 536 "mon_parse.y"
            { return ERR_EXPECT_DEVICE_NUM; }
#line 3186 "mon_parse.c"
    break;

  case 144: /* disk_rules: CMD_SAVE filename device_num error  */
#line 538 "mon_parse.y"
            { return ERR_EXPECT_ADDRESS; }
#line 3192 "mon_parse.c"
    break;

  case 145: /* disk_rules: CMD_BSAVE filename device_num address_range end_cmd  */
#line 540 "mon_parse.y"
            { mon_file_save((yyvsp[-3].str), (yyvsp[-2].i), (yyvsp[-1].range)[0], (yyvsp[-1].range)[1], TRUE); }
#line 3198 "mon_parse.c"
    break;

  case 146: /* disk_rules: CMD_BSAVE filename device_num error  */
#line 542 "mon_parse.y"
            { return ERR_EXPECT_ADDRESS; }
#line 3204 "mon_parse.c"
    break;

  case 147: /* disk_rules: CMD_VERIFY filename device_num address end_cmd  */
#line 544 "mon_parse.y"
            { mon_file_verify((yyvsp[-3].str),(yyvsp[-2].i),(yyvsp[-1].a)); }
#line 3210 "mon_parse.c"
    break;

  case 148: /* disk_rules: CMD_VERIFY filename device_num error  */
#line 546 "mon_parse.y"
            { return ERR_EXPECT_ADDRESS; }
#line 3216 "mon_parse.c"
    break;

  case 149: /* disk_rules: CMD_BLOCK_READ expression expression opt_address end_cmd  */
#line 548 "mon_parse.y"
            { mon_drive_block_cmd(0,(yyvsp[-3].i),(yyvsp[-2].i),(yyvsp[-1].a)); }
#line 3222 "mon_parse.c"
    break;

  case 150: /* disk_rules: CMD_BLOCK_WRITE expression expression address end_cmd  */
#line 550 "mon_parse.y"
            { mon_drive_block_cmd(1,(yyvsp[-3].i),(yyvsp[-2].i),(yyvsp[-1].a)); }
#line 3228 "mon_parse.c"
    break;

  case 151: /* disk_rules: CMD_LIST end_cmd  */
#line 552 "mon_parse.y"
            { mon_drive_list(-1); }
#line 3234 "mon_parse.c"
    break;

  case 152: /* disk_rules: CMD_LIST device_num end_cmd  */
#line 554 "mon_parse.y"
            { mon_drive_list((yyvsp[-1].i)); }
#line 3240 "mon_parse.c"
    break;

  case 153: /* disk_rules: CMD_ATTACH filename expression end_cmd  */
#line 556 "mon_parse.y"
            { mon_attach((yyvsp[-2].str),(yyvsp[-1].i)); }
#line 3246 "mon_parse.c"
    break;

  case 154: /* disk_rules: CMD_DETACH expression end_cmd  */
#line 558 "mon_parse.y"
            { mon_detach((yyvsp[-1].i)); }
#line 3252 "mon_parse.c"
    break;

  case 155: /* disk_rules: CMD_AUTOSTART filename end_cmd  */
#line 560 "mon_parse.y"
            { mon_autostart((yyvsp[-1].str),0,1); }
#line 3258 "mon_parse.c"
    break;

  case 156: /* disk_rules: CMD_AUTOSTART filename opt_sep number end_cmd  */
#line 562 "mon_parse.y"
            { mon_autostart((yyvsp[-3].str),(yyvsp[-1].i),1); }
#line 3264 "mon_parse.c"
    break;

  case 157: /* disk_rules: CMD_AUTOLOAD filename end_cmd  */
#line 564 "mon_parse.y"
            { mon_autostart((yyvsp[-1].str),0,0); }
#line 3270 "mon_parse.c"
    break;

  case 158: /* disk_rules: CMD_AUTOLOAD filename opt_sep number end_cmd  */
#line 566 "mon_parse.y"
            { mon_autostart((yyvsp[-3].str),(yyvsp[-1].i),0); }
#line 3276 "mon_parse.c"
    break;

  case 159: /* cmd_file_rules: CMD_RECORD filename end_cmd  */
#line 570 "mon_parse.y"
                { mon_record_commands((yyvsp[-1].str)); }
#line 3282 "mon_parse.c"
    break;

  case 160: /* cmd_file_rules: CMD_MON_STOP end_cmd  */
#line 572 "mon_parse.y"
                { mon_end_recording(); }
#line 3288 "mon_parse.c"
    break;

  case 161: /* cmd_file_rules: CMD_PLAYBACK filename end_cmd  */
#line 574 "mon_parse.y"
                { mon_playback_init((yyvsp[-1].str)); }
#line 3294 "mon_parse.c"
    break;

  case 162: /* data_entry_rules: CMD_ENTER_DATA address data_list end_cmd  */
#line 578 "mon_parse.y"
                  { mon_memory_fill((yyvsp[-2].a), BAD_ADDR, (unsigned char *)(yyvsp[-1].str)); }
#line 3300 "mon_parse.c"
    break;

  case 163: /* data_entry_rules: CMD_ENTER_BIN_DATA end_cmd  */
#line 580 "mon_parse.y"
                  { printf("Not yet.\n"); }
#line 3306 "mon_parse.c"
    break;

  case 164: /* monitor_debug_rules: CMD_YYDEBUG end_cmd  */
#line 584 "mon_parse.y"
                     { yydebug = 1; }
#line 3312 "mon_parse.c"
    break;

  case 165: /* rest_of_line: R_O_L  */
#line 587 "mon_parse.y"
                    { (yyval.str) = (yyvsp[0].str); }
#line 3318 "mon_parse.c"
    break;

  case 166: /* opt_rest_of_line: R_O_L  */
#line 590 "mon_parse.y"
                        { (yyval.str) = (yyvsp[0].str); }
#line 3324 "mon_parse.c"
    break;

  case 167: /* opt_rest_of_line: %empty  */
#line 591 "mon_parse.y"
                    { (yyval.str) = NULL; }
#line 3330 "mon_parse.c"
    break;

  case 169: /* filename: error  */
#line 595 "mon_parse.y"
                { return ERR_EXPECT_FILENAME; }
#line 3336 "mon_parse.c"
    break;

  case 171: /* device_num: error  */
#line 599 "mon_parse.y"
              { return ERR_EXPECT_DEVICE_NUM; }
#line 3342 "mon_parse.c"
    break;

  case 172: /* opt_mem_op: MEM_OP  */
#line 602 "mon_parse.y"
                   { (yyval.i) = (yyvsp[0].i); }
#line 3348 "mon_parse.c"
    break;

  case 173: /* opt_mem_op: %empty  */
#line 603 "mon_parse.y"
            { (yyval.i) = e_load | e_store | e_exec; }
#line 3354 "mon_parse.c"
    break;

  case 174: /* register: MON_REGISTER  */
#line 606 "mon_parse.y"
                                { (yyval.i) = new_reg(default_memspace, (yyvsp[0].reg)); }
#line 3360 "mon_parse.c"
    break;

  case 175: /* register: memspace MON_REGISTER  */
#line 607 "mon_parse.y"
                                { (yyval.i) = new_reg((yyvsp[-1].i), (yyvsp[0].reg)); }
#line 3366 "mon_parse.c"
    break;

  case 178: /* reg_asgn: register EQUALS number  */
#line 615 "mon_parse.y"
          { (monitor_cpu_for_memspace[reg_memspace((yyvsp[-2].i))]->mon_register_set_val)(reg_memspace((yyvsp[-2].i)), reg_regid((yyvsp[-2].i)), (WORD) (yyvsp[0].i)); }
#line 3372 "mon_parse.c"
    break;

  case 179: /* checkpt_num: d_number  */
#line 618 "mon_parse.y"
                      { (yyval.i) = (yyvsp[0].i); }
#line 3378 "mon_parse.c"
    break;

  case 180: /* checkpt_num: error  */
#line 619 "mon_parse.y"
                   { return ERR_EXPECT_CHECKNUM; }
#line 3384 "mon_parse.c"
    break;

  case 182: /* address_opt_range: address  */
#line 623 "mon_parse.y"
                           { (yyval.range)[0] = (yyvsp[0].a); (yyval.range)[1] = BAD_ADDR; }
#line 3390 "mon_parse.c"
    break;

  case 183: /* address_range: address opt_sep address  */
#line 626 "mon_parse.y"
                                       { (yyval.range)[0] = (yyvsp[-2].a); (yyval.range)[1] = (yyvsp[0].a); }
#line 3396 "mon_parse.c"
    break;

  case 184: /* address_range: H_RANGE_GUESS  */
#line 628 "mon_parse.y"
               { if (resolve_range(e_default_space, (yyval.range), (yyvsp[0].str))) return ERR_ADDR_TOO_BIG; }
#line 3402 "mon_parse.c"
    break;

  case 185: /* address_range: memspace opt_sep H_RANGE_GUESS  */
#line 630 "mon_parse.y"
               { if (resolve_range((yyvsp[-2].i), (yyval.range), (yyvsp[0].str))) return ERR_ADDR_TOO_BIG; }
#line 3408 "mon_parse.c"
    break;

  case 186: /* opt_address: opt_sep address  */
#line 633 "mon_parse.y"
                             { (yyval.a) = (yyvsp[0].a); }
#line 3414 "mon_parse.c"
    break;

  case 187: /* opt_address: %empty  */
#line 634 "mon_parse.y"
             { (yyval.a) = BAD_ADDR; }
#line 3420 "mon_parse.c"
    break;

  case 188: /* address: memloc  */
#line 638 "mon_parse.y"
         {
             (yyval.a) = new_addr(e_default_space,(yyvsp[0].i));
             if (opt_asm) new_cmd = asm_mode = 1; 
         }
#line 3429 "mon_parse.c"
    break;

  case 189: /* address: memspace opt_sep memloc  */
#line 643 "mon_parse.y"
         {
             (yyval.a) = new_addr((yyvsp[-2].i), (yyvsp[0].i));
             if (opt_asm) new_cmd = asm_mode = 1; 
         }
#line 3438 "mon_parse.c"
    break;

  case 190: /* address: LABEL  */
#line 648 "mon_parse.y"
         {
             temp = mon_symbol_table_lookup_addr(e_default_space, (yyvsp[0].str));
             if (temp >= 0)
                 (yyval.a) = new_addr(e_default_space, temp);
             else
                 return ERR_UNDEFINED_LABEL;
         }
#line 3450 "mon_parse.c"
    break;

  case 193: /* memspace: MEM_COMP  */
#line 661 "mon_parse.y"
                   { (yyval.i) = e_comp_space; }
#line 3456 "mon_parse.c"
    break;

  case 194: /* memspace: MEM_DISK8  */
#line 662 "mon_parse.y"
                    { (yyval.i) = e_disk8_space; }
#line 3462 "mon_parse.c"
    break;

  case 195: /* memspace: MEM_DISK9  */
#line 663 "mon_parse.y"
                    { (yyval.i) = e_disk9_space; }
#line 3468 "mon_parse.c"
    break;

  case 196: /* memspace: MEM_DISK10  */
#line 664 "mon_parse.y"
                     { (yyval.i) = e_disk10_space; }
#line 3474 "mon_parse.c"
    break;

  case 197: /* memspace: MEM_DISK11  */
#line 665 "mon_parse.y"
                     { (yyval.i) = e_disk11_space; }
#line 3480 "mon_parse.c"
    break;

  case 198: /* memloc: memaddr  */
#line 668 "mon_parse.y"
                { (yyval.i) = (yyvsp[0].i); if (!CHECK_ADDR((yyvsp[0].i))) return ERR_ADDR_TOO_BIG; }
#line 3486 "mon_parse.c"
    break;

  case 199: /* memaddr: number  */
#line 670 "mon_parse.y"
                { (yyval.i) = (yyvsp[0].i); }
#line 3492 "mon_parse.c"
    break;

  case 200: /* expression: expression '+' expression  */
#line 672 "mon_parse.y"
                                      { (yyval.i) = (yyvsp[-2].i) + (yyvsp[0].i); }
#line 3498 "mon_parse.c"
    break;

  case 201: /* expression: expression '-' expression  */
#line 673 "mon_parse.y"
                                      { (yyval.i) = (yyvsp[-2].i) - (yyvsp[0].i); }
#line 3504 "mon_parse.c"
    break;

  case 202: /* expression: expression '*' expression  */
#line 674 "mon_parse.y"
                                      { (yyval.i) = (yyvsp[-2].i) * (yyvsp[0].i); }
#line 3510 "mon_parse.c"
    break;

  case 203: /* expression: expression '/' expression  */
#line 675 "mon_parse.y"
                                      { (yyval.i) = ((yyvsp[0].i)) ? ((yyvsp[-2].i) / (yyvsp[0].i)) : 1; }
#line 3516 "mon_parse.c"
    break;

  case 204: /* expression: '(' expression ')'  */
#line 676 "mon_parse.y"
                               { (yyval.i) = (yyvsp[-1].i); }
#line 3522 "mon_parse.c"
    break;

  case 205: /* expression: '(' expression error  */
#line 677 "mon_parse.y"
                                 { return ERR_MISSING_CLOSE_PAREN; }
#line 3528 "mon_parse.c"
    break;

  case 206: /* expression: value  */
#line 678 "mon_parse.y"
                  { (yyval.i) = (yyvsp[0].i); }
#line 3534 "mon_parse.c"
    break;

  case 207: /* cond_expr: cond_expr COMPARE_OP cond_expr  */
#line 682 "mon_parse.y"
           {
               (yyval.cond_node) = new_cond; (yyval.cond_node)->is_parenthized = FALSE;
               (yyval.cond_node)->child1 = (yyvsp[-2].cond_node); (yyval.cond_node)->child2 = (yyvsp[0].cond_node); (yyval.cond_node)->operation = (yyvsp[-1].cond_op);
           }
#line 3543 "mon_parse.c"
    break;

  case 208: /* cond_expr: cond_expr COMPARE_OP error  */
#line 687 "mon_parse.y"
           { return ERR_INCOMPLETE_COMPARE_OP; }
#line 3549 "mon_parse.c"
    break;

  case 209: /* cond_expr: L_PAREN cond_expr R_PAREN  */
#line 689 "mon_parse.y"
           { (yyval.cond_node) = (yyvsp[-1].cond_node); (yyval.cond_node)->is_parenthized = TRUE; }
#line 3555 "mon_parse.c"
    break;

  case 210: /* cond_expr: L_PAREN cond_expr error  */
#line 691 "mon_parse.y"
           { return ERR_MISSING_CLOSE_PAREN; }
#line 3561 "mon_parse.c"
    break;

  case 211: /* cond_expr: compare_operand  */
#line 693 "mon_parse.y"
           { (yyval.cond_node) = (yyvsp[0].cond_node); }
#line 3567 "mon_parse.c"
    break;

  case 212: /* compare_operand: register  */
#line 696 "mon_parse.y"
                          { (yyval.cond_node) = new_cond;
                            (yyval.cond_node)->operation = e_INV;
                            (yyval.cond_node)->is_parenthized = FALSE;
                            (yyval.cond_node)->reg_num = (yyvsp[0].i); (yyval.cond_node)->is_reg = TRUE;
                            (yyval.cond_node)->child1 = NULL; (yyval.cond_node)->child2 = NULL;
                          }
#line 3578 "mon_parse.c"
    break;

  case 213: /* compare_operand: number  */
#line 702 "mon_parse.y"
                          { (yyval.cond_node) = new_cond;
                            (yyval.cond_node)->operation = e_INV;
                            (yyval.cond_node)->is_parenthized = FALSE;
                            (yyval.cond_node)->value = (yyvsp[0].i); (yyval.cond_node)->is_reg = FALSE;
                            (yyval.cond_node)->child1 = NULL; (yyval.cond_node)->child2 = NULL;
                          }
#line 3589 "mon_parse.c"
    break;

  case 216: /* data_element: number  */
#line 714 "mon_parse.y"
                     { mon_add_number_to_buffer((yyvsp[0].i)); }
#line 3595 "mon_parse.c"
    break;

  case 217: /* data_element: STRING  */
#line 715 "mon_parse.y"
                     { mon_add_string_to_buffer((yyvsp[0].str)); }
#line 3601 "mon_parse.c"
    break;

  case 220: /* hunt_element: number  */
#line 722 "mon_parse.y"
                     { mon_add_number_to_buffer((yyvsp[0].i)); }
#line 3607 "mon_parse.c"
    break;

  case 221: /* hunt_element: MASK  */
#line 723 "mon_parse.y"
                     { mon_add_number_masked_to_buffer((yyvsp[0].i), 0x00); }
#line 3613 "mon_parse.c"
    break;

  case 222: /* hunt_element: STRING  */
#line 724 "mon_parse.y"
                     { mon_add_string_to_buffer((yyvsp[0].str)); }
#line 3619 "mon_parse.c"
    break;

  case 223: /* value: number  */
#line 727 "mon_parse.y"
              { (yyval.i) = (yyvsp[0].i); }
#line 3625 "mon_parse.c"
    break;

  case 224: /* value: register  */
#line 728 "mon_parse.y"
                { (yyval.i) = (monitor_cpu_for_memspace[reg_memspace((yyvsp[0].i))]->mon_register_get_val)(reg_memspace((yyvsp[0].i)), reg_regid((yyvsp[0].i))); }
#line 3631 "mon_parse.c"
    break;

  case 225: /* d_number: D_NUMBER  */
#line 731 "mon_parse.y"
                   { (yyval.i) = (yyvsp[0].i); }
#line 3637 "mon_parse.c"
    break;

  case 226: /* d_number: B_NUMBER_GUESS  */
#line 732 "mon_parse.y"
                         { (yyval.i) = strtol((yyvsp[0].str), NULL, 10); }
#line 3643 "mon_parse.c"
    break;

  case 227: /* d_number: O_NUMBER_GUESS  */
#line 733 "mon_parse.y"
                         { (yyval.i) = strtol((yyvsp[0].str), NULL, 10); }
#line 3649 "mon_parse.c"
    break;

  case 228: /* d_number: D_NUMBER_GUESS  */
#line 734 "mon_parse.y"
                         { (yyval.i) = strtol((yyvsp[0].str), NULL, 10); }
#line 3655 "mon_parse.c"
    break;

  case 229: /* guess_default: B_NUMBER_GUESS  */
#line 737 "mon_parse.y"
                              { (yyval.i) = resolve_datatype(B_NUMBER,(yyvsp[0].str)); }
#line 3661 "mon_parse.c"
    break;

  case 230: /* guess_default: O_NUMBER_GUESS  */
#line 738 "mon_parse.y"
                              { (yyval.i) = resolve_datatype(O_NUMBER,(yyvsp[0].str)); }
#line 3667 "mon_parse.c"
    break;

  case 231: /* guess_default: D_NUMBER_GUESS  */
#line 739 "mon_parse.y"
                              { (yyval.i) = resolve_datatype(D_NUMBER,(yyvsp[0].str)); }
#line 3673 "mon_parse.c"
    break;

  case 232: /* number: H_NUMBER  */
#line 742 "mon_parse.y"
                 { (yyval.i) = (yyvsp[0].i); }
#line 3679 "mon_parse.c"
    break;

  case 233: /* number: D_NUMBER  */
#line 743 "mon_parse.y"
                 { (yyval.i) = (yyvsp[0].i); }
#line 3685 "mon_parse.c"
    break;

  case 234: /* number: O_NUMBER  */
#line 744 "mon_parse.y"
                 { (yyval.i) = (yyvsp[0].i); }
#line 3691 "mon_parse.c"
    break;

  case 235: /* number: B_NUMBER  */
#line 745 "mon_parse.y"
                 { (yyval.i) = (yyvsp[0].i); }
#line 3697 "mon_parse.c"
    break;

  case 236: /* number: guess_default  */
#line 746 "mon_parse.y"
                      { (yyval.i) = (yyvsp[0].i); }
#line 3703 "mon_parse.c"
    break;

  case 240: /* assembly_instruction: OPCODE asm_operand_mode  */
#line 754 "mon_parse.y"
                                              { (yyval.i) = 0;
                                                if ((yyvsp[-1].str)) {
                                                    (monitor_cpu_for_memspace[default_memspace]->mon_assemble_instr)((yyvsp[-1].str), (yyvsp[0].i));
                                                } else {
                                                    new_cmd = 1;
                                                    asm_mode = 0;
                                                }
                                                opt_asm = 0;
                                              }
#line 3717 "mon_parse.c"
    break;

  case 242: /* post_assemble: assembly_instr_list  */
#line 765 "mon_parse.y"
                                   { asm_mode = 0; }
#line 3723 "mon_parse.c"
    break;

  case 243: /* asm_operand_mode: ARG_IMMEDIATE number  */
#line 768 "mon_parse.y"
                                       { if ((yyvsp[0].i) > 0xff)
                          (yyval.i) = join_ints(ASM_ADDR_MODE_IMMEDIATE_16,(yyvsp[0].i));
                        else
                          (yyval.i) = join_ints(ASM_ADDR_MODE_IMMEDIATE,(yyvsp[0].i)); }
#line 3732 "mon_parse.c"
    break;

  case 244: /* asm_operand_mode: number  */
#line 772 "mon_parse.y"
           { if ((yyvsp[0].i) < 0x100)
               (yyval.i) = join_ints(ASM_ADDR_MODE_ZERO_PAGE,(yyvsp[0].i));
             else
               (yyval.i) = join_ints(ASM_ADDR_MODE_ABSOLUTE,(yyvsp[0].i));
           }
#line 3742 "mon_parse.c"
    break;

  case 245: /* asm_operand_mode: number COMMA REG_X  */
#line 777 "mon_parse.y"
                        { if ((yyvsp[-2].i) < 0x100)
                            (yyval.i) = join_ints(ASM_ADDR_MODE_ZERO_PAGE_X,(yyvsp[-2].i));
                          else
                            (yyval.i) = join_ints(ASM_ADDR_MODE_ABSOLUTE_X,(yyvsp[-2].i));
                        }
#line 3752 "mon_parse.c"
    break;

  case 246: /* asm_operand_mode: number COMMA REG_Y  */
#line 782 "mon_parse.y"
                        { if ((yyvsp[-2].i) < 0x100)
                            (yyval.i) = join_ints(ASM_ADDR_MODE_ZERO_PAGE_Y,(yyvsp[-2].i));
                          else
                            (yyval.i) = join_ints(ASM_ADDR_MODE_ABSOLUTE_Y,(yyvsp[-2].i));
                        }
#line 3762 "mon_parse.c"
    break;

  case 247: /* asm_operand_mode: L_PAREN number R_PAREN  */
#line 788 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_ABS_INDIRECT,(yyvsp[-1].i)); }
#line 3768 "mon_parse.c"
    break;

  case 248: /* asm_operand_mode: L_PAREN number COMMA REG_X R_PAREN  */
#line 790 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_INDIRECT_X,(yyvsp[-3].i)); }
#line 3774 "mon_parse.c"
    break;

  case 249: /* asm_operand_mode: L_PAREN number R_PAREN COMMA REG_Y  */
#line 792 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_INDIRECT_Y,(yyvsp[-3].i)); }
#line 3780 "mon_parse.c"
    break;

  case 250: /* asm_operand_mode: L_PAREN REG_BC R_PAREN  */
#line 793 "mon_parse.y"
                           { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_IND_BC,0); }
#line 3786 "mon_parse.c"
    break;

  case 251: /* asm_operand_mode: L_PAREN REG_DE R_PAREN  */
#line 794 "mon_parse.y"
                           { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_IND_DE,0); }
#line 3792 "mon_parse.c"
    break;

  case 252: /* asm_operand_mode: L_PAREN REG_HL R_PAREN  */
#line 795 "mon_parse.y"
                           { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_IND_HL,0); }
#line 3798 "mon_parse.c"
    break;

  case 253: /* asm_operand_mode: L_PAREN REG_IX R_PAREN  */
#line 796 "mon_parse.y"
                           { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_IND_IX,0); }
#line 3804 "mon_parse.c"
    break;

  case 254: /* asm_operand_mode: L_PAREN REG_IY R_PAREN  */
#line 797 "mon_parse.y"
                           { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_IND_IY,0); }
#line 3810 "mon_parse.c"
    break;

  case 255: /* asm_operand_mode: L_PAREN REG_SP R_PAREN  */
#line 798 "mon_parse.y"
                           { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_IND_SP,0); }
#line 3816 "mon_parse.c"
    break;

  case 256: /* asm_operand_mode: L_PAREN number R_PAREN COMMA REG_A  */
#line 800 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_ABSOLUTE_A,(yyvsp[-3].i)); }
#line 3822 "mon_parse.c"
    break;

  case 257: /* asm_operand_mode: L_PAREN number R_PAREN COMMA REG_HL  */
#line 802 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_ABSOLUTE_HL,(yyvsp[-3].i)); }
#line 3828 "mon_parse.c"
    break;

  case 258: /* asm_operand_mode: L_PAREN number R_PAREN COMMA REG_IX  */
#line 804 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_ABSOLUTE_IX,(yyvsp[-3].i)); }
#line 3834 "mon_parse.c"
    break;

  case 259: /* asm_operand_mode: L_PAREN number R_PAREN COMMA REG_IY  */
#line 806 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_ABSOLUTE_IY,(yyvsp[-3].i)); }
#line 3840 "mon_parse.c"
    break;

  case 260: /* asm_operand_mode: %empty  */
#line 807 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_IMPLIED,0); }
#line 3846 "mon_parse.c"
    break;

  case 261: /* asm_operand_mode: REG_A  */
#line 808 "mon_parse.y"
          { (yyval.i) = join_ints(ASM_ADDR_MODE_ACCUMULATOR,0); }
#line 3852 "mon_parse.c"
    break;

  case 262: /* asm_operand_mode: REG_B  */
#line 809 "mon_parse.y"
          { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_B,0); }
#line 3858 "mon_parse.c"
    break;

  case 263: /* asm_operand_mode: REG_C  */
#line 810 "mon_parse.y"
          { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_C,0); }
#line 3864 "mon_parse.c"
    break;

  case 264: /* asm_operand_mode: REG_D  */
#line 811 "mon_parse.y"
          { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_D,0); }
#line 3870 "mon_parse.c"
    break;

  case 265: /* asm_operand_mode: REG_E  */
#line 812 "mon_parse.y"
          { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_E,0); }
#line 3876 "mon_parse.c"
    break;

  case 266: /* asm_operand_mode: REG_H  */
#line 813 "mon_parse.y"
          { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_H,0); }
#line 3882 "mon_parse.c"
    break;

  case 267: /* asm_operand_mode: REG_IXH  */
#line 814 "mon_parse.y"
            { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_IXH,0); }
#line 3888 "mon_parse.c"
    break;

  case 268: /* asm_operand_mode: REG_IYH  */
#line 815 "mon_parse.y"
            { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_IYH,0); }
#line 3894 "mon_parse.c"
    break;

  case 269: /* asm_operand_mode: REG_L  */
#line 816 "mon_parse.y"
          { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_L,0); }
#line 3900 "mon_parse.c"
    break;

  case 270: /* asm_operand_mode: REG_IXL  */
#line 817 "mon_parse.y"
            { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_IXL,0); }
#line 3906 "mon_parse.c"
    break;

  case 271: /* asm_operand_mode: REG_IYL  */
#line 818 "mon_parse.y"
            { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_IYL,0); }
#line 3912 "mon_parse.c"
    break;

  case 272: /* asm_operand_mode: REG_AF  */
#line 819 "mon_parse.y"
           { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_AF,0); }
#line 3918 "mon_parse.c"
    break;

  case 273: /* asm_operand_mode: REG_BC  */
#line 820 "mon_parse.y"
           { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_BC,0); }
#line 3924 "mon_parse.c"
    break;

  case 274: /* asm_operand_mode: REG_DE  */
#line 821 "mon_parse.y"
           { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_DE,0); }
#line 3930 "mon_parse.c"
    break;

  case 275: /* asm_operand_mode: REG_HL  */
#line 822 "mon_parse.y"
           { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_HL,0); }
#line 3936 "mon_parse.c"
    break;

  case 276: /* asm_operand_mode: REG_IX  */
#line 823 "mon_parse.y"
           { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_IX,0); }
#line 3942 "mon_parse.c"
    break;

  case 277: /* asm_operand_mode: REG_IY  */
#line 824 "mon_parse.y"
           { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_IY,0); }
#line 3948 "mon_parse.c"
    break;

  case 278: /* asm_operand_mode: REG_SP  */
#line 825 "mon_parse.y"
           { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_SP,0); }
#line 3954 "mon_parse.c"
    break;


#line 3958 "mon_parse.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 829 "mon_parse.y"


void parse_and_execute_line(char *input)
{
   char *temp_buf;
   int i, rc;

   temp_buf = lib_malloc(strlen(input) + 3);
   strcpy(temp_buf,input);
   i = (int)strlen(input);
   temp_buf[i++] = '\n';
   temp_buf[i++] = '\0';
   temp_buf[i++] = '\0';

   make_buffer(temp_buf);
   if ( (rc =yyparse()) != 0) {
       mon_out("ERROR -- ");
       switch(rc) {
         case ERR_BAD_CMD:
           mon_out("Bad command:\n");
           break;
         case ERR_RANGE_BAD_START:
           mon_out("Bad first address in range:\n");
           break;
         case ERR_RANGE_BAD_END:
           mon_out("Bad second address in range:\n");
           break;
         case ERR_EXPECT_CHECKNUM:
           mon_out("Checkpoint number expected:\n");
           break;
         case ERR_EXPECT_END_CMD:
           mon_out("Unexpected token:\n");
           break;
         case ERR_MISSING_CLOSE_PAREN:
           mon_out("')' expected:\n");
           break;
         case ERR_INCOMPLETE_COMPARE_OP:
           mon_out("Compare operation missing an operand:\n");
           break;
         case ERR_EXPECT_FILENAME:
           mon_out("Expecting a filename:\n");
           break;
         case ERR_ADDR_TOO_BIG:
           mon_out("Address too large:\n");
           break;
         case ERR_IMM_TOO_BIG:
           mon_out("Immediate argument too large:\n");
           break;
         case ERR_EXPECT_STRING:
           mon_out("Expecting a string.\n");
           break;
         case ERR_UNDEFINED_LABEL:
           mon_out("Found an undefined label.\n");
           break;
         case ERR_EXPECT_DEVICE_NUM:
           mon_out("Expecting a device number.\n");
           break;
         case ERR_EXPECT_ADDRESS:
           mon_out("Expecting an address.\n");
           break;
         case ERR_ILLEGAL_INPUT:
         default:
           mon_out("Wrong syntax:\n");
       }
       mon_out("  %s\n", input);
       for (i = 0; i < last_len; i++)
           mon_out(" ");
       mon_out("  ^\n");
       asm_mode = 0;
       new_cmd = 1;
   }
   lib_free(temp_buf);
   free_buffer();
}

static int yyerror(char *s)
{
   fprintf(stderr, "ERR:%s\n", s);
   return 0;
}

static int resolve_datatype(unsigned guess_type, const char *num)
{
   /* FIXME: Handle cases when default type is non-numerical */
   if (default_radix == e_hexadecimal) {
       return strtol(num, NULL, 16);
   }

   if ((guess_type == D_NUMBER) || (default_radix == e_decimal)) {
       return strtol(num, NULL, 10);
   }

   if ((guess_type == O_NUMBER) || (default_radix == e_octal)) {
       return strtol(num, NULL, 8);
   }

   return strtol(num, NULL, 2);
}

/*
 * Resolve a character sequence containing 8 hex digits like "08001000". 
 * This could be a lazy version of "0800 1000". If the default radix is not
 * hexadecimal, we handle it like a ordinary number, in the latter case there
 * is only one number in the range.
 */
static int resolve_range(enum t_memspace memspace, MON_ADDR range[2], 
                         const char *num)
{
    char start[5];
    char end[5];
    long sa;

    range[1] = BAD_ADDR;

    switch (default_radix)
    {
    case e_hexadecimal:
        /* checked twice, but as the code must have exactly 8 digits: */
        if (strlen(num) == 8) {
            memcpy(start, num, 4);
            start[4] = '\0';
            memcpy(end, num + 4, 4);
            end[4] = '\0';
            sa = strtol(start, NULL, 16);
            range[1] = new_addr(memspace, strtol(end, NULL, 16));
        }
        else
            sa = strtol(num, NULL, 16);
        break;

    case e_decimal:
       sa = strtol(num, NULL, 10);
       break;

    case e_octal:
       sa = strtol(num, NULL, 8);
       break;

    default:
       sa = strtol(num, NULL, 2);
    }

    if (!CHECK_ADDR(sa))
        return ERR_ADDR_TOO_BIG;

    range[0] = new_addr(memspace, sa);
    return 0;
}

/* If we want 'quit' for OS/2 I couldn't leave the emulator by calling exit(0)
   So I decided to skip this (I think it's unnecessary for OS/2 */
static void mon_quit(void)
{
#ifdef OS2
    /* same as "quit" */
    exit_mon = 1; 
#else
    exit_mon = 2;
#endif
}

