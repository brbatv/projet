
/**
 * @file print.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:12:17 2012
 * @brief Printing stuff for SFS.
 *
 * Printing stuff for SFS.
 */

#include "print.h"

#include <stdio.h>

void sfs_print_atom( object o ) {
	
	switch(o->type)

	{
	case SFS_NUMBER:
	printf("%ld",o->this.number.this.integer);
	break;

	case SFS_BOOLEAN:
	if (o==true) printf("#t");
	if (o==false) printf("#f");
	break;

	case SFS_NIL:
	printf("()");
	break;
	
	case SFS_CHARACTER:

	if(o->this.character == ' ')
		printf("#\\space");
	else if (o->this.character == '\n')
		printf("#\\newline");
	else 
		printf("#\\%c",o->this.character); 
	break;

	case SFS_STRING:
	printf("\"%s\"",o->this.string);
	break;
	case SFS_SYMBOL:
	printf("%s",o->this.symbol);
	break;	
	}
	
    return;
}

void sfs_print_pair( object o, uint * root) {

if (ispair( car( o ) )){
	printf("(");
	}
	sfs_print( car( o ) , root);
	if (cdr( o ) != nil){
		printf(" ");
		sfs_print_pair( cdr( o ) , root);		
		}
	else printf(")");
    return;
}

void sfs_print( object o , uint * root) {

    if (ispair(o) ) {
	if (*root == TRUE){
	   printf("(");
	   *root = FALSE;
           }
        sfs_print_pair( o , root );
    }
    else {
        sfs_print_atom( o );
    }
}
