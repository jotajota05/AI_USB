
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
 * File: parse.h
 * Description: Functions for the pddl parser
 *
 * Author: Frank Rittinger 1998 / Joerg Hoffmann 1999
 *
 *********************************************************************/ 





#ifndef _PARSE_H
#define _PARSE_H





type_tree main_type_tree( void );
type_tree find_branch( char *name, type_tree root );
void add_to_type_tree( FactList *t_list, type_tree tree );



void build_orig_constant_list( void );
FactList * build_object_list_from_ttl(type_tree_list ttl, 
				      FactList * types_done );
TokenList *type_already_known( char *name, FactList * types );



char *copy_Token( char *s );
TokenList *copy_complete_TokenList( TokenList *source, 
				    TokenList **end );
void strupcase( char *from );
char *rmdash( char *s );



Bool make_strips_domain( void );
Bool make_conjunction_of_atoms( PlNode **n );
Bool make_conjunction_of_literals( PlNode **n );





#endif /* PARSE */
