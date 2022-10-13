/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

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

#line 377 "mon_parse.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_MON_PARSE_H_INCLUDED  */
