
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

    DEBUG_MSG("Printing some %s",whattype(o));
    if (o==NULL) {
        return;
    }
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
    case SFS_COMPOUND:
	printf("#<procedure>");
	break;
    case SFS_PRIMITIVE:
	printf("#<Function>");
	break;
    }

    return;
}

void sfs_print_pair( object o) {
    DEBUG_MSG("Printing a pair...");
    printf("(");
    while (o != nil) {
        if (isatom(cdr(o)) && !isnil(cdr(o)))
        {   DEBUG_MSG("is it a cons ?");
            sfs_print(car(o));
            printf(".");
            sfs_print(cdr(o));
            printf(")");
            return;
        }
        sfs_print( car( o ) ) ;
        o = cdr( o );
        if(o != nil)
            printf(" ");
    }
    printf(")");
    return;
}

void sfs_print( object o) {

    if (ispair( o ) ) {
        sfs_print_pair( o );
    }
    else {
        sfs_print_atom( o );
    }
}

void print_env(object env)
{   DEBUG_MSG("Printing env");
    object obj_temp=car(env);
    while(obj_temp!=nil)
    {   sfs_print_atom(caar(obj_temp));
        printf("\t ");
        obj_temp=cdr(obj_temp);
    }
    obj_temp=car(env);
    printf("\n");
    while(obj_temp!=nil)
    {
        sfs_print_atom(cdar(obj_temp));
        printf("\t");
        obj_temp=cdr(obj_temp);
    }
    printf("\n");
}
