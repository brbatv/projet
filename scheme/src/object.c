
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
		p->this.special = p;
		return p;
		}
	else return nil;
    /*t->this.special = t;*/
}

object make_boolean (unsigned int i) {
	if(i == FALSE){
		if (false == NULL){
			object p = make_object(SFS_BOOLEAN);
			p->this.special = p;			
			return p;
			}
		else return false;
	}
	else if (true == NULL){
			object p = make_object(SFS_BOOLEAN);
			p->this.special = p;
			return p;
			}
		else return true;
		
}

object make_integer(int i) {
	
	object t = make_object(SFS_NUMBER);
	t->this.number.numtype = NUM_INTEGER;
	t->this.number.this.integer = i;
	return t;

}

object make_character(char c) {

	object t = make_object(SFS_CHARACTER);
	t->this.character=c;
	return t;

}

object make_string(char* s) {

	object t=make_object(SFS_STRING);
	strcpy(t->this.string,s);
	return t;

}

object make_symbol(char* s)
{ 	
	object t=make_object(SFS_SYMBOL);
	strcpy(t->this.symbol,s);
	return t;
}


object make_scharacter(char* s) 
{
object t= make_object(SFS_SCHARACTER);
strcpy(t->this.string,s);
return t;
}



object make_pair(object car , object cdr){

	object t = make_object(SFS_PAIR);
	t->this.pair.car = car;
	t->this.pair.cdr = cdr;
	return t;
}
