

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
 * File: instantiateII.h
 * Description: headers for instantiating operators, second part.
 *
 *              - unify inertia in preconds with initial state
 *              - multiply remaining uninstantiated parameters
 *              - perform reachability analysis
 *              - collect relevant facts and perform final action cleanup
 *
 *
 * Author: Joerg Hoffmann 1999
 *
 *********************************************************************/ 







#ifndef _INSTANTIATEII_H
#define _INSTANTIATEII_H





void build_action_templates( void );
void unify_inertia_preconds( int curr_inertia );
void multiply_parameters( int curr_parameter );



void perform_reachability_analysis( void );
int fact_adress( void );



void collect_relevant_facts( void );



void build_connectivity_graph( void );



#endif /* _INSTANTIATEII_H */

