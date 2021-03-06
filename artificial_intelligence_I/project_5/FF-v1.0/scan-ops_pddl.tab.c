
/*  A Bison parser, made from scan-ops_pddl.y
 by  GNU Bison version 1.25
  */

#define YYBISON 1  /* Identify Bison output.  */

#define yyparse ops_pddlparse
#define yylex ops_pddllex
#define yyerror ops_pddlerror
#define yylval ops_pddllval
#define yychar ops_pddlchar
#define yydebug ops_pddldebug
#define yynerrs ops_pddlnerrs
#define	DEFINE_TOK	258
#define	DOMAIN_TOK	259
#define	REQUIREMENTS_TOK	260
#define	TYPES_TOK	261
#define	EITHER_TOK	262
#define	CONSTANTS_TOK	263
#define	PREDICATES_TOK	264
#define	ACTION_TOK	265
#define	VARS_TOK	266
#define	CONTEXT_TOK	267
#define	IMPLIES_TOK	268
#define	PRECONDITION_TOK	269
#define	PARAMETERS_TOK	270
#define	EFFECT_TOK	271
#define	AND_TOK	272
#define	NOT_TOK	273
#define	WHEN_TOK	274
#define	FORALL_TOK	275
#define	IMPLY_TOK	276
#define	OR_TOK	277
#define	EXISTS_TOK	278
#define	EQUAL_TOK	279
#define	NAME	280
#define	VARIABLE	281
#define	TYPE	282
#define	OPEN_PAREN	283
#define	CLOSE_PAREN	284

#line 21 "scan-ops_pddl.y"

#ifdef YYDEBUG
  extern int yydebug=1;
#endif


#include <stdio.h>
#include <string.h> 
#include "ff.h"
#include "memory.h"
#include "parse.h"


#ifndef SCAN_ERR
#define SCAN_ERR
#define DOMDEF_EXPECTED            0
#define DOMAIN_EXPECTED            1
#define DOMNAME_EXPECTED           2
#define LBRACKET_EXPECTED          3
#define RBRACKET_EXPECTED          4
#define DOMDEFS_EXPECTED           5
#define REQUIREM_EXPECTED          6
#define TYPEDLIST_EXPECTED         7
#define LITERAL_EXPECTED           8
#define PRECONDDEF_UNCORRECT       9
#define TYPEDEF_EXPECTED          10
#define CONSTLIST_EXPECTED        11
#define PREDDEF_EXPECTED          12 
#define NAME_EXPECTED             13
#define VARIABLE_EXPECTED         14
#define ACTIONFUNCTOR_EXPECTED    15
#define ATOM_FORMULA_EXPECTED     16
#define EFFECT_DEF_EXPECTED       17
#define NEG_FORMULA_EXPECTED      18
#define NOT_SUPPORTED             19
#define ACTION                    20
#endif


#define NAME_STR "name\0"
#define VARIABLE_STR "variable\0"
#define STANDARD_TYPE "OBJECT\0"
 

static char *serrmsg[] = {
  "domain definition expected",
  "'domain' expected",
  "domain name expected",
  "'(' expected",
  "')' expected",
  "additional domain definitions expected",
  "requirements (e.g. ':STRIPS') expected",
  "typed list of <%s> expected",
  "literal expected",
  "uncorrect precondition definition",
  "type definition expected",
  "list of constants expected",
  "predicate definition expected",
  "<name> expected",
  "<variable> expected",
  "action functor expected",
  "atomic formula expected",
  "effect definition expected",
  "negated atomic formula expected",
  "requirement %s not supported by this IPP version",  
  "action definition is not correct",
  NULL
};


/* void opserr( int errno, char *par ); */


static int sact_err;
static char *sact_err_par = NULL;
static PlOperator *scur_op = NULL;
static Bool sis_negated = FALSE;


int supported( char *str )

{

  int i;
  char * sup[] = { ":STRIPS", ":NEGATION", ":EQUALITY",":TYPING", 
		   ":CONDITIONAL-EFFECTS", ":DISJUNCTIVE-PRECONDITIONS", 
		   ":EXISTENTIAL-PRECONDITIONS", ":UNIVERSAL-PRECONDITIONS", 
		   ":QUANTIFIED-PRECONDITIONS", ":ADL",
		   NULL };     

  for (i=0; NULL != sup[i]; i++) {
    if ( SAME == strcmp(sup[i], str) ) {
      return TRUE;
    }
  }
  
  return FALSE;

}


#line 127 "scan-ops_pddl.y"
typedef union {

  char string[MAX_LENGTH];
  char *pstring;
  PlNode *pPlNode;
  FactList *pFactList;
  TokenList *pTokenList;

} YYSTYPE;
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		156
#define	YYFLAG		-32768
#define	YYNTBASE	30

#define YYTRANSLATE(x) ((unsigned)(x) <= 284 ? yytranslate[x] : 68)

static const char yytranslate[] = {     0,
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
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     1,     4,     5,    11,    16,    18,    21,    24,    27,
    30,    33,    34,    40,    41,    42,    49,    50,    51,    59,
    60,    61,    65,    66,    72,    73,    79,    80,    81,    90,
    91,    96,    97,   103,   104,   109,   110,   115,   117,   122,
   127,   132,   138,   146,   154,   155,   158,   160,   165,   170,
   178,   184,   185,   188,   193,   195,   200,   201,   204,   206,
   208,   210,   213,   215,   217,   218,   224,   228,   231,   232,
   238,   242
};

static const short yyrhs[] = {    -1,
    31,    32,     0,     0,    28,     3,    34,    33,    35,     0,
    28,     4,    25,    29,     0,    29,     0,    40,    35,     0,
    47,    35,     0,    45,    35,     0,    49,    35,     0,    36,
    35,     0,     0,    28,     9,    38,    37,    29,     0,     0,
     0,    28,    25,    67,    29,    39,    38,     0,     0,     0,
    28,     5,    41,    25,    42,    43,    29,     0,     0,     0,
    25,    44,    43,     0,     0,    28,     6,    46,    66,    29,
     0,     0,    28,     8,    48,    66,    29,     0,     0,     0,
    28,    10,    50,    25,    51,    52,    53,    29,     0,     0,
    15,    28,    67,    29,     0,     0,    11,    28,    67,    29,
    53,     0,     0,    14,    56,    54,    53,     0,     0,    16,
    58,    55,    53,     0,    60,     0,    28,    17,    57,    29,
     0,    28,    22,    57,    29,     0,    28,    18,    56,    29,
     0,    28,    21,    56,    56,    29,     0,    28,    23,    28,
    67,    29,    56,    29,     0,    28,    20,    28,    67,    29,
    56,    29,     0,     0,    56,    57,     0,    60,     0,    28,
    17,    59,    29,     0,    28,    18,    58,    29,     0,    28,
    20,    28,    67,    29,    58,    29,     0,    28,    19,    56,
    58,    29,     0,     0,    58,    59,     0,    28,    18,    61,
    29,     0,    61,     0,    28,    65,    62,    29,     0,     0,
    63,    62,     0,    25,     0,    26,     0,    25,     0,    25,
    64,     0,    25,     0,    24,     0,     0,    25,     7,    64,
    29,    66,     0,    25,    27,    66,     0,    25,    66,     0,
     0,    26,     7,    64,    29,    67,     0,    26,    27,    67,
     0,    26,    67,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   182,   187,   192,   200,   209,   219,   221,   223,   225,   227,
   229,   235,   240,   244,   247,   282,   286,   292,   298,   303,
   305,   314,   318,   323,   332,   337,   347,   353,   356,   365,
   370,   385,   387,   405,   411,   411,   417,   426,   439,   445,
   451,   457,   467,   509,   550,   555,   568,   581,   587,   593,
   630,   649,   653,   665,   671,   680,   691,   694,   705,   711,
   721,   728,   740,   746,   756,   759,   819,   831,   854,   857,
   916,   928
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","DEFINE_TOK",
"DOMAIN_TOK","REQUIREMENTS_TOK","TYPES_TOK","EITHER_TOK","CONSTANTS_TOK","PREDICATES_TOK",
"ACTION_TOK","VARS_TOK","CONTEXT_TOK","IMPLIES_TOK","PRECONDITION_TOK","PARAMETERS_TOK",
"EFFECT_TOK","AND_TOK","NOT_TOK","WHEN_TOK","FORALL_TOK","IMPLY_TOK","OR_TOK",
"EXISTS_TOK","EQUAL_TOK","NAME","VARIABLE","TYPE","OPEN_PAREN","CLOSE_PAREN",
"file","@1","domain_definition","@2","domain_name","optional_domain_defs","predicates_def",
"@3","predicates_list","@4","require_def","@5","@6","require_key_star","@7",
"types_def","@8","constants_def","@9","action_def","@10","@11","param_def","action_def_body",
"@12","@13","adl_goal_description","adl_goal_description_star","adl_effect",
"adl_effect_star","literal_term","atomic_formula_term","term_star","term","name_plus",
"predicate","typed_list_name","typed_list_variable", NULL
};
#endif

static const short yyr1[] = {     0,
    31,    30,    33,    32,    34,    35,    35,    35,    35,    35,
    35,    37,    36,    38,    39,    38,    41,    42,    40,    43,
    44,    43,    46,    45,    48,    47,    50,    51,    49,    52,
    52,    53,    53,    54,    53,    55,    53,    56,    56,    56,
    56,    56,    56,    56,    57,    57,    58,    58,    58,    58,
    58,    59,    59,    60,    60,    61,    62,    62,    63,    63,
    64,    64,    65,    65,    66,    66,    66,    66,    67,    67,
    67,    67
};

static const short yyr2[] = {     0,
     0,     2,     0,     5,     4,     1,     2,     2,     2,     2,
     2,     0,     5,     0,     0,     6,     0,     0,     7,     0,
     0,     3,     0,     5,     0,     5,     0,     0,     8,     0,
     4,     0,     5,     0,     4,     0,     4,     1,     4,     4,
     4,     5,     7,     7,     0,     2,     1,     4,     4,     7,
     5,     0,     2,     4,     1,     4,     0,     2,     1,     1,
     1,     2,     1,     1,     0,     5,     3,     2,     0,     5,
     3,     2
};

static const short yydefact[] = {     1,
     0,     0,     2,     0,     0,     3,     0,     0,     0,     0,
     6,     4,     0,     0,     0,     0,     0,     5,    17,    23,
    25,    14,    27,    11,     7,     9,     8,    10,     0,    65,
    65,     0,    12,     0,    18,    65,     0,     0,    69,     0,
    28,    20,     0,    65,    68,    24,    26,    69,     0,    13,
    30,    21,     0,    61,     0,    67,     0,    69,    72,    15,
     0,    32,    20,    19,    62,    65,     0,    71,    14,    69,
     0,     0,     0,     0,    22,    66,    69,    16,     0,    69,
     0,    34,    38,    55,     0,    36,    47,    29,    70,    31,
     0,    45,     0,     0,     0,    45,     0,    64,    63,    57,
    32,    52,     0,     0,     0,    32,    32,    45,     0,     0,
     0,    69,     0,     0,    69,    59,    60,     0,    57,    35,
    52,     0,     0,     0,    69,    37,    33,    46,    39,    41,
    54,     0,     0,    40,     0,    56,    58,    53,    48,    49,
     0,     0,     0,    42,     0,    51,     0,     0,     0,     0,
    44,    43,    50,     0,     0,     0
};

static const short yydefgoto[] = {   154,
     1,     3,     8,     6,    12,    13,    40,    33,    69,    14,
    29,    42,    53,    63,    15,    30,    16,    31,    17,    34,
    51,    62,    74,   101,   106,   108,   109,   121,   122,    83,
    84,   118,   119,    55,   100,    37,    49
};

static const short yypact[] = {-32768,
   -17,    13,-32768,     8,    22,-32768,    23,    -1,    18,    51,
-32768,-32768,    -1,    -1,    -1,    -1,    -1,-32768,-32768,-32768,
-32768,    26,-32768,-32768,-32768,-32768,-32768,-32768,    25,    33,
    33,    37,-32768,    38,-32768,    -4,    45,    53,    54,    55,
-32768,    66,    67,    33,-32768,-32768,-32768,    -2,    64,-32768,
    36,-32768,    68,    67,    69,-32768,    67,    54,-32768,-32768,
    71,    65,    66,-32768,-32768,    33,    72,-32768,    26,    54,
    74,    75,    76,    77,-32768,-32768,    54,-32768,    78,    54,
    48,-32768,-32768,-32768,    21,-32768,-32768,-32768,-32768,-32768,
    79,    75,    75,    81,    75,    75,    82,-32768,-32768,    17,
    65,    76,    76,    75,    83,    65,    65,    75,    84,    85,
    86,    54,    75,    87,    54,-32768,-32768,    88,    17,-32768,
    76,    89,    90,    76,    54,-32768,-32768,-32768,-32768,-32768,
-32768,    91,    92,-32768,    93,-32768,-32768,-32768,-32768,-32768,
    94,    95,    75,-32768,    75,-32768,    76,    96,    97,    98,
-32768,-32768,-32768,   100,   105,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,-32768,-32768,    73,-32768,-32768,    27,-32768,-32768,
-32768,-32768,    31,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,   -93,-32768,-32768,   -60,   -90,   -69,   -26,   -72,
   -84,    -7,-32768,   -37,-32768,   -29,   -48
};


#define	YYLAST		127


static const short yytable[] = {    59,
    87,    38,    43,    86,    57,   114,    45,   120,   111,    68,
     2,    82,   126,   127,    56,     4,    65,   128,   111,    67,
    36,    79,    44,    48,    58,     7,    10,    11,    89,    87,
    87,    91,   110,   123,   113,     5,    76,   102,   103,   104,
   105,   116,   117,   124,    98,    99,    18,     9,    87,    35,
    61,    87,   133,    32,   141,    19,    20,    36,    21,    22,
    23,    39,    41,   132,    92,    93,   135,    94,    95,    96,
    97,    98,    99,    46,    87,    71,   142,   150,    72,    48,
    73,    47,   148,    50,   149,    24,    25,    26,    27,    28,
    52,    54,    60,    75,   138,    78,    64,    66,    70,   155,
    77,    80,    81,    85,   156,    88,    90,   107,   112,   115,
   125,   137,   129,   130,   131,   134,   136,   139,   140,   143,
   144,   145,   146,   147,   151,   152,   153
};

static const short yycheck[] = {    48,
    73,    31,     7,    73,     7,    96,    36,   101,    93,    58,
    28,    72,   106,   107,    44,     3,    54,   108,   103,    57,
    25,    70,    27,    26,    27,     4,    28,    29,    77,   102,
   103,    80,    93,   103,    95,    28,    66,    17,    18,    19,
    20,    25,    26,   104,    24,    25,    29,    25,   121,    25,
    15,   124,   113,    28,   124,     5,     6,    25,     8,     9,
    10,    25,    25,   112,    17,    18,   115,    20,    21,    22,
    23,    24,    25,    29,   147,    11,   125,   147,    14,    26,
    16,    29,   143,    29,   145,    13,    14,    15,    16,    17,
    25,    25,    29,    63,   121,    69,    29,    29,    28,     0,
    29,    28,    28,    28,     0,    29,    29,    29,    28,    28,
    28,   119,    29,    29,    29,    29,    29,    29,    29,    29,
    29,    29,    29,    29,    29,    29,    29
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "../bison//share/bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(TO,FROM,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (to, from, count)
     char *to;
     char *from;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *to, char *from, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 196 "../bison//share/bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#ifdef __cplusplus
#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* not __cplusplus */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not YYPARSE_PARAM */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* not YYPARSE_PARAM */

int
yyparse(YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 1:
#line 183 "scan-ops_pddl.y"
{ 
  opserr( DOMDEF_EXPECTED, NULL ); 
;
    break;}
case 3:
#line 194 "scan-ops_pddl.y"
{ 
  /* initialize typetree 
   */
  gglobal_type_tree_list = new_type_tree_list( STANDARD_TYPE );
;
    break;}
case 4:
#line 200 "scan-ops_pddl.y"
{
  if ( gcmd_line.display_info >= 1 ) {
    printf("\ndomain '%s' defined\n", gdomain_name);
  }
;
    break;}
case 5:
#line 211 "scan-ops_pddl.y"
{ 
  gdomain_name = new_Token( strlen(yyvsp[-1].string)+1 );
  strcpy( gdomain_name, yyvsp[-1].string);
;
    break;}
case 12:
#line 237 "scan-ops_pddl.y"
{
;
    break;}
case 13:
#line 240 "scan-ops_pddl.y"
{ 
;
    break;}
case 14:
#line 246 "scan-ops_pddl.y"
{;
    break;}
case 15:
#line 249 "scan-ops_pddl.y"
{

  FactList *fl, *fl1;
  TokenList *tl, *tl1;

  if ( gpredicates_and_types ) {
    fl = gpredicates_and_types;
    while ( fl->next ) {
      fl = fl->next;
    }
    fl->next = new_FactList();
    fl = fl->next;
  } else {
    fl = new_FactList();
    gpredicates_and_types = fl;
  }
  tl = new_TokenList();
  fl->item = tl;
  tl->item = new_Token( strlen( yyvsp[-2].string ) + 1);
  strcpy( tl->item, yyvsp[-2].string );
  fl1 = yyvsp[-1].pFactList;
  while ( fl1 ) {
    tl1 = new_TokenList();
    tl->next = tl1;
    tl = tl1;
    tl1->item = new_Token( strlen( fl1->item->next->item ) + 1 );
    strcpy( tl1->item, fl1->item->next->item );
    fl1 = fl1->next;
  }
  free_FactList( yyvsp[-1].pFactList );

;
    break;}
case 17:
#line 288 "scan-ops_pddl.y"
{ 
  opserr( REQUIREM_EXPECTED, NULL ); 
;
    break;}
case 18:
#line 292 "scan-ops_pddl.y"
{ 
  if ( !supported( yyvsp[0].string ) ) {
    opserr( NOT_SUPPORTED, yyvsp[0].string );
    yyerror();
  }
;
    break;}
case 21:
#line 307 "scan-ops_pddl.y"
{ 
  if ( !supported( yyvsp[0].string ) ) {
    opserr( NOT_SUPPORTED, yyvsp[0].string );
    yyerror();
  }
;
    break;}
case 23:
#line 320 "scan-ops_pddl.y"
{ 
  opserr( TYPEDEF_EXPECTED, NULL ); 
;
    break;}
case 24:
#line 324 "scan-ops_pddl.y"
{ 
  add_to_type_tree( yyvsp[-1].pFactList, main_type_tree() );
  free_FactList( yyvsp[-1].pFactList );
;
    break;}
case 25:
#line 334 "scan-ops_pddl.y"
{ 
  opserr( CONSTLIST_EXPECTED, NULL ); 
;
    break;}
case 26:
#line 338 "scan-ops_pddl.y"
{ 
  gorig_constant_list = yyvsp[-1].pFactList;
;
    break;}
case 27:
#line 349 "scan-ops_pddl.y"
{ 
  opserr( ACTION, NULL ); 
;
    break;}
case 28:
#line 353 "scan-ops_pddl.y"
{ 
  scur_op = new_PlOperator( yyvsp[0].string );
;
    break;}
case 29:
#line 357 "scan-ops_pddl.y"
{
  scur_op->next = gloaded_ops;
  gloaded_ops = scur_op; 
;
    break;}
case 30:
#line 367 "scan-ops_pddl.y"
{ 
  scur_op->params = NULL; 
;
    break;}
case 31:
#line 372 "scan-ops_pddl.y"
{
  FactList *f;
  scur_op->params = yyvsp[-1].pFactList;
  for (f = scur_op->params; f; f = f->next) {
    /* to be able to distinguish params from :VARS 
     */
    scur_op->number_of_real_params++;
  }
;
    break;}
case 33:
#line 389 "scan-ops_pddl.y"
{
  FactList *f = NULL;

  /* add vars as parameters 
   */
  if ( scur_op->params ) {
    for( f = scur_op->params; f->next; f = f->next ) {
      /* empty, get to the end of list 
       */
    }
    f->next = yyvsp[-2].pFactList;
    f = f->next;
  } else {
    scur_op->params = yyvsp[-2].pFactList;
  }
;
    break;}
case 34:
#line 407 "scan-ops_pddl.y"
{ 
  scur_op->preconds = yyvsp[0].pPlNode; 
;
    break;}
case 36:
#line 413 "scan-ops_pddl.y"
{ 
  scur_op->effects = yyvsp[0].pPlNode; 
;
    break;}
case 38:
#line 428 "scan-ops_pddl.y"
{ 
  if ( sis_negated ) {
    yyval.pPlNode = new_PlNode(NOT);
    yyval.pPlNode->sons = new_PlNode(ATOM);
    yyval.pPlNode->sons->atom = yyvsp[0].pTokenList;
    sis_negated = FALSE;
  } else {
    yyval.pPlNode = new_PlNode(ATOM);
    yyval.pPlNode->atom = yyvsp[0].pTokenList;
  }
;
    break;}
case 39:
#line 441 "scan-ops_pddl.y"
{ 
  yyval.pPlNode = new_PlNode(AND);
  yyval.pPlNode->sons = yyvsp[-1].pPlNode;
;
    break;}
case 40:
#line 447 "scan-ops_pddl.y"
{ 
  yyval.pPlNode = new_PlNode(OR);
  yyval.pPlNode->sons = yyvsp[-1].pPlNode;
;
    break;}
case 41:
#line 453 "scan-ops_pddl.y"
{ 
  yyval.pPlNode = new_PlNode(NOT);
  yyval.pPlNode->sons = yyvsp[-1].pPlNode;
;
    break;}
case 42:
#line 459 "scan-ops_pddl.y"
{ 
  PlNode *np = new_PlNode(NOT);
  np->sons = yyvsp[-2].pPlNode;
  np->next = yyvsp[-1].pPlNode;

  yyval.pPlNode = new_PlNode(OR);
  yyval.pPlNode->sons = np;
;
    break;}
case 43:
#line 471 "scan-ops_pddl.y"
{ 
  /* The typed_list_variable returns a FactList with two-item TokenLists, 
   * the first item is the variable and the second item its type.
   * We now have to split off this FactList into a PlNode for each 
   * variable-type TokenList. 
   */
  FactList *tl = yyvsp[-3].pFactList, *t1;
  PlNode *pln1;
  PlNode *pln2;

  pln1 = new_PlNode(EX);
  pln1->atom = tl->item;
  yyval.pPlNode = pln1;

  t1 = tl;
  /* every loop gives us one quantor with one variable and its type 
   */
  while ( t1->next ) {
    t1 = t1->next;

    pln2 = new_PlNode(EX);
    pln2->atom = t1->item;
    /* append the next quantor to the sons of the previous node 
     */
    pln1->sons = pln2;
    pln1 = pln2;
  }
  pln1->sons = yyvsp[-1].pPlNode;

  t1 = tl->next;
  while ( TRUE ) {
    free ( tl );
    if ( !t1 ) break;
    tl = t1;
    t1 = tl->next;
  }

;
    break;}
case 44:
#line 513 "scan-ops_pddl.y"
{ 
  /* This will be handled exactly like the ex-quantor case, s.a. 
   */
  FactList *tl = yyvsp[-3].pFactList, *t1;
  PlNode *pln1;
  PlNode *pln2;
  
  pln1 = new_PlNode(ALL);
  pln1->atom = tl->item;
  yyval.pPlNode = pln1;

  t1 = tl;
  /* every loop gives us one quantor with one variable and its type 
   */
  while ( t1->next ) {
    t1 = t1->next;
      
    pln2 = new_PlNode(ALL);
    pln2->atom = t1->item;
    pln1->sons = pln2;
    pln1 = pln2;
  }
  pln1->sons = yyvsp[-1].pPlNode;

  t1 = tl->next;
  while ( TRUE ) {
    free ( tl );
    if ( !t1 ) break;
    tl = t1;
    t1 = tl->next;
  }

;
    break;}
case 45:
#line 552 "scan-ops_pddl.y"
{
  yyval.pPlNode = NULL;
;
    break;}
case 46:
#line 557 "scan-ops_pddl.y"
{
  yyvsp[-1].pPlNode->next = yyvsp[0].pPlNode;
  yyval.pPlNode = yyvsp[-1].pPlNode;
;
    break;}
case 47:
#line 570 "scan-ops_pddl.y"
{ 
  if ( sis_negated ) {
    yyval.pPlNode = new_PlNode(NOT);
    yyval.pPlNode->sons = new_PlNode(ATOM);
    yyval.pPlNode->sons->atom = yyvsp[0].pTokenList;
    sis_negated = FALSE;
  } else {
    yyval.pPlNode = new_PlNode(ATOM);
    yyval.pPlNode->atom = yyvsp[0].pTokenList;
  }
;
    break;}
case 48:
#line 583 "scan-ops_pddl.y"
{ 
  yyval.pPlNode = new_PlNode(AND);
  yyval.pPlNode->sons = yyvsp[-1].pPlNode;
;
    break;}
case 49:
#line 589 "scan-ops_pddl.y"
{ 
  yyval.pPlNode = new_PlNode(NOT);
  yyval.pPlNode->sons = yyvsp[-1].pPlNode;
;
    break;}
case 50:
#line 597 "scan-ops_pddl.y"
{ 
  /* This will be handled exactly like quantors in the goals part, s.o. 
   */
  FactList *fl = yyvsp[-3].pFactList, *f1;
  PlNode *pln1;
  PlNode *pln2;
  
  pln1 = new_PlNode(ALL);
  pln1->atom = fl->item;
  yyval.pPlNode = pln1;

  f1 = fl;
  /* every loop gives us one quantor with one variable and its type 
   */
  while ( f1->next ) {
    f1 = f1->next;
    
    pln2 = new_PlNode(ALL);
    pln2->atom = f1->item;
    pln1->sons = pln2;
    pln1 = pln2;
  }
  pln1->sons = yyvsp[-1].pPlNode;

  f1 = fl->next;
  while ( TRUE ) {
    free( fl );
    if ( !f1 ) break;
    fl = f1;
    f1 = fl->next;
  }

;
    break;}
case 51:
#line 632 "scan-ops_pddl.y"
{
  /* This will be conditional effects in FF representation, but here
   * a formula like (WHEN p q) will be saved as:
   *  [WHEN]
   *  [sons]
   *   /  \
   * [p]  [q]
   * That means, the first son is p, and the second one is q. 
   */
  yyval.pPlNode = new_PlNode(WHEN);
  yyvsp[-2].pPlNode->next = yyvsp[-1].pPlNode;
  yyval.pPlNode->sons = yyvsp[-2].pPlNode;
;
    break;}
case 52:
#line 650 "scan-ops_pddl.y"
{ 
  yyval.pPlNode = NULL; 
;
    break;}
case 53:
#line 655 "scan-ops_pddl.y"
{
  yyvsp[-1].pPlNode->next = yyvsp[0].pPlNode;
  yyval.pPlNode = yyvsp[-1].pPlNode;
;
    break;}
case 54:
#line 667 "scan-ops_pddl.y"
{ 
  yyval.pTokenList = yyvsp[-1].pTokenList;
  sis_negated = TRUE;
;
    break;}
case 55:
#line 673 "scan-ops_pddl.y"
{
  yyval.pTokenList = yyvsp[0].pTokenList;
;
    break;}
case 56:
#line 682 "scan-ops_pddl.y"
{ 
  yyval.pTokenList = new_TokenList();
  yyval.pTokenList->item = yyvsp[-2].pstring;
  yyval.pTokenList->next = yyvsp[-1].pTokenList;
;
    break;}
case 57:
#line 693 "scan-ops_pddl.y"
{ yyval.pTokenList = NULL; ;
    break;}
case 58:
#line 696 "scan-ops_pddl.y"
{
  yyval.pTokenList = new_TokenList();
  yyval.pTokenList->item = yyvsp[-1].pstring;
  yyval.pTokenList->next = yyvsp[0].pTokenList;
;
    break;}
case 59:
#line 707 "scan-ops_pddl.y"
{ 
  yyval.pstring = new_Token( strlen(yyvsp[0].string)+1 );
  strcpy( yyval.pstring, yyvsp[0].string );
;
    break;}
case 60:
#line 713 "scan-ops_pddl.y"
{ 
  yyval.pstring = new_Token( strlen(yyvsp[0].string)+1 );
  strcpy( yyval.pstring, yyvsp[0].string );
;
    break;}
case 61:
#line 723 "scan-ops_pddl.y"
{
  yyval.pTokenList = new_TokenList();
  yyval.pTokenList->item = new_Token( strlen(yyvsp[0].string)+1 );
  strcpy( yyval.pTokenList->item, yyvsp[0].string );
;
    break;}
case 62:
#line 730 "scan-ops_pddl.y"
{
  yyval.pTokenList = new_TokenList();
  yyval.pTokenList->item = new_Token( strlen(yyvsp[-1].string)+1 );
  strcpy( yyval.pTokenList->item, yyvsp[-1].string );
  yyval.pTokenList->next = yyvsp[0].pTokenList;
;
    break;}
case 63:
#line 742 "scan-ops_pddl.y"
{ 
  yyval.pstring = new_Token( strlen(yyvsp[0].string)+1 );
  strcpy( yyval.pstring, yyvsp[0].string );
;
    break;}
case 64:
#line 748 "scan-ops_pddl.y"
{ 
  yyval.pstring = new_Token( strlen(EQ_STR)+1 );
  strcpy( yyval.pstring, EQ_STR );
;
    break;}
case 65:
#line 758 "scan-ops_pddl.y"
{ yyval.pFactList = NULL; ;
    break;}
case 66:
#line 761 "scan-ops_pddl.y"
{ /* this is a very, very special case... it may mean that
   * a. a parameter has one of the types in name_plus
   * b. a type is subtype of one of the following types in name_plus 
   * => for both possibilities we use the same solution:
   * build a new type name: either_name1_name2_..._namen and check
   * if a type with this name already exists. If so then NAME has this type,
   * if not then build a new type, include it in the type tree and
   * return NAME with the new type 
   * The new artificial type is not a subtype of OBJECT because its own
   * elements must already be instances of a subtype of OBJECT 
   */
  char *s;
  TokenList *t, *t1;
  type_tree tt;
  type_tree_list rootl, *st;
  
  s = new_Token( MAX_LENGTH );
  strcpy( s, EITHER_STR );
  for ( t = yyvsp[-2].pTokenList; t; t = t->next ) {
    strcat( s, CONNECTOR );
    strcat( s, t->item );
  }
  tt = NULL;
  for ( rootl = gglobal_type_tree_list; rootl; rootl = rootl->next ) {
    if ((tt = find_branch( s, rootl->item))) break;
  }
  if ( !tt ) {/* the type doesn't exist yet, so build it */
    rootl = new_type_tree_list( s );
    rootl->next = gglobal_type_tree_list;
    st = &(rootl->item->sub_types);
    for ( t = yyvsp[-2].pTokenList; t; t = t->next ) {
      if ((tt = find_branch( t->item, main_type_tree()))) {
	*st = new_type_tree_list( NULL );
	(*st)->item = tt;
	st = &((*st)->next);
      }
    }  
  }

  t = yyvsp[-2].pTokenList;
  while ( t ) {
    t1 = t->next;
    free( t->item );
    free( t );
    t = t1;
  }

  /* now do the simple stuff: return a name with a (quite complicated)
   * type 
   */
  yyval.pFactList = new_FactList();
  yyval.pFactList->item = new_TokenList();
  yyval.pFactList->item->item = new_Token( strlen(yyvsp[-4].string)+1 );
  strcpy( yyval.pFactList->item->item, yyvsp[-4].string );
  yyval.pFactList->item->next = new_TokenList();
  yyval.pFactList->item->next->item = s;
  yyval.pFactList->next = yyvsp[0].pFactList;
;
    break;}
case 67:
#line 821 "scan-ops_pddl.y"
{
  yyval.pFactList = new_FactList();
  yyval.pFactList->item = new_TokenList();
  yyval.pFactList->item->item = new_Token( strlen(yyvsp[-2].string)+1 );
  strcpy( yyval.pFactList->item->item, yyvsp[-2].string );
  yyval.pFactList->item->next = new_TokenList();
  yyval.pFactList->item->next->item = new_Token( strlen(yyvsp[-1].string)+1 );
  strcpy( yyval.pFactList->item->next->item, yyvsp[-1].string );
  yyval.pFactList->next = yyvsp[0].pFactList;
;
    break;}
case 68:
#line 833 "scan-ops_pddl.y"
{
  yyval.pFactList = new_FactList();
  yyval.pFactList->item = new_TokenList();
  yyval.pFactList->item->item = new_Token( strlen(yyvsp[-1].string)+1 );
  strcpy( yyval.pFactList->item->item, yyvsp[-1].string );
  yyval.pFactList->item->next = new_TokenList();
  if ( yyvsp[0].pFactList ) {/* another element (already typed) is following */
    char *s = yyvsp[0].pFactList->item->next->item;
    yyval.pFactList->item->next->item = new_Token(strlen(s) + 1);
    strcpy( yyval.pFactList->item->next->item, s ); /* same type as the next one */
    yyval.pFactList->next = yyvsp[0].pFactList;
  } else {/* no further element - it must be an untyped list */
    yyval.pFactList->item->next->item = new_Token( strlen(STANDARD_TYPE)+1 );
    strcpy( yyval.pFactList->item->next->item, STANDARD_TYPE );
    yyval.pFactList->next = yyvsp[0].pFactList;
  }
;
    break;}
case 69:
#line 856 "scan-ops_pddl.y"
{ yyval.pFactList = NULL; ;
    break;}
case 70:
#line 859 "scan-ops_pddl.y"
{ /* this is a very, very special case... it may mean that
   * a parameter has one of the types in name_plus
   * => build a new type name: either_name1_name2_..._namen and check
   * if a type with this name already exists. If so then NAME has this type,
   * if not then build a new type, include it in the type tree and
   * return NAME with the new type 
   * The new artificial type is not a subtype of OBJECT because its own
   * elements must already be instances of a subtype of OBJECT 
   */
  char *s;
  TokenList *t, *t1;
  type_tree tt;
  type_tree_list rootl, *st;
  
  s = new_Token( MAX_LENGTH );
  strcpy( s, EITHER_STR );
  for ( t = yyvsp[-2].pTokenList; t; t = t->next ) {
    strcat( s, CONNECTOR );
    strcat( s, t->item );
  }
  tt = NULL;
  for ( rootl = gglobal_type_tree_list; rootl; rootl = rootl->next ) {
    if ((tt = find_branch( s, rootl->item))) break;
  }
  if ( !tt ) {/* the type doesn't exist yet, so build it */
    rootl = new_type_tree_list( s );
    rootl->next = gglobal_type_tree_list;
    st = &(rootl->item->sub_types);
    for ( t = yyvsp[-2].pTokenList; t; t = t->next ) {
      if ((tt = find_branch( t->item, main_type_tree()))) {
	*st = new_type_tree_list( NULL );
	(*st)->item = tt;
	st = &((*st)->next);
      }
    }  
    gglobal_type_tree_list = rootl;
  }

  t = yyvsp[-2].pTokenList;
  while ( t ) {
    t1 = t->next;
    free( t->item );
    free( t );
    t = t1;
  }

  /* now do the simple stuff: return a name with a (quite complicated)
   * type 
   */
  yyval.pFactList = new_FactList();
  yyval.pFactList->item = new_TokenList();
  yyval.pFactList->item->item = new_Token( strlen(yyvsp[-4].string)+1 );
  strcpy( yyval.pFactList->item->item, yyvsp[-4].string );
  yyval.pFactList->item->next = new_TokenList();
  yyval.pFactList->item->next->item = s;
  yyval.pFactList->next = yyvsp[0].pFactList;
;
    break;}
case 71:
#line 918 "scan-ops_pddl.y"
{
  yyval.pFactList = new_FactList();
  yyval.pFactList->item = new_TokenList();
  yyval.pFactList->item->item = new_Token( strlen(yyvsp[-2].string)+1 );
  strcpy( yyval.pFactList->item->item, yyvsp[-2].string );
  yyval.pFactList->item->next = new_TokenList();
  yyval.pFactList->item->next->item = new_Token( strlen(yyvsp[-1].string)+1 );
  strcpy( yyval.pFactList->item->next->item, yyvsp[-1].string );
  yyval.pFactList->next = yyvsp[0].pFactList;
;
    break;}
case 72:
#line 930 "scan-ops_pddl.y"
{
  yyval.pFactList = new_FactList();
  yyval.pFactList->item = new_TokenList();
  yyval.pFactList->item->item = new_Token( strlen(yyvsp[-1].string)+1 );
  strcpy( yyval.pFactList->item->item, yyvsp[-1].string );
  yyval.pFactList->item->next = new_TokenList();
  if ( yyvsp[0].pFactList ) {/* another element (already typed) is following */
    char *s = yyvsp[0].pFactList->item->next->item;
    int l = strlen( s );
    yyval.pFactList->item->next->item = new_Token( l+1 );
    strcpy( yyval.pFactList->item->next->item, s ); /* same type as the next one */
    yyval.pFactList->next = yyvsp[0].pFactList;
  } else {/* no further element - it must be an untyped list */
    yyval.pFactList->item->next->item = new_Token( strlen(STANDARD_TYPE)+1 );
    strcpy( yyval.pFactList->item->next->item, STANDARD_TYPE );
    yyval.pFactList->next = yyvsp[0].pFactList;
  }
;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 498 "../bison//share/bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 950 "scan-ops_pddl.y"

#include "lex.ops_pddl.c"


/**********************************************************************
 * Functions
 **********************************************************************/

/* 
 * call	bison -pops -bscan-ops scan-ops.y
 */

void opserr( int errno, char *par )

{

/*   sact_err = errno; */

/*   if ( sact_err_par ) { */
/*     free(sact_err_par); */
/*   } */
/*   if ( par ) { */
/*     sact_err_par = new_Token(strlen(par)+1); */
/*     strcpy(sact_err_par, par); */
/*   } else { */
/*     sact_err_par = NULL; */
/*   } */

}
  


int yyerror( char *msg )

{

  fflush(stdout);
  fprintf(stderr, "\n%s: syntax error in line %d, '%s':\n", 
	  gact_filename, lineno, yytext);

  if ( NULL != sact_err_par ) {
    fprintf(stderr, "%s %s\n", serrmsg[sact_err], sact_err_par);
  } else {
    fprintf(stderr, "%s\n", serrmsg[sact_err]);
  }

  exit( 1 );

}



void load_ops_file( char *filename )

{

  FILE * fp;/* pointer to input files */
  char tmp[MAX_LENGTH] = "";

  /* open operator file 
   */
  if( ( fp = fopen( filename, "r" ) ) == NULL ) {
    sprintf(tmp, "\nff: can't find operator file: %s\n\n", filename );
    perror(tmp);
    exit( 1 );
  }

  gact_filename = filename;
  lineno = 1; 
  yyin = fp;

  yyparse();

  fclose( fp );/* and close file again */

}
