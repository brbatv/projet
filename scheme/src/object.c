
/**
 * @file object.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 18:02:57 2012
 * @brief Object definitions for SFS.
 *
 * Object definitions for SFS.
 */

#include "object.h"
#include "mem.h"


object make_object( uint type ) {

    object t = sfs_malloc( sizeof( *t ) );

    t->type = type;

    return t;
}

/*fonction qui alloue nil la 1ere fois et qui retourne celle ci ensuite */
object make_nil( void ) {
	
	if(nil == NULL){
		object p = make_object(SFS_NIL);
		return p;
		}
	else return nil;
    /*t->this.special = t;*/
}

/*object make_boolean (unsigned int i) {
	if(i == 0){
		if (faux == NULL){
			object p = make_object(SFS_BOOLEAN);
		

}*/

object make_integer(int i) {
	
	object t = make_object(SFS_NUMBER);
	t->this.number.numtype = NUM_INTEGER;
	t->this.number.this.integer = i;
	return t;

}
