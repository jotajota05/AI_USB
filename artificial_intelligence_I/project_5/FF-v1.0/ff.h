
/*********************************************************************
 * (C) Copyright 1999 Albert Ludwigs University Freiburg
 *     Institute of Computer Science
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 * 
 *********************************************************************/


/*********************************************************************
 * File: ff.h
 * Description: Types and structures for the FastForward planner.
 *
 *        --------- STRIPS  VERSION  v 1.0 --------------
 *
 * Author: Joerg Hoffmann 1999
 * Contact: hoffmann@informatik.uni-freiburg.de
 *
 *********************************************************************/ 








#ifndef __FF_H
#define __FF_H

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <sys/times.h>









/*
 *  ------------------------------------ DEFINES ----------------------------
 */











/***********************
 * MEANINGLESS HELPERS *
 ***********************/




/* strcmp returns 0 if two strings are equal, which is not nice */
#define SAME 0









/****************
 * PARSING ETC. *
 ****************/









/* various defines used in parsing
 */
#define EQ_STR "EQ"
#define HIDDEN_STR "#"
#define AXIOM_STR "AXIOM"
#define NAME_STR "name\0"
#define VARIABLE_STR "variable\0"
#define STANDARD_TYPE "OBJECT\0"
#define EITHER_STR "EITHER"









/***************************
 * SOME ARBITRARY SETTINGS *
 ***************************/











/* maximal string length
 */
#define MAX_LENGTH 256 


/* marks border between connected items 
 */
#define CONNECTOR "~"


/* std size of helping arrays
 */
#define ARRAY_SIZE 50 


/* first size of goals_at array in 1P extraction
 */
#define RELAXED_STEPS_DEFAULT 10







/************************
 * INSTANTIATION LIMITS *
 ************************/






#define MAX_CONSTANTS 2000
#define MAX_PREDICATES 50
#define MAX_TYPES 50
#define MAX_ARITY 5
#define MAX_VARS 15


#define MAX_TYPE 2000


#define MAX_INITIAL 5000


#define MAX_OPERATORS 50


#define MAX_TYPE_INTERSECTIONS 10


#define MAX_RELEVANT_FACTS 50000/* i think this is VERY generous... */









/******************************************
 * DOMAIN STRUCTURE AND SEARCHING LIMITS *
 ******************************************/







#define MAX_OP_P 10
#define MAX_OP_A 10
#define MAX_OP_D 10





#define MAX_PLAN_LENGTH 2000


#define MAX_STATE 400


#define MAX_SPACE 150000


#define STATE_HASH_SIZE 4096
#define STATE_HASH_BITS 4095







/****************
 * CODE DEFINES *
 ****************/








/* not a real 'code' define; used in relax and search to encode
 * infinite level number / plan length
 */
#ifndef INFINITY
#define INFINITY -1
#endif








/* define boolean types if not allready defined
 */
#ifndef Bool
typedef unsigned char Bool;
#ifndef TRUE /* we assume that FALSE is also not defined */
#define TRUE 1
#define FALSE 0
#endif /* TRUE */
#endif /* Bool */


/* code a param number into a negative number and vice versa
 */
#define ENCODE_VAR( val ) (val * (-1)) - 1
#define DECODE_VAR( val ) (val + 1) * (-1)

#define GET_CONSTANT( val, pointer ) ( val >= 0 ) ? val : pointer->inst_table[DECODE_VAR( val )]


/* Check allocated memory
 */
#define CHECK_PTR(p) if (NULL == (p)) { \
  fprintf(stdout, "\n\aNO MEMORY in file %s:%d\n\n", __FILE__, __LINE__); \
  exit(1);}


/* add elapsed time from main local time vars to specified val
 */
#define TIME( val ) val += ( float ) ( ( end.tms_utime - start.tms_utime + \
					 end.tms_stime - start.tms_stime  ) / 100.0 )












/*
 *  ------------------------------ DATA STRUCTURES ----------------------------
 */











/*******************
 * GENERAL HELPERS *
 *******************/








/* all command switches
 */
struct _command_line {

  char path[MAX_LENGTH];
  char ops_file_name[MAX_LENGTH];
  char fct_file_name[MAX_LENGTH];
  int display_info;
  int debug;

};


typedef char *Token;












/***********
 * PARSING *
 ***********/










/* A list of strings
 */
typedef struct _TokenList {

  char *item;
  struct _TokenList *next;

} TokenList;



/* list of string lists
 */
typedef struct _FactList {

  TokenList *item;
  struct _FactList *next;

} FactList;



/* This type indicates whether a node in the pddl tree stands for
 * an atomic expression, a junctor or a quantor. 
 */
typedef enum _Connective{ATOM, 
			 NOT, 
			 AND, 
			 OR, 
			 ALL, 
			 EX, 
			 WHEN} Connective;



/*
 * This is a node in the tree to parse PDDL files
 */
typedef struct _PlNode {

  /* type of the node
   */
  Connective connective;

  /* AND, OR, NOT, WHEN => NULL
   * ALL, EX            => the quantified variable with its type
   * ATOM               => the atom as predicate->param1->param2->...
   */
  TokenList *atom;

  /* (a) for AND, OR this is the list of sons(a AND b AND c...),
   * (b) for the rest this is the son, e.g. a subtree that is negated
   * (c) for WHEN, the first son is the condition and the next son
   * is the effect
   */
  struct _PlNode *sons;

  /* if you have a list of sons, they are connected by next
   */
  struct _PlNode *next;

} PlNode;


/*
 * This resembles an uninstantiated PDDL operator
 */
typedef struct _PlOperator {

  char *name;

  /* params is a list of variable/type pairs, such that:
   * factlist->item = [variable] -> [type]
   */
  FactList *params;
  PlNode *preconds;
  PlNode *effects;

  /* only important for PDDL where :VARS may be added to the param list
   * which must be hidden when writing the plan to an output file
   */
  int number_of_real_params; 

  struct _PlOperator *next;

} PlOperator;


/* the type_tree structure is used to deal with types and subclasses
 *  of types
 */
typedef struct TYPETREE_LIST *type_tree_list, type_tree_list_elt;

typedef struct TYPETREE {
  
  char *name;  /* an object type */
  type_tree_list sub_types;

} *type_tree, type_tree_elt;

struct TYPETREE_LIST {

  type_tree item;
  struct TYPETREE_LIST *next;

};









/***************** 
 * INSTANTIATION *
 *****************/











typedef int TypeArray[MAX_TYPE_INTERSECTIONS];

typedef int *int_pointer;







/* a partially instantiated fact: predicate and args
 */
typedef struct _Fact {

  int predicate, args[MAX_ARITY];

} Fact;



/* a partially instantiated operator
 */
typedef struct _Operator {

  char *name, *var_names[MAX_VARS];
  int num_vars, var_types[MAX_VARS], inst_table[MAX_VARS];
  int number_of_real_params; 

  Fact preconds[MAX_OP_P];
  int num_preconds;
  Fact adds[MAX_OP_A];
  int num_adds;
  Fact dels[MAX_OP_D];
  int num_dels;

  Bool out;

} Operator, *Operator_pointer;



/* minimal info for a fully instantiated operator;
 * yields one action when expanded
 */
typedef struct _ActionTemplate {

  int op;
  int inst_table[MAX_VARS];

  struct _ActionTemplate *next;

} ActionTemplate;



/* an instantiated operator
 */
typedef struct _Action {

  int op;
  int inst_table[MAX_VARS];

  int preconds[MAX_OP_P];
  int num_preconds;
  int adds[MAX_OP_A];
  int num_adds;
  int dels[MAX_OP_D];
  int num_dels;

  struct _Action *next;

} Action;
  













/*****************************************************
 * BASIC OP AND FT STRUCTURES FOR CONNECTIVITY GRAPH *
 *****************************************************/












typedef struct _OpConn {

  /* to get name
   */
  int op;
  int inst_table[MAX_VARS];

  /* general connectivity info
   */
  int *P;
  int num_P;
  int *A;
  int num_A;
  int *D;
  int num_D;

  /* members for relaxed fixpoint computation
   */
  int level;
  Bool in_O;
  int num_active_Ps;
  Bool ch;

  /* members for 1Ph extraction
   */
  Bool is_in_H;

} OpConn;



typedef struct _FtConn {

  /* general connectivity info
   */
  int *P;
  int num_P;
  int *A;
  int num_A;
  int *D;
  int num_D;

  /* members for orderings computation
   */
  int *False;
  int num_False;

  /* members for relaxed fixpoint computation
   */
  int level;
  Bool in_F;

  /* members for 1Ph extraction
   */
  int is_goal;
  int is_true;
  Bool ch;

  /* in search: for hashing
   */
  int rand;

} FtConn;












/****************************
 * STRUCTURES FOR SEARCHING *
 ****************************/









typedef struct _State {
  
  int F[MAX_STATE];
  int num_F;

} State;



typedef struct _SearchNode {
  
  State S;
  int op;
  int father;
  int depth;

} SearchNode;



typedef struct _StateHashEntry {

  State S;
  int sum;

  struct _StateHashEntry *next;

} StateHashEntry, *StateHashEntry_pointer;
















/*
 *  -------------------------------- MAIN FN HEADERS ----------------------------
 */












void output_planner_info( void );
void ff_usage( void );
Bool process_command_line( int argc, char *argv[] );









/*
 *  ----------------------------- GLOBAL VARIABLES ----------------------------
 */












/*******************
 * GENERAL HELPERS *
 *******************/










/* used to time the different stages of the planner
 */
extern float gtempl_time, greach_time, grelev_time, gconn_time;
extern float gsearch_time;

/* the command line inputs
 */
extern struct _command_line gcmd_line;

/* number of states that got heuristically evaluated
 */
extern int gevaluated_states;

/* info on search spaces structure
 */
extern int gmax_search_depth;
extern int gmax_search_size;








/***********
 * PARSING *
 ***********/











/* used for pddl parsing, flex only allows global variables
 */
extern int gbracket_count;
extern char *gproblem_name;

/* The current input line number
 */
extern int lineno;

/* The current input filename
 */
extern char *gact_filename;

/* The pddl domain name
 */
extern char *gdomain_name;

/* loaded, uninstantiated operators
 */
extern PlOperator *gloaded_ops;

/* stores initials as fact_list 
 */
extern PlNode *gorig_initial_facts;

/* not yet preprocessed goal facts
 */
extern PlNode *gorig_goal_facts;

/* to store all typed objects 
 */
extern FactList *gorig_constant_list;

/* type hierarchy (PDDL) 
 */
extern type_tree_list gglobal_type_tree_list;

/* helper for types parsing
 */
extern FactList *gtypes;

/* the predicates and their types as defined in the domain file
 */
extern FactList *gpredicates_and_types;










/*****************
 * INSTANTIATING *
 *****************/










/* global arrays of constant names,
 *               type names (with their constants),
 *               predicate names,
 *               predicate aritys,
 *               defined types of predicate args
 */
extern Token gconstants[MAX_CONSTANTS];
extern int gnum_constants;
extern Token gtype_names[MAX_TYPES];
extern int gtype_consts[MAX_TYPES][MAX_TYPE];
extern Bool gis_member[MAX_CONSTANTS][MAX_TYPES];
extern int gtype_size[MAX_TYPES];
extern int gnum_types;
extern Token gpredicates[MAX_PREDICATES];
extern int garity[MAX_PREDICATES];
extern int gpredicates_args_type[MAX_PREDICATES][MAX_ARITY];
extern int gnum_predicates;




/* the domain in integer (Fact) representation
 */
extern Operator_pointer goperators[MAX_OPERATORS];
extern int gnum_operators;
extern Fact gfull_initial[MAX_INITIAL];
extern int gnum_full_initial;
extern Fact ggoal[MAX_STATE];
extern int gnum_goal;





/* stores inertia - information: is any occurence of the predicate
 * added / deleted in the uninstantiated ops ?
 */
extern Bool gis_added[MAX_PREDICATES];
extern Bool gis_deleted[MAX_PREDICATES];

/* splitted initial state:
 * initial non static facts,
 * initial inertia facts of arity > 1
 */
extern Fact ginitial[MAX_STATE];
extern int gnum_initial;
extern Fact ginertia[MAX_INITIAL];
extern int gnum_inertia;

/* the type numbers corresponding to any unary inertia
 */
extern int gtype_to_predicate[MAX_PREDICATES];
extern int gpredicate_to_type[MAX_TYPES];

/* (ordered) numbers of types that new type is intersection of
 */
extern TypeArray gintersected_types[MAX_TYPES];
extern int gnum_intersected_types[MAX_TYPES];






/* intermediate step: store minimal action info, use it
 * to determine relevant facts, number of actions and final form
 * before creating actual actions
 */
extern ActionTemplate *gtemplates;
extern int gnum_templates;





/* store the final "relevant facts"
 */
extern Fact grelevant_facts[MAX_RELEVANT_FACTS];
extern int gnum_relevant_facts;
extern int gnum_pp_facts;

/* the (fully instantiated) domain in integer 
 * (number of relevant Fact) representation
 */
extern Action *gactions;
extern int gnum_actions;
extern State ginitial_state;
extern State ggoal_state;










/**********************
 * CONNECTIVITY GRAPH *
 **********************/






/* one fact array, ..
 */
extern FtConn *gft_conn;
extern int gnum_ft_conn;

/* one ops (actions) array
 */
extern OpConn *gop_conn;
extern int gnum_op_conn;








/*******************
 * SEARCHING NEEDS *
 *******************/









/* communication from extract 1.P. to search engines:
 * 1P action choice and all (gA) applicable ops
 */
extern int *gH;
extern int gnum_H;

extern int *gA;
extern int gnum_A;



/* always stores (current) serial plan
 */
extern int gplan_ops[MAX_PLAN_LENGTH];
extern int gnum_plan_ops;

/* stores the states that the current plan goes through
 */
extern State gplan_states[MAX_PLAN_LENGTH + 1];
extern int gplan_states_sum[MAX_PLAN_LENGTH + 1];









#endif __FF_H
