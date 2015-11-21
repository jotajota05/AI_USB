
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
 * File: search.h
 * Description: headers for routines that search the state space
 *
 *              In this version, standard Greedy Heuristic Improvement
 *
 * Author: Joerg Hoffmann 1999
 *
 *********************************************************************/ 






#ifndef _SEARCH_H
#define _SEARCH_H



Bool do_greedy_heuristic_improvement( void );



Bool search_H_for_better_state( State S, int h, State *S_, int *h_ );
Bool search_A_for_better_state( State S, int h, State *S_, int *h_ );
void add_to_search_space( State S, int op, int father );
int expand_H_first_node( int h );
int expand_A_first_node( int h );



void extract_plan_fragment( void );
int state_seen( int num );
Bool same_state( State *S1, State *S2 );
int state_sum( State S );



void hash_state( State S );
Bool state_hashed( State S );
void reset_hash_entrys( void );



void result_to_dest( State *dest, State source, int action );
void source_to_dest( State *dest, State source );
void print_state( State S );





#endif /* _SEARCH_H */
