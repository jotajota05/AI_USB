
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
 * File: output.h
 * Description: print headers
 *
 * Author: Joerg Hoffmann 1999
 *
 *********************************************************************/ 





#ifndef _OUTPUT_H
#define _OUTPUT_H



void print_FactList( FactList *list, char *sepf, char *sept );
void print_hidden_tokenlist( TokenList *list, char *sep );
void print_indent( int indent );
void print_PlNode( PlNode *plnode, int indent );
void print_plops( PlOperator *plop );



void print_Fact( Fact *f ); 
void print_ft_name( int index );
void print_op_name( int index );
void print_Operator( Operator *o );
void print_Action( Action *a );



void print_plan( void );


#endif /* _OUTPUT_H */
