
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
 * File: memory.c
 * Description: Creation and Deletion functions for all data structures.
 *
 * Author: Joerg Hoffmann
 *
 *********************************************************************/ 









#include "ff.h"
#include "memory.h"









/**********************
 * CREATION FUNCTIONS *
 **********************/











/* parsing
 */









char *new_Token( int len )

{

  char *tok = ( char * ) calloc( len, sizeof( char ) );
  CHECK_PTR(tok);

  return tok;

}



TokenList *new_TokenList( void )

{

  TokenList *result = ( TokenList * ) calloc( 1, sizeof( TokenList ) );
  CHECK_PTR(result);

  result->item = NULL; 
  result->next = NULL;

  return result;

}



FactList *new_FactList( void )

{

  FactList *result = ( FactList * ) calloc( 1, sizeof( FactList ) );
  CHECK_PTR(result);

  result->item = NULL; 
  result->next = NULL;

  return result;

}



PlNode *new_PlNode( Connective c )

{

  PlNode *result = ( PlNode * ) calloc( 1, sizeof( PlNode ) );
  CHECK_PTR(result);

  result->connective = c;
  result->atom = NULL;
  result->sons = NULL;
  result->next = NULL;

  return result;

}



PlOperator *new_PlOperator( char *name )

{

  PlOperator *result = ( PlOperator * ) calloc( 1, sizeof( PlOperator ) );
  CHECK_PTR(result);

  if ( name ) {
    result->name = new_Token(strlen(name)+1);
    CHECK_PTR(result->name);
    strcpy(result->name, name);
  } else {
    result->name = NULL;
  }

  result->params = NULL;
  result->preconds = NULL;
  result->effects = NULL;
  result->number_of_real_params = 0;
  result->next = NULL;

  return result;

}



PlOperator *new_axiom_op_list( void )

{

  static int count;
  char *name;
  PlOperator *ret;

  /* WARNING: count should not exceed 999 
   */
  count++;
  if ( count == 10000 ) {
    printf("\ntoo many axioms! look into memory.c, line 157\n\n");
    exit( 1 );
  }
  name = new_Token(strlen(HIDDEN_STR)+strlen(AXIOM_STR)+4+1);
  sprintf(name, "%s%s%4d", HIDDEN_STR, AXIOM_STR, count);

  ret = new_PlOperator(name);
  free(name);

  return ret;

}



type_tree new_type_tree( char *name )

{

  type_tree act_type;
  
  if (!name) {
    return NULL;
  }

  act_type = ( type_tree ) calloc( 1, sizeof( type_tree_elt ) );
  CHECK_PTR(act_type);

  act_type->name = new_Token( strlen( name ) + 1 );
  strcpy( act_type->name, name );
  act_type->sub_types = NULL;

  return act_type;

}



type_tree_list new_type_tree_list( char *name )

{

  type_tree_list act_type_list;
  
  act_type_list = ( type_tree_list ) calloc( 1, sizeof( type_tree_list_elt ) );
  CHECK_PTR(act_type_list);

  if ( name ) {
    act_type_list->item = new_type_tree( name );
  } else {
    act_type_list->item = NULL;
  }

  act_type_list->next = NULL;
  
  return act_type_list;

}









/* instantiation
 */









Operator *new_Operator( char *name, int norp )

{

  int i;

  Operator *result = ( Operator * ) calloc( 1, sizeof( Operator ) );
  CHECK_PTR(result);

  if ( name ) {
    result->name = new_Token( strlen( name ) + 1 );
    CHECK_PTR( result->name );
    strcpy( result->name, name );
  } else {
    result->name = NULL;
  }

  result->num_vars = 0;
  result->number_of_real_params = norp;

  for ( i = 0; i < MAX_VARS; i++ ) {
    result->inst_table[i] = -1;
  }

  result->num_preconds = 0;
  result->num_adds = 0;
  result->num_dels = 0;

  result->out = FALSE;

  return result;

}



ActionTemplate *new_ActionTemplate( int op )

{

  ActionTemplate *result = ( ActionTemplate * ) calloc( 1, sizeof( ActionTemplate ) );
  CHECK_PTR(result);

  result->op = op;

  result->next = NULL;

  return result;

}

 

Action *new_Action( int op )

{

  Action *result = ( Action * ) calloc( 1, sizeof( Action ) );
  CHECK_PTR(result);

  result->op = op;

  result->num_preconds = 0;
  result->num_adds = 0;
  result->num_dels = 0;

  result->next = NULL;

  return result;

}





/* others
 */








StateHashEntry *new_StateHashEntry( void )

{

  StateHashEntry *result = ( StateHashEntry * ) calloc( 1, sizeof( StateHashEntry ) );
  CHECK_PTR(result);

  result->next = NULL;

  return result;

}

  








/**********************
 * DELETION FUNCTIONS *
 **********************/












void free_TokenList( TokenList *source )

{

  if ( source ) {
    free_TokenList( source->next );
    if ( source->item ) {
      free( source->item );
    }
    free( source );
  }

}



void free_FactList( FactList *source )

{

  if ( source ) {
    free_FactList( source->next );
    free_TokenList( source->item );
    free( source );
  }

}



void free_PlNode( PlNode *node )

{
  
  if ( node ) {
    free_PlNode( node->sons );
    free_PlNode( node->next );
    free_TokenList( node->atom );
    free( node );
  }

}



void free_PlOperator( PlOperator *o )

{

  if ( o ) {
    free_PlOperator( o->next );

    if ( o->name ) {
      free( o->name );
    }
    
    free_FactList( o->params );
    free_PlNode( o->preconds );
    free_PlNode( o->effects );

    free( o );
  }

}



void free_Operator( Operator *o )

{

  if ( o ) {

    if ( o->name ) {
      free( o->name );
    }

    free( o );
  } 

}



void free_single_ActionTemplate( ActionTemplate *t )

{

  if ( t ) {
    free( t );
  }

}
