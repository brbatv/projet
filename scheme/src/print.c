
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

	}
	
    return;
}

void sfs_print_pair( object o ) {

    return;
}

void sfs_print( object o ) {

    if ( SFS_PAIR == o->type ) {
        sfs_print_pair( o );
    }
    else {
        sfs_print_atom( o );
    }

}
