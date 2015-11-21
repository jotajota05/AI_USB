
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
 * File: output.c
 * Description: printing info out
 *
 * Author: Joerg Hoffmann
 *
 *********************************************************************/ 





#include "ff.h"

#include "output.h"







/* parsing
 */







void print_FactList( FactList *list, char *sepf, char *sept )

{

  FactList *i_list;
  TokenList *i_tl;
    
  if ( list ) {
    i_tl = list->item;
    if (NULL == i_tl || NULL == i_tl->item) {
      printf("empty");
    } else {
      printf("%s", i_tl->item);
      i_tl = i_tl->next;
    }
    
    while (NULL != i_tl) {
      if (NULL != i_tl->item) {
	printf("%s%s", sept, i_tl->item);
      }
      i_tl = i_tl->next;
    }
    
    for ( i_list = list->next; i_list; i_list = i_list->next ) {
      printf("%s", sepf);
      i_tl = i_list->item;
      if (NULL == i_tl || NULL == i_tl->item) {
	printf("empty");
      } else {
	printf("%s", i_tl->item);
	i_tl = i_tl->next;
      }
      
      while (NULL != i_tl) {
	if (NULL != i_tl->item) {
	  printf("%s%s", sept, i_tl->item);
	}
	i_tl = i_tl->next;
      }
    }
  }

}



void print_hidden_TokenList( TokenList *list, char *sep )

{

  TokenList *i_tl;

  i_tl = list;
  if (NULL!=i_tl) {
    printf("%s", i_tl->item);
    i_tl = i_tl->next;
  } else {
    printf("empty");
  }
  
  while (NULL != i_tl) {
    printf("%s%s", sep, i_tl->item);
    i_tl = i_tl->next;
  }
  
}



void print_indent( int indent )

{

  int i;
  for (i=0;i<indent;i++) {
    printf(" ");
  }

}



void print_PlNode( PlNode *plnode, int indent )

{

  PlNode *i_son;

  if ( !plnode ) {
    printf("none\n");
    return;
  }
  
  switch (plnode->connective) {
  case ALL: 
    printf("ALL %s : %s\n", plnode->atom->item,
	    plnode->atom->next->item);
    print_indent(indent);
    printf("(   ");
    print_PlNode(plnode->sons,indent+4);
    print_indent(indent);
    printf(")\n");
    break;
  case EX:
    printf("EX  %s : %s\n", plnode->atom->item,
	    plnode->atom->next->item);
    print_indent(indent);
    printf("(   ");
    print_PlNode(plnode->sons,indent+4);
    print_indent(indent);
    printf(")\n");
    break;
  case AND: 
    printf("A(  ");
    print_PlNode(plnode->sons, indent+4);
    if ( plnode->sons ) {
      for ( i_son = plnode->sons->next; i_son!=NULL; i_son = i_son->next ) {
	print_indent(indent);
	printf("AND ");
	print_PlNode(i_son,indent+4);
      }
    }
    print_indent(indent);      
    printf(")\n");
    break;
  case OR:  
    printf("O(  ");
    print_PlNode(plnode->sons, indent+4);
    for ( i_son = plnode->sons->next; i_son!=NULL; i_son = i_son->next ) {
      print_indent(indent);
      printf("OR ");
      print_PlNode(i_son,indent+4);
    }
    print_indent(indent);      
    printf(")\n");
    break;
  case WHEN:
    printf("IF   ");
    print_PlNode(plnode->sons,indent+5);
    print_indent(indent);
    printf("THEN ");
    print_PlNode(plnode->sons->next,indent+5);
    print_indent(indent);
    printf("ENDIF\n");
    break;
  case NOT:
    if (ATOM==plnode->sons->connective) {
      printf("NOT ");
      print_PlNode(plnode->sons,indent+4);
    } else {
      printf("NOT(");
      print_PlNode(plnode->sons,indent+4);
      print_indent(indent+3);
      printf(")\n");
    }
    break;
  case ATOM:
    printf("(");
    print_hidden_TokenList(plnode->atom, " ");
    printf(")\n");
    break;
  default:
    printf("\n***** ERROR ****");
    printf("\nprint_plnode: %d > Wrong Node specifier\n", plnode->connective);
    exit(1);
  }     

} 



void print_plops( PlOperator *plop )

{

  PlOperator *i_plop;
  int count = 0;

  if ( !plop ) {
    printf("none\n");
  }

  for ( i_plop = plop; i_plop!=NULL; i_plop = i_plop->next ) {
    printf("\nOPERATOR ");
    printf("%s", i_plop->name);
    printf("\nparameters:\n");
    print_FactList ( i_plop->params, "\n", " : ");
    printf("\n\npreconditions:\n");
    print_PlNode(i_plop->preconds, 0);
    printf("effects:\n");
    print_PlNode(i_plop->effects, 0);
    printf("\n-----\n");
    count++;
  }
  printf("\nAnzahl der Operatoren: %d\n", count);

}







/* facts and actions
 */








void print_Fact( Fact *f )

{

  int j;

  if ( f->predicate == -1 ) {
    printf("=(");
    for ( j=0; j<2; j++ ) {
      if ( f->args[j] >= 0 ) {
	printf("%s", gconstants[(f->args)[j]]);
      } else {
	printf("x%d", DECODE_VAR( f->args[j] ));
      }
      if ( j < 1) {
	printf(" ");
      }
    }
    printf(")");
    return;
  }
    
  printf("%s(", gpredicates[f->predicate]);
  for ( j=0; j<garity[f->predicate]; j++ ) {
    if ( f->args[j] >= 0 ) {
      printf("%s", gconstants[(f->args)[j]]);
    } else {
      printf("x%d", DECODE_VAR( f->args[j] ));
    }
    if ( j < garity[f->predicate] - 1 ) {
      printf(" ");
    }
  }
  printf(")");

}



void print_ft_name( int index )

{

  print_Fact( &(grelevant_facts[index]) );

}



void print_op_name( int index )

{

  int i;

  if ( goperators[gop_conn[index].op]->name ) {
    printf("%s", goperators[gop_conn[index].op]->name);
  }
  for ( i=0; i<goperators[gop_conn[index].op]->num_vars; i++ ) {
    printf(" %s", gconstants[gop_conn[index].inst_table[i]]);
  }

}



void print_Operator( Operator *o )

{

  int i, j, t;

  printf("\nCoded Operator %s, parameters:", o->name);

  for ( i=0; i<o->num_vars; i++ ) {
    printf("\nx%d: ", i);
    t = o->var_types[i];
    if ( gpredicate_to_type[t] == -1 ) {
      if ( gnum_intersected_types[t] == -1 ) {
	printf("%s", gtype_names[t]);
      } else {
	printf("INTERSECTED TYPE (");
	for ( j = 0; j < gnum_intersected_types[t]; j++ ) {
	  if ( gpredicate_to_type[gintersected_types[t][j]] == -1 ) {
	    printf("%s", gtype_names[gintersected_types[t][j]]);
	  } else {
	    printf("UNARY INERTIA TYPE (%s)", 
		   gpredicates[gpredicate_to_type[gintersected_types[t][j]]]);
	  }
	  if ( j < gnum_intersected_types[t] - 1 ) {
	    printf(" and ");
	  }
	}
	printf(")");
      }
    } else {
      printf("UNARY INERTIA TYPE (%s)", gpredicates[gpredicate_to_type[t]]);
    }
  }
  printf("\n");

  printf("\ninstantiation:");
  for ( i=0; i<o->num_vars; i++ ) {
    printf("\nx%d = %s", i, 
	   ( o->inst_table[i] >= 0 ) ? gconstants[o->inst_table[i]] : "?");
  }
  printf("\n");

  printf("\npreconditions:");
  for ( i = 0; i < o->num_preconds; i++ ) {
    printf("\n");
    print_Fact( &(o->preconds[i]) );
  }
  printf("\n");

  printf("\nadds:");
  for ( i = 0; i < o->num_adds; i++ ) {
    printf("\n");
    print_Fact( &(o->adds[i]) );
  }
  printf("\n");

  printf("\ndels:");
  for ( i = 0; i < o->num_dels; i++ ) {
    printf("\n");
    print_Fact( &(o->dels[i]) );
  }
  printf("\n");

}



void print_Action( Action *a )

{

  int i;
  Operator *o = goperators[a->op];

  printf("\nCoded Action %s ", o->name);
  for ( i = 0; i < o->num_vars; i++ ) {
    printf("%s ", gconstants[a->inst_table[i]]);
  }
  printf("\n");

  printf("\npreconditions:");
  for ( i = 0; i < a->num_preconds; i++ ) {
    printf("\n");
    print_ft_name( a->preconds[i] );
  }
  printf("\n");

  printf("\nadds:");
  for ( i = 0; i < a->num_adds; i++ ) {
    printf("\n");
    print_ft_name( a->adds[i] );
  }
  printf("\n");

  printf("\ndels:");
  for ( i = 0; i < a->num_dels; i++ ) {
    printf("\n");
    print_ft_name( a->dels[i] );
  }
  printf("\n");

}







/* non trivial output routines
 */








void print_plan( void )

{

  int i;

  printf("\nff: found legal plan as follows");
  printf("\n\nstep ");
  for ( i = 0; i < gnum_plan_ops; i++ ) {
    printf("%4d: ", i);
    print_op_name( gplan_ops[i] );
    printf("\n     ");
  }

}
