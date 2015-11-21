
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
 * File: memory.h
 * Description: Creation / Deletion functions for all data structures.
 *
 * Author: Joerg Hoffmann / Frank Rittinger
 *
 *********************************************************************/ 






#ifndef _MEMORY_H
#define _MEMORY_H





char *new_Token( int len );
TokenList *new_TokenList( void );
FactList *new_FactList( void );
PlNode *new_PlNode( Connective c );
PlOperator *new_PlOperator( char *name );
PlOperator *new_axiom_op_list( void );
type_tree new_type_tree( char *name );
type_tree_list new_type_tree_list( char *name );



Operator *new_Operator( char *name, int norp );
ActionTemplate *new_ActionTemplate( int op );
Action *new_Action( int op );



StateHashEntry *new_StateHashEntry( void );





void free_TokenList( TokenList *source );
void free_FactList( FactList *source );
void free_PlNode( PlNode *node );
void free_PlOperator( PlOperator *o );
void free_Operator( Operator *o );
void free_single_ActionTemplate( ActionTemplate *t );





#endif /* _MEMORY_H */
