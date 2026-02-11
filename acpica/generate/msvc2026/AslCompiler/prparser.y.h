
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
     EXPOP_EOF = 258,
     EXPOP_NEW_LINE = 259,
     EXPOP_NUMBER = 260,
     EXPOP_HEX_NUMBER = 261,
     EXPOP_RESERVED1 = 262,
     EXPOP_RESERVED2 = 263,
     EXPOP_PAREN_OPEN = 264,
     EXPOP_PAREN_CLOSE = 265,
     EXPOP_LOGICAL_OR = 266,
     EXPOP_LOGICAL_AND = 267,
     EXPOP_OR = 268,
     EXPOP_XOR = 269,
     EXPOP_AND = 270,
     EXPOP_NOT_EQUAL = 271,
     EXPOP_EQUAL = 272,
     EXPOP_LESS_EQUAL = 273,
     EXPOP_GREATER_EQUAL = 274,
     EXPOP_LESS = 275,
     EXPOP_GREATER = 276,
     EXPOP_SHIFT_LEFT = 277,
     EXPOP_SHIFT_RIGHT = 278,
     EXPOP_SUBTRACT = 279,
     EXPOP_ADD = 280,
     EXPOP_MODULO = 281,
     EXPOP_DIVIDE = 282,
     EXPOP_MULTIPLY = 283,
     EXPOP_LOGICAL_NOT = 284,
     EXPOP_ONES_COMPLIMENT = 285,
     EXPOP_DEFINE = 286,
     EXPOP_IDENTIFIER = 287
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{


     UINT64                 value;
     UINT32                 op;
     char                   *str;



} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE PrParserlval;


