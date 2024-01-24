
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
     VAR = 258,
     ARR = 259,
     INT = 260,
     STR = 261,
     READ = 262,
     IF = 263,
     ELSE = 264,
     DO = 265,
     WHILE = 266,
     PRINT = 267,
     PLUS = 268,
     MINUS = 269,
     TIMES = 270,
     DIV = 271,
     MOD = 272,
     BIGGEREQ = 273,
     LESSEQ = 274,
     BIGGER = 275,
     LESS = 276,
     EQQ = 277,
     EQ = 278,
     NEQ = 279,
     SQBRACKETOPEN = 280,
     SQBRACKETCLOSE = 281,
     OPEN = 282,
     CLOSE = 283,
     BRACKETOPEN = 284,
     BRACKETCLOSE = 285,
     DOT = 286,
     COMMA = 287,
     COLON = 288,
     SEMICOLON = 289,
     IDENTIFIER = 290,
     INTCONSTANT = 291,
     STRINGCONSTANT = 292
   };
#endif
/* Tokens.  */
#define VAR 258
#define ARR 259
#define INT 260
#define STR 261
#define READ 262
#define IF 263
#define ELSE 264
#define DO 265
#define WHILE 266
#define PRINT 267
#define PLUS 268
#define MINUS 269
#define TIMES 270
#define DIV 271
#define MOD 272
#define BIGGEREQ 273
#define LESSEQ 274
#define BIGGER 275
#define LESS 276
#define EQQ 277
#define EQ 278
#define NEQ 279
#define SQBRACKETOPEN 280
#define SQBRACKETCLOSE 281
#define OPEN 282
#define CLOSE 283
#define BRACKETOPEN 284
#define BRACKETCLOSE 285
#define DOT 286
#define COMMA 287
#define COLON 288
#define SEMICOLON 289
#define IDENTIFIER 290
#define INTCONSTANT 291
#define STRINGCONSTANT 292




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


