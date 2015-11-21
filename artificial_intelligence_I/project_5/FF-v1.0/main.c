
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
 * File: main.c
 * Description: The main routine for the FastForward Planner.
 *
 * Author: Joerg Hoffmann 1999
 * 
 *********************************************************************/ 








#include "ff.h"

#include "memory.h"
#include "output.h"

#include "parse.h"

#include "instantiateI.h"
#include "instantiateII.h"

#include "relax.h"
#include "search.h"









/*
 *  ----------------------------- GLOBAL VARIABLES ----------------------------
 */












/*******************
 * GENERAL HELPERS *
 *******************/








/* used to time the different stages of the planner
 */
float gtempl_time = 0, greach_time = 0, grelev_time = 0, gconn_time = 0;
float gsearch_time = 0;


/* the command line inputs
 */
struct _command_line gcmd_line;

/* number of states that got heuristically evaluated
 */
int gevaluated_states = 0;

/* info on search spaces structure
 */
int gmax_search_depth = 0;
int gmax_search_size = 0;







/***********
 * PARSING *
 ***********/







/* used for pddl parsing, flex only allows global variables
 */
int gbracket_count;
char *gproblem_name;

/* The current input line number
 */
int lineno = 1;

/* The current input filename
 */
char *gact_filename;

/* The pddl domain name
 */
char *gdomain_name = NULL;

/* loaded, uninstantiated operators
 */
PlOperator *gloaded_ops = NULL;

/* stores initials as fact_list 
 */
PlNode *gorig_initial_facts = NULL;

/* not yet preprocessed goal facts
 */
PlNode *gorig_goal_facts = NULL;

/* axioms as in UCPOP before being changed to ops
 */
PlOperator *gloaded_axioms = NULL;

/* to store all typed objects 
 */
FactList *gorig_constant_list = NULL;

/* type hierarchy (PDDL) 
 */
type_tree_list gglobal_type_tree_list;

/* helper for types parsing
 */
FactList *gtypes = NULL;

/* the predicates and their types as defined in the domain file
 */
FactList *gpredicates_and_types = NULL;







/*****************
 * INSTANTIATING *
 *****************/







/* global arrays of constant names,
 *               type names (with their constants),
 *               predicate names,
 *               predicate aritys,
 *               defined types of predicate args
 */
Token gconstants[MAX_CONSTANTS];
int gnum_constants = 0;
Token gtype_names[MAX_TYPES];
int gtype_consts[MAX_TYPES][MAX_TYPE];
Bool gis_member[MAX_CONSTANTS][MAX_TYPES];
int gtype_size[MAX_TYPES];
int gnum_types = 0;
Token gpredicates[MAX_PREDICATES];
int garity[MAX_PREDICATES];
int gpredicates_args_type[MAX_PREDICATES][MAX_ARITY];
int gnum_predicates = 0;





/* the domain in integer (Fact) representation
 */
Operator_pointer goperators[MAX_OPERATORS];
int gnum_operators;
Fact gfull_initial[MAX_INITIAL];
int gnum_full_initial = 0;
Fact ggoal[MAX_STATE];
int gnum_goal = 0;






/* stores inertia - information: is any occurence of the predicate
 * added / deleted in the uninstantiated ops ?
 */
Bool gis_added[MAX_PREDICATES];
Bool gis_deleted[MAX_PREDICATES];

/* splitted initial state:
 * initial non static facts,
 * initial inertia facts of arity > 1
 */
Fact ginitial[MAX_STATE];
int gnum_initial = 0;
Fact ginertia[MAX_INITIAL];
int gnum_inertia = 0;

/* the type numbers corresponding to any unary inertia
 */
int gtype_to_predicate[MAX_PREDICATES];
int gpredicate_to_type[MAX_TYPES];

/* (ordered) numbers of types that new type is intersection of
 */
TypeArray gintersected_types[MAX_TYPES];
int gnum_intersected_types[MAX_TYPES];





/* intermediate step: store minimal action info, use it
 * to determine relevant facts, number of actions and final form
 * before creating actual actions
 */
ActionTemplate *gtemplates = NULL;
int gnum_templates = 0;




/* store the final "relevant facts"
 */
Fact grelevant_facts[MAX_RELEVANT_FACTS];
int gnum_relevant_facts = 0;
int gnum_pp_facts;


/* the (fully instantiated) domain in integer 
 * (number of relevant Fact) representation
 */
Action *gactions = NULL;
int gnum_actions;
State ginitial_state;
State ggoal_state;








/**********************
 * CONNECTIVITY GRAPH *
 **********************/






/* one fact array, ..
 */
FtConn *gft_conn;
int gnum_ft_conn;

/* one ops (actions) array
 */
OpConn *gop_conn;
int gnum_op_conn;









/*******************
 * SEARCHING NEEDS *
 *******************/








/* communication from extract 1.P. to search engines:
 * 1P action choice and all (gA) applicable ops
 */
int *gH;
int gnum_H;

int *gA;
int gnum_A;



/* always stores (current) serial plan
 */
int gplan_ops[MAX_PLAN_LENGTH];
int gnum_plan_ops = 0;

/* stores the states that the current plan goes through
 */
State gplan_states[MAX_PLAN_LENGTH + 1];
int gplan_states_sum[MAX_PLAN_LENGTH + 1];











/*
 *  ----------------------------- HEADERS FOR PARSING ----------------------------
 * ( fns defined in the scan-* files )
 */







void get_fct_file_name( char *filename );
void load_ops_file( char *filename );
void load_fct_file( char *filename );











/*
 *  ----------------------------- MAIN ROUTINE ----------------------------
 */









int main( int argc, char *argv[] )

{

  /* resulting name for ops file
   */
  char ops_file[MAX_LENGTH] = "";
  /* same for fct file 
   */
  char fct_file[MAX_LENGTH] = "";
  
  struct tms start, end;

  Bool found_plan;

  /* command line treatment
   */
  if ( argc == 1 || ( argc == 2 && *++argv[0] == '?' ) ) {
    ff_usage();
    exit( 1 );
  }
  if ( !process_command_line( argc, argv ) ) {
    ff_usage();
    exit( 1 );
  }


  /* make file names
   */

  /* one input name missing
   */
  if ( !gcmd_line.ops_file_name || 
       !gcmd_line.fct_file_name ) {
    fprintf(stdout, "\nff: two input files needed\n\n");
    ff_usage();      
    exit( 1 );
  }
  /* add path info, complete file names will be stored in
   * ops_file and fct_file 
   */
  sprintf(ops_file, "%s%s", gcmd_line.path, gcmd_line.ops_file_name);
  sprintf(fct_file, "%s%s", gcmd_line.path, gcmd_line.fct_file_name);


  /* parse the input files
   */

  /* start parse & instantiation timing
   */
  times( &start );
  /* domain file (ops)
   */
  if ( gcmd_line.display_info >= 1 ) {
    printf("\nff: parsing domain file");
  } 
  /* it is important for the pddl language to define the domain before 
   * reading the problem 
   */
  load_ops_file( ops_file );
  /* problem file (facts)
   */  
  if ( gcmd_line.display_info >= 1 ) {
    printf(" ... done.\nff: parsing problem file"); 
  }
  load_fct_file( fct_file );
  if ( gcmd_line.display_info >= 1 ) {
    printf(" ... done.\n\n");
  }

  /* This is needed to get all types.
   */
  build_orig_constant_list();

  /* last step of parsing: see if it's a STRIPS domain!
   */
  if ( !make_strips_domain() ) {
    printf("\nff: this is not a STRIPS problem!");
    printf("\n    can't be handled by this version.\n\n");
    exit( 1 );
  }


  /* now instantiate operators; 
   */

  /* start by collecting all strings and thereby encoding 
   * the domain in integers.
   */
  encode_domain_in_integers();

  /* inertia preprocessing:
   *   - collect inertia information
   *   - split initial state into
   *        - types for unary inertia
   *        - array containing all inertia relations
   *        - array containing non - static relations
   *   - encode unary inertia in op preconds into types
   */
  do_inertia_preprocessing();

  /* unify inertia preconds with initial state,
   * then multiply remaining parameters;
   * create one ActionTemplate for each possible parameter combination
   *
   * --- the actual instantiation part, creating all possible instances ---
   */
  build_action_templates();

  times(&end);
  TIME( gtempl_time );

  times(&start);

  /* perform a simple reachabilty analysis
   * (added facts fixpoint)
   * to find out which facts can (at most) be made true in domain
   */
  perform_reachability_analysis();
  
  times(&end);
  TIME( greach_time );

  times(&start);

  /* as a last step, collect relevant facts (deleted ini's and
   * added non ini's) and remove others from domain
   */
  collect_relevant_facts();

  times(&end);
  TIME( grelev_time );

  times(&start);

  /* now build globally accessable connectivity graph
   */
  build_connectivity_graph();

  times(&end);
  TIME( gconn_time );
  
  times(&start);

  /* ready to search for a solution !
   */
  found_plan = do_greedy_heuristic_improvement();

  times(&end);
  TIME( gsearch_time );

  if ( found_plan ) {
    print_plan();
  }

  output_planner_info();


  printf("\n\n");
  exit( 0 );

}











/*
 *  ----------------------------- HELPING FUNCTIONS ----------------------------
 */












void output_planner_info( void )

{

  printf( "\n\ntime spent: %7.2f seconds instantiating %d action templates", 
	  gtempl_time, gnum_templates );
  printf( "\n            %7.2f seconds reachability analysis, yielding %d facts and %d actions", 
	  greach_time, gnum_pp_facts, gnum_actions );
  printf( "\n            %7.2f seconds collecting %d relevant facts", 
	  grelev_time, gnum_relevant_facts );
  printf( "\n            %7.2f seconds building connectivity graph", gconn_time );
  printf( "\n            %7.2f seconds searching, evaluating %d states", 
	  gsearch_time, gevaluated_states );
  printf( "\n                    max search depth %d, max search space size %d",
	  gmax_search_depth, gmax_search_size );
  printf( "\n            %7.2f seconds total time", 
	  gtempl_time + greach_time + grelev_time + gconn_time + gsearch_time );

  printf("\n\n");
  exit( 0 );

}



void ff_usage( void )

{

  printf("\nusage of ff:\n");

  printf("\nOPTIONS   DESCRIPTIONS\n\n");
  printf("-p <str>    path for operator and fact file\n");
  printf("-o <str>    operator file name\n");
  printf("-f <str>    fact file name\n\n");
  printf("-i <num>    run-time information level( preset: 1 )\n");
  printf("      0     only times\n");
  printf("      1     problem name, planning process infos\n");
  printf("    101     cleaned up STRIPS problem\n");
  printf("    102     collected string tables\n");
  printf("    103     encoded domain\n");
  printf("    104     predicates inertia info\n");
  printf("    105     splitted initial state\n");
  printf("    106     extended types table\n");
  printf("    107     all action templates\n");
  printf("    108     inertia cleaned up operator schemata\n");
  printf("    109     reachability analysis results\n");
  printf("    110     final domain representation\n");
  printf("    111     connectivity graph\n");
  printf("    112     False sets of goals <GAM>\n");
  printf("    113     detected ordering constraints leq_h <GAM>\n");
  printf("    114     the Goal Agenda <GAM>\n");
  printf("    115     fixpoint result on each evaluated state <1Ph>\n");
  printf("    116     1P extracted on each evaluated state <1Ph>\n");
  printf("    117     H set collected for each evaluated state <1Ph>\n");
  
  printf("\n-d <num>    switch on debugging\n\n");

}



Bool process_command_line( int argc, char *argv[] )

{

  char option;

  gcmd_line.display_info = 1;
  gcmd_line.debug = 0;
  
  memset(gcmd_line.ops_file_name, 0, MAX_LENGTH);
  memset(gcmd_line.fct_file_name, 0, MAX_LENGTH);
  memset(gcmd_line.path, 0, MAX_LENGTH);

  while ( --argc && ++argv ) {
    if ( *argv[0] != '-' || strlen(*argv) != 2 ) {
      return FALSE;
    }
    option = *++argv[0];
    switch ( option ) {
    default:
      if ( --argc && ++argv ) {
	switch ( option ) {
	case 'p':
	  strncpy( gcmd_line.path, *argv, MAX_LENGTH );
	  break;
	case 'o':
	  strncpy( gcmd_line.ops_file_name, *argv, MAX_LENGTH );
	  break;
	case 'f':
	  strncpy( gcmd_line.fct_file_name, *argv, MAX_LENGTH );
	  break;
	case 'i':
	  sscanf( *argv, "%d", &gcmd_line.display_info );
	  break;
	case 'd':
	  sscanf( *argv, "%d", &gcmd_line.debug );
	  break;
	default:
	  printf( "\nff: unknown option: %c entered\n\n", option );
	  return FALSE;
	}
      } else {
	return FALSE;
      }
    }
  }

  return TRUE;

}

