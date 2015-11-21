

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
 * File: relax.c
 * Description: this file handles the relaxed planning problem, i.e.,
 *              the code is responsible for the heuristic evaluation
 *              of states during search.
 *
 *              --- THE HEART PEACE OF THE FF PLANNER ! ---
 *
 *              - fast (time critical) computation of the relaxed fixpoint
 *              - extraction of as short as possible plans, without search
 *
 * Author: Joerg Hoffmann 1999
 *
 *********************************************************************/ 









#include "ff.h"

#include "output.h"
#include "memory.h"

#include "relax.h"








/* local globals
 */








/* fixpoint
 */
int *lF;
int lnum_F;
int *lO;
int lnum_O;

int *lch_O;
int lnum_ch_O;

int *l0P_O;
int lnum_0P_O;



/* 1P extraction
 */
int **lgoals_at;
int *lnum_goals_at;

int *lch_F;
int lnum_ch_F;

int lsum;







/* some simple helpers, for -1 == INFINITY method
 */











Bool LESS( int a, int b )

{

  if ( a == INFINITY ) {
    return FALSE;
  }

  if ( b == INFINITY ) {
    return TRUE;
  }

  return ( a < b ? TRUE : FALSE );

}



Bool LEQ( int a, int b )

{

  if ( b == INFINITY ) {
    return TRUE;
  }

  if ( a == INFINITY ) {
    return FALSE;
  }

  return ( a <= b ? TRUE : FALSE );

}



Bool GEQ( int a, int b )

{


  if ( a == INFINITY ) {
    return TRUE;
  }

  if ( b == INFINITY ) {
    return FALSE;
  }

  return ( a >= b ? TRUE : FALSE );

}











/* functions accessed from outside
 */










int get_1P_and_AH( State S )

{

  int h, max;

  gevaluated_states++;

  max = build_fixpoint( S, TRUE );
  h = extract_1P( max, TRUE );

  if ( gcmd_line.display_info == 115 ) {
    print_fixpoint_result();
  }

  reset_fixpoint();

  return h;

}



int get_1P( State S )

{

  int h, max;

  gevaluated_states++;

  max = build_fixpoint( S, FALSE );
  h = extract_1P( max, FALSE );

  if ( gcmd_line.display_info == 115 ) {
    print_fixpoint_result();
  }

  reset_fixpoint();

  return h;

}















/* relaxed fixpoint on a state
 */












int build_fixpoint( State S, Bool A_info )

{

  int start_ft, stop_ft, start_op, stop_op, i, time = 0;

  static Bool first_call = TRUE;

  if ( first_call ) {
    /* get memory for local globals
     */
    lF = ( int * ) calloc( gnum_ft_conn, sizeof( int ) );
    lO = ( int * ) calloc( gnum_op_conn, sizeof( int ) );
    lch_O = ( int * ) calloc( gnum_op_conn, sizeof( int ) );
    l0P_O = ( int * ) calloc( gnum_op_conn, sizeof( int ) );
    
    /* initialize connectivity graph members for
     * relaxed planning
     */
    lnum_0P_O = 0;
    for ( i = 0; i < gnum_op_conn; i++ ) {      
      gop_conn[i].level = INFINITY;    
      gop_conn[i].in_O = FALSE;
      gop_conn[i].num_active_Ps = 0;
      gop_conn[i].ch = FALSE;
      
      gop_conn[i].is_in_H = FALSE;

      if ( gop_conn[i].num_P == 0 ) {
	l0P_O[lnum_0P_O++] = i;
      }
    }
    for ( i = 0; i < gnum_ft_conn; i++ ) {
      gft_conn[i].level = INFINITY;
      gft_conn[i].in_F = FALSE;
    }
    first_call = FALSE;
  }

  initialize_fixpoint( S );

  start_ft = 0;
  start_op = 0;
  while ( TRUE ) {
    if ( all_goals_activated( time ) ) {
      break;
    }

    stop_ft = lnum_F;
    for ( i = start_ft; i < stop_ft; i++ ) {
      activate_ft( lF[i], time );
    }

    if ( time == 0 ) {
      for ( i = 0; i < lnum_0P_O; i++ ) {
	if ( gop_conn[l0P_O[i]].in_O ) {
	  continue;
	}
	new_op( l0P_O[i] );
      }
      if ( A_info ) {
	collect_A_info();
      }
    }

    stop_op = lnum_O;
    for ( i = start_op; i < stop_op; i++ ) {
      activate_op( lO[i], time );
    }

    if ( stop_ft == lnum_F ) {
      break;
    }

    start_ft = stop_ft;
    start_op = stop_op;
    time++;
  }

  return time;

}    



void initialize_fixpoint( State S )

{

  int i;

  lnum_O = 0;
  lnum_ch_O = 0;

  lnum_F = 0;
  for ( i = 0; i < S.num_F; i++ ) {
    if ( gft_conn[S.F[i]].in_F ) {
      continue;
    }
    new_fact( S.F[i] );
  }

}
   


void activate_ft( int index, int time )

{

  int i;

  gft_conn[index].level = time;

  for ( i = 0; i < gft_conn[index].num_P; i++ ) {
    gop_conn[gft_conn[index].P[i]].num_active_Ps++;
    if ( !gop_conn[gft_conn[index].P[i]].ch ) {
      gop_conn[gft_conn[index].P[i]].ch = TRUE;
      lch_O[lnum_ch_O++] = gft_conn[index].P[i];
    }
    if ( gop_conn[gft_conn[index].P[i]].num_active_Ps ==
	 gop_conn[gft_conn[index].P[i]].num_P ) {
      new_op( gft_conn[index].P[i] );
    }
  }

}



void activate_op( int index, int time )

{

  int i;

  gop_conn[index].level = time;

  for ( i = 0; i < gop_conn[index].num_A; i++ ) {
    if ( gft_conn[gop_conn[index].A[i]].in_F ) {
      continue;
    }
    new_fact( gop_conn[index].A[i] );
  }

}



void new_fact( int index )

{

  lF[lnum_F++] = index;
  gft_conn[index].in_F = TRUE;

}



void new_op( int index )

{

  lO[lnum_O++] = index;
  gop_conn[index].in_O = TRUE;

}



void reset_fixpoint( void )

{

  int i;

  for ( i = 0; i < lnum_F; i++ ) {
    gft_conn[lF[i]].level = INFINITY;
    gft_conn[lF[i]].in_F = FALSE;
  }

  for ( i = 0; i < lnum_O; i++ ) {
    gop_conn[lO[i]].level = INFINITY;
    gop_conn[lO[i]].in_O = FALSE;
  }

  for ( i = 0; i < lnum_ch_O; i++ ) {
    gop_conn[lch_O[i]].num_active_Ps = 0;
    gop_conn[lch_O[i]].ch = FALSE;
  }

}



Bool all_goals_activated( int time ) 

{

  int i;

  for ( i = 0; i < ggoal_state.num_F; i++ ) {
    if ( !gft_conn[ggoal_state.F[i]].in_F ) {
      return FALSE;
    }
  }

  for ( i = 0; i < ggoal_state.num_F; i++ ) {
    if ( gft_conn[ggoal_state.F[i]].level == INFINITY ) {
      gft_conn[ggoal_state.F[i]].level = time;
    }
  }

  return TRUE;

}



void collect_A_info( void )

{

  static Bool first_call = TRUE;

  int i;

  if ( first_call ) {
    gA = ( int * ) calloc( gnum_op_conn, sizeof( int ) );
    first_call = FALSE;
  }

  for ( i = 0; i < lnum_O; i++ ) {
    gA[i] = lO[i];
  }
  gnum_A = lnum_O;

}



void print_fixpoint_result( void )

{

  int time, i;
  Bool hit, hit_F, hit_O;

  time = 0;
  while ( 1 ) {
    hit = FALSE;
    hit_F = FALSE;
    hit_O = FALSE;
    for ( i = 0; i < gnum_ft_conn; i++ ) {
      if ( gft_conn[i].level == time ) {
	hit = TRUE;
	hit_F = TRUE;
	break;
      }
    }
    for ( i = 0; i < gnum_op_conn; i++ ) {
      if ( gop_conn[i].level == time ) {
	hit = TRUE;
	hit_O = TRUE;
	break;
      }
    }
    if ( !hit ) {
      break;
    }
 
    printf("\n\nLEVEL %d:", time);
    if ( hit_F ) {
      printf("\n\nFACTS:");
      for ( i = 0; i < gnum_ft_conn; i++ ) {
	if ( gft_conn[i].level == time ) {
	  printf("\n");
	  print_ft_name( i );
	}
      }
    }
    if ( hit_O ) {
      printf("\n\nOPS:");
      for ( i = 0; i < gnum_op_conn; i++ ) {
	if ( gop_conn[i].level == time ) {
	  printf("\n");
	  print_op_name( i );
	}
      }
    }

    time++;
  }
  fflush( stdout );

}
    






/* 1P extraction
 */












int extract_1P( int max, Bool AH_info )

{

  static Bool first_call = TRUE;
  int i, max_goal_level, time;

  if ( first_call ) {
    for ( i = 0; i < gnum_ft_conn; i++ ) {
      gft_conn[i].is_true = INFINITY;
      gft_conn[i].is_goal = FALSE;
      gft_conn[i].ch = FALSE;
    }
    lch_F = ( int * ) calloc( gnum_ft_conn, sizeof( int ) );
    first_call = FALSE;
  }

  if ( (max_goal_level = initialize_goals( max )) == INFINITY ) {
    return INFINITY;
  }

  lnum_ch_F = 0;
  lsum = 0;
  for ( time = max_goal_level; time > 0; time-- ) {
    achieve_goals( time );
    if ( time == 1 && AH_info ) {
      collect_H_info();
    }
  }

  reset_search_info();

  return lsum;

}



int initialize_goals( int max )

{

  static Bool first_call = TRUE;
  static int highest_seen;

  int i, max_goal_level, ft;

  if ( first_call ) {
    lgoals_at = ( int ** ) calloc( RELAXED_STEPS_DEFAULT, sizeof( int * ) );
    lnum_goals_at = ( int * ) calloc( RELAXED_STEPS_DEFAULT, sizeof( int ) );
    for ( i = 0; i < RELAXED_STEPS_DEFAULT; i++ ) {
      lgoals_at[i] = ( int * ) calloc( gnum_ft_conn, sizeof( int ) );
    }
    highest_seen = RELAXED_STEPS_DEFAULT;
    first_call = FALSE;
  }

  if ( max + 1 > highest_seen ) {
    for ( i = 0; i < highest_seen; i++ ) {
      free( lgoals_at[i] );
    }
    free( lgoals_at );
    free( lnum_goals_at );
    highest_seen = max + 1;
    lgoals_at = ( int ** ) calloc( highest_seen, sizeof( int * ) );
    lnum_goals_at = ( int * ) calloc( highest_seen, sizeof( int ) );
    for ( i = 0; i < highest_seen; i++ ) {
      lgoals_at[i] = ( int * ) calloc( gnum_ft_conn, sizeof( int ) );
    }
  }

  for ( i = 0; i < max + 1; i++ ) {
    lnum_goals_at[i] = 0;
  }

  max_goal_level = 0;
  for ( i = 0; i < ggoal_state.num_F; i++ ) {
    ft = ggoal_state.F[i];
    if ( gft_conn[ft].level == INFINITY ) {
      return INFINITY;
    }
    if ( gft_conn[ft].level > max_goal_level ) {
      max_goal_level = gft_conn[ft].level;
    }
    lgoals_at[gft_conn[ft].level][lnum_goals_at[gft_conn[ft].level]++] = ft;
  }

  return max_goal_level;

}



void achieve_goals( int time )

{

  int i, j, k, p, ft, op, min_p, min_o;

  if ( gcmd_line.display_info == 116 ) {
    printf("\nselecting at step %3d: ", time-1);
  }

  for ( i = 0; i < lnum_goals_at[time]; i++ ) {
    ft = lgoals_at[time][i];

    if ( gft_conn[ft].is_true == time ) {
      /* fact already added by prev now selected op
       */
      continue;
    }

    min_p = INFINITY;
    min_o = -1;
    for ( j = 0; j < gft_conn[ft].num_A; j++ ) {
      op = gft_conn[ft].A[j];
      if ( gop_conn[op].level != time - 1 ) continue;
      p = 0;
      for ( k = 0; k < gop_conn[op].num_P; k++ ) {
	p += gft_conn[gop_conn[op].P[k]].level;
      }
      if ( LESS( p, min_p ) ) {
	min_p = p;
	min_o = op;
      }
    }
    op = min_o;

    lsum++;
    if ( gcmd_line.display_info == 116 ) {
      print_op_name( op );
      printf("\n                       ");
    }

    if ( time > 1 ) {
      for ( j = 0; j < gop_conn[op].num_P; j++ ) {
	ft = gop_conn[op].P[j];
	if ( gft_conn[ft].is_true == time ) {
	  /* a prev at this level selected op accidently adds this precond, 
	   * so we can order that op before this one and get the precond added for free.
	   */
	  continue;
	}
	if ( gft_conn[ft].is_goal ) {
	  /* this fact already is a goal
	   */
	  continue;
	}
	lgoals_at[gft_conn[ft].level][lnum_goals_at[gft_conn[ft].level]++] = ft;
	gft_conn[ft].is_goal = TRUE;
	if ( !gft_conn[ft].ch ) {
	  lch_F[lnum_ch_F++] = ft;
	  gft_conn[ft].ch = TRUE;
	}
      }
    }

    for ( j = 0; j < gop_conn[op].num_A; j++ ) {
      ft = gop_conn[op].A[j];
      gft_conn[ft].is_true = time;
      if ( !gft_conn[ft].ch ) {
	lch_F[lnum_ch_F++] = ft;
	gft_conn[ft].ch = TRUE;
      }
    }
  }  

}



void collect_H_info( void )

{

  static Bool first_call = TRUE;
  int i, j, ft, op;

  if ( gcmd_line.display_info == 117 ) {
    printf("\ncollecting H: ");
  }

  if ( first_call ) {
    gH = ( int * ) calloc( gnum_op_conn, sizeof( int ) );
    gnum_H = 0;
    first_call = FALSE;
  }

  for ( i = 0; i < gnum_H; i++ ) {
    gop_conn[gH[i]].is_in_H = FALSE;
  }
  gnum_H = 0;

  for ( i = 0; i < lnum_goals_at[1]; i++ ) {
    ft = lgoals_at[1][i];

    for ( j = 0; j < gft_conn[ft].num_A; j++ ) {
      op = gft_conn[ft].A[j];
      if ( gop_conn[op].level != 0 ) {
	continue;
      }

      if ( gop_conn[op].is_in_H ) {
	continue;
      }
      gop_conn[op].is_in_H = TRUE;
      gH[gnum_H++] = op;
      if ( gcmd_line.display_info == 117 ) {
	print_op_name( op );
	printf("\n              ");
      }
    }
  }

}



void reset_search_info( void )

{

  int i;

  for ( i = 0; i < lnum_ch_F; i++ ) {
    gft_conn[lch_F[i]].is_true = INFINITY;
    gft_conn[lch_F[i]].is_goal = FALSE;
    gft_conn[lch_F[i]].ch = FALSE;
  }
  
}
