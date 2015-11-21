

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
 * File: instantiateI.h
 * Description: headers for instantiating operators, first part.
 *              - transform domain into integers
 *              - domain cleanup functions
 *              - inertia preprocessing:
 *                  - collect inertia info
 *                  - split initial state in special arrays
 *                  - encode unary inertia as types
 *
 * Author: Joerg Hoffmann 1999
 *
 *********************************************************************/ 







#ifndef _INSTANTIATEI_H
#define _INSTANTIATEI_H



void encode_domain_in_integers( void );
void collect_all_strings( void );
int position_in_types_table( char *str );
int position_in_constants_table( char *str );
int position_in_predicates_table( char *str );
void create_integer_representation( void );
void make_Fact( Fact *f, PlNode *n, Operator *o );
Bool is_subtype( int t1, int t2 );
void cleanup_domain( void );
void replace_var_entries( Operator *o, int p0, int p1 );
void remove_identical_preconds_and_effects( Operator *o );
Bool identical_fact( Fact *f1, Fact *f2 );
void remove_unused_parameters( void );
void decrement_var_entries( Operator *o, int start );



void do_inertia_preprocessing( void );
void collect_inertia_information( void );
void split_initial_state( void );
void encode_unary_inertia_as_types( void );
int find_intersected_type( TypeArray T, int num_T );
void remove_ops_with_empty_parameter_types( void );



#endif /* _INSTANTIATEI_H */

