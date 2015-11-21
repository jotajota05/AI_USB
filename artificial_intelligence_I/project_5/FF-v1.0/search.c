
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
 * File: search.c
 * Description: implementation of routines that search the state space
 *
 *              In this version, standard Greedy Heuristic Improvement
 *
 * Author: Joerg Hoffmann 1999
 *
 *********************************************************************/ 









#include "ff.h"

#include "output.h"
#include "memory.h"

#include "relax.h"
#include "search.h"










/* local globals for this file
 */








/* the search space, an array of search nodes with two int pointers into it
 */
SearchNode lsearch_space[MAX_SPACE];
int lspace_start, lspace_end, lspace_size;



/* memory (hash table) for states that are already members
 * of the breadth - first search space
 */
StateHashEntry_pointer lstate_hash_entry[STATE_HASH_SIZE];
int lnum_state_hash_entry[STATE_HASH_SIZE];
int lchanged_entrys[STATE_HASH_SIZE];
int lnum_changed_entrys;
Bool lchanged_entry[STATE_HASH_SIZE];








/* uppermost search function, called by main
 */








Bool do_greedy_heuristic_improvement( void )

{

  State S, S_;
  int h, h_;

  source_to_dest( &S, ginitial_state );

  h = get_1P_and_AH( S );

  if ( h == INFINITY ) {
    printf("\n\nGoals can't be reached -- problem proved unsolvable!\n\n");
    exit( 1 );
  }

  source_to_dest( &(gplan_states[0]), ginitial_state );
  gplan_states_sum[0] = state_sum( ginitial_state );
  
  printf("\n\nCueing down from goal distance: %4d", h);

  while ( h != 0 ) {
    if ( !search_H_for_better_state( S, h, &S_, &h_ ) ) {
      /* H space got empty, switch to complete space
       */
      if ( gcmd_line.display_info ) {
	printf("\n\nH search space got empty !");
	printf("\nswitching to complete search space now.\n");
	fflush( stdout );
      }
      get_1P_and_AH( S );
      reset_hash_entrys();
      if ( !search_A_for_better_state( S, h, &S_, &h_ ) ) {
	if ( gcmd_line.display_info ) {
	  printf("\n\nsearch space got empty !");
	  printf("\neither - problem is not invertible or");
	  printf("\n       - problem is unsolvable\n\n");
	}
	return FALSE;
      }
    }
    source_to_dest( &S, S_ );
    h = h_;
    printf("\n                                %4d", h);
  }

  return TRUE;

}









/* functions that realize breadth first search in
 * H and A spaces for better heuristic evaluated state
 */











Bool search_H_for_better_state( State S, int h, State *S_, int *h_ )

{

  int i, h__;
  State S__;

  lspace_start = 0;
  lspace_end = 0;
  lspace_size = 0;

  hash_state( S );

  for ( i = gnum_H - 1; i > -1; i-- ) {
    result_to_dest( &S__, S, gH[i] );
    add_to_search_space( S__, gH[i], -1 );
  }

  while ( TRUE ) {  
    if ( lspace_start == lspace_end ) {
      return FALSE;
    }
    h__ = expand_H_first_node( h );
    if ( LESS( h__, h ) ) {
      break;
    }
  }

  reset_hash_entrys();

  extract_plan_fragment();

  source_to_dest( S_, lsearch_space[lspace_start].S );
  *h_ = h__;

  if ( lsearch_space[lspace_start].depth > gmax_search_depth ) {
    gmax_search_depth = lsearch_space[lspace_start].depth;
  }

  if ( lspace_size > gmax_search_size ) {
    gmax_search_size = lspace_size;
  }

  return TRUE;

}



Bool search_A_for_better_state( State S, int h, State *S_, int *h_ )

{

  int i, h__;
  State S__;

  lspace_start = 0;
  lspace_end = 0;
  lspace_size = 0;

  hash_state( S );

  for ( i = 0; i < gnum_A; i++ ) {
    result_to_dest( &S__, S, gA[i] );
    add_to_search_space( S__, gA[i], -1 );
  }

  while ( TRUE ) {  
    if ( lspace_start == lspace_end ) {
      return FALSE;
    }
    h__ = expand_A_first_node( h );
    if ( LESS( h__, h ) ) {
      break;
    }
  }

  reset_hash_entrys();

  extract_plan_fragment();

  source_to_dest( S_, lsearch_space[lspace_start].S );
  *h_ = h__;

  if ( lsearch_space[lspace_start].depth > gmax_search_depth ) {
    gmax_search_depth = lsearch_space[lspace_start].depth;
  }

  if ( lspace_size > gmax_search_size ) {
    gmax_search_size = lspace_size;
  }

  return TRUE;

}



void add_to_search_space( State S, int op, int father )

{

  /* see if state is already a part of this search space
   */
  if ( state_hashed( S ) ) {
    return;
  }

  source_to_dest( &(lsearch_space[lspace_end].S), S );
  lsearch_space[lspace_end].op = op;
  lsearch_space[lspace_end].father = father;
  if ( father == -1 ) {
    lsearch_space[lspace_end].depth = 1;
  } else {
    lsearch_space[lspace_end].depth = lsearch_space[father].depth + 1;
  }

  lspace_end++;
  if ( lspace_end == MAX_SPACE ) {
    printf("\nsearch space size too small! currently %d\n\n", MAX_SPACE);
    exit( 1 );
  }

  lspace_size++;

  hash_state( S );

}



int expand_H_first_node( int h )

{

  int h_, i;
  State S_;

  h_ = get_1P_and_AH( lsearch_space[lspace_start].S );
    
  if ( h_ == INFINITY ) {
    lspace_start++;
    return h_;
  }

  if ( h_ < h ) {
    return h_;
  }

  for ( i = gnum_H - 1; i > -1; i-- ) {
    result_to_dest( &S_, lsearch_space[lspace_start].S, gH[i] );
    add_to_search_space( S_, gH[i], lspace_start );
  }
    
  lspace_start++;

  return h_;

}



int expand_A_first_node( int h )

{

  int h_, i;
  State S_;

  h_ = get_1P_and_AH( lsearch_space[lspace_start].S );
    
  if ( h_ == INFINITY ) {
    lspace_start++;
    return h_;
  }

  if ( h_ < h ) {
    return h_;
  }

  for ( i = 0; i < gnum_A; i++ ) {
    result_to_dest( &S_, lsearch_space[lspace_start].S, gA[i] );
    add_to_search_space( S_, gA[i], lspace_start );
  }
    
  lspace_start++;

  return h_;

}











/* updating the current serial plan, based on
 * search space information
 */











void extract_plan_fragment( void )

{

  int i, seen;
  int ops[MAX_PLAN_LENGTH], num_ops;

  num_ops = 0;
  for ( i = lspace_start; i != -1; i = lsearch_space[i].father ) {
    if ( num_ops == MAX_PLAN_LENGTH ) {
      printf("\nincrease MAX_PLAN_LENGTH! currently %d\n\n",
	     MAX_PLAN_LENGTH);
      exit( 1 );
    }
    ops[num_ops++] = lsearch_space[i].op;
  }

  for ( i = num_ops - 1; i > -1; i-- ) {
    /* SCHNELLERE METHODE, hashing oder UBTree verwenden !
     */
    if ( gnum_plan_ops == MAX_PLAN_LENGTH ) {
      printf("\nincrease MAX_PLAN_LENGTH! currently %d\n\n",
	     MAX_PLAN_LENGTH);
      exit( 1 );
    }
    result_to_dest( &(gplan_states[gnum_plan_ops + 1]), 
		    gplan_states[gnum_plan_ops], ops[i] );
    gplan_states_sum[gnum_plan_ops + 1] = state_sum( gplan_states[gnum_plan_ops + 1] );
    if ( (seen = state_seen( gnum_plan_ops + 1)) != -1 ) {
      gnum_plan_ops = seen;
      printf("\ngoing back to %d", seen);
      continue;
    }
    gplan_ops[gnum_plan_ops++] = ops[i];
  }

}



int state_seen( int num )

{

  int i;

  for ( i = 0; i <= gnum_plan_ops; i++ ) {
    if ( gplan_states_sum[i] != gplan_states_sum[num] ) {
      continue;
    }
    if ( same_state( &gplan_states[i], &gplan_states[num] ) ) {
      return i;
    }
  }

  return -1;

}



Bool same_state( State *S1, State *S2 ) 

{

  int i, j;

  if ( (*S2).num_F != (*S1).num_F ) {
    return FALSE;
  }

  for ( i = 0; i < (*S2).num_F; i++ ) {
    for ( j = 0; j < (*S1).num_F; j++ ) {
      if ( (*S1).F[j] == (*S2).F[i] ) {
	break;
      }
    }
    if ( j == (*S1).num_F ) {
      return FALSE;
    }
  }

  return TRUE;

}



int state_sum( State S )

{

  int i, sum = 0;

  for ( i = 0; i < S.num_F; i++ ) {
    sum += gft_conn[S.F[i]].rand;
  }

  return sum;

}










/* hashing algorithm for recognizing repeated states in
 * breadth first search
 */












void hash_state( State S )

{

  static Bool first_call = TRUE;

  int i, sum, index;
  StateHashEntry *h, *prev = NULL;

  if ( first_call ) {
    for ( i = 0; i < STATE_HASH_SIZE; i++ ) {
      lstate_hash_entry[i] = NULL;
      lnum_state_hash_entry[i] = 0;
      lchanged_entry[i] = FALSE;
    }
    lnum_changed_entrys = 0;
    first_call = FALSE;
  }

  sum = state_sum( S );
  index = sum & STATE_HASH_BITS;

  h = lstate_hash_entry[index];
  if ( !h ) {
    h = new_StateHashEntry();
    source_to_dest( &(h->S), S );
    h->sum = sum;
    lstate_hash_entry[index] = h;
    lnum_state_hash_entry[index]++;
    if ( !lchanged_entry[index] ) {
      lchanged_entrys[lnum_changed_entrys++] = index;
      lchanged_entry[index] = TRUE;
    }
    return;
  }
  i = 0;
  while ( h ) {
    if ( i == lnum_state_hash_entry[index] ) {
      break;
    }
    i++;
    prev = h;
    h = h->next;
  }

  if ( h ) {
    /* current list end is still in allocated list of hash entrys
     */
    source_to_dest( &(h->S), S );
    h->sum = sum;
    lnum_state_hash_entry[index]++;
    if ( !lchanged_entry[index] ) {
      lchanged_entrys[lnum_changed_entrys++] = index;
      lchanged_entry[index] = TRUE;
    }
    return;
  }
  /* allocated list ended; connect a new hash entry to it.
   */
  h = new_StateHashEntry();
  source_to_dest( &(h->S), S );
  h->sum = sum;
  prev->next = h;
  lnum_state_hash_entry[index]++;
  if ( !lchanged_entry[index] ) {
    lchanged_entrys[lnum_changed_entrys++] = index;
    lchanged_entry[index] = TRUE;
  }
  return;
      
}



Bool state_hashed( State S )

{

  int i, sum, index;
  StateHashEntry *h;

  sum = state_sum( S );
  index = sum & STATE_HASH_BITS;

  h = lstate_hash_entry[index];
  for ( i = 0; i < lnum_state_hash_entry[index]; i++ ) {
    if ( h->sum != sum ) {
      h = h->next;
      continue;
    }
    if ( same_state( &(h->S), &S ) ) {
      return TRUE;
    }
    h = h->next;
  }

  return FALSE;

}




void reset_hash_entrys( void )

{

  int i;

  for ( i = 0; i < lnum_changed_entrys; i++ ) {
    lnum_state_hash_entry[lchanged_entrys[i]] = 0;
    lchanged_entry[lchanged_entrys[i]] = FALSE;
  }
  lnum_changed_entrys = 0;

}












/* basic state handling functions
 */











void result_to_dest( State *dest, State source, int action )

{

  int i, j;

  dest->num_F = 0;
  for ( i = 0; i < source.num_F; i++ ) {
    for ( j = 0; j < gop_conn[action].num_D; j++ ) {
      if ( gop_conn[action].D[j] == source.F[i] ) {
	break;
      }
    }
    if ( j < gop_conn[action].num_D ) {
      continue;
    }
    dest->F[dest->num_F++] = source.F[i];
  }

  for ( i = 0; i < gop_conn[action].num_A; i++ ) {
    for ( j = 0; j < dest->num_F; j++ ) {
      if ( dest->F[j] == gop_conn[action].A[i] ) {
	break;
      }
    }
    if ( j < dest->num_F ) {
      continue;
    }
    dest->F[dest->num_F++] = gop_conn[action].A[i];
  }

}



void source_to_dest( State *dest, State source )

{

  int i;

  for ( i = 0; i < source.num_F; i++ ) {
    dest->F[i] = source.F[i];
  }
  dest->num_F = source.num_F;

}



void print_state( State S )

{

  int i;
  
  for ( i = 0; i < S.num_F; i++ ) {
    printf("\n");
    print_ft_name( S.F[i] );
  }

}
