
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     VOID = 259,
     CONST = 260,
     IF = 261,
     ELSE = 262,
     WHILE = 263,
     BREAK = 264,
     CONTINUE = 265,
     RETURN = 266,
     ID = 267,
     OCTAL_CONST = 268,
     HEX_CONST = 269,
     DEC_CONST = 270,
     ASSIGN = 271,
     OR = 272,
     AND = 273,
     EQNEQ = 274,
     CMP = 275,
     ADDSUB = 276,
     MULDIVSUR = 277
   };
#endif
/* Tokens.  */
#define INT 258
#define VOID 259
#define CONST 260
#define IF 261
#define ELSE 262
#define WHILE 263
#define BREAK 264
#define CONTINUE 265
#define RETURN 266
#define ID 267
#define OCTAL_CONST 268
#define HEX_CONST 269
#define DEC_CONST 270
#define ASSIGN 271
#define OR 272
#define AND 273
#define EQNEQ 274
#define CMP 275
#define ADDSUB 276
#define MULDIVSUR 277




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 9 "test.y"

    int     num;
    char*   str;
    struct ASTnode* node; /*"struct" is indispensable*/



/* Line 1676 of yacc.c  */
#line 104 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


