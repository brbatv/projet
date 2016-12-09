#include "object.h"
#include "mem.h"


object make_object( uint type ) {

    object t = sfs_malloc( sizeof( *t ) );

    t->type = type;

    return t;
}

/*fonction qui alloue nil la 1ere fois et qui retourne celle ci ensuite */
object make_nil( void ) {

    if(nil == NULL) {
        object p = make_object(SFS_NIL);
        p->this.special = p;
        return p;
    }
    else return nil;
    /*t->this.special = t;*/
}

/*fonction qui alloue true ou fasle selon l'argument i a la 1ere fois occurence
et qui retourne respectivement true et false aux occurences suivantes */
object make_boolean (unsigned int i) {
    if(i == FALSE) {
        if (false == NULL) {
            object p = make_object(SFS_BOOLEAN);
            p->this.special = p;
            return p;
        }
        else return false;
    }
    else if (true == NULL) {
        object p = make_object(SFS_BOOLEAN);
        p->this.special = p;
        return p;
    }
    else return true;

}

object make_integer(int i) {
    DEBUG_MSG("Making an int");
    object t = make_object(SFS_NUMBER);
    t->this.number.numtype = NUM_INTEGER;
    t->this.number.this.integer = i;
    return t;

}

object make_character(char c) {
    DEBUG_MSG("Making %c as a char",c);
    object t = make_object(SFS_CHARACTER);
    t->this.character=c;
    return t;

}

object make_string(char* s) {
    DEBUG_MSG("Making %s as a string...",s);
    object t=make_object(SFS_STRING);
    strcpy(t->this.string,s);
    return t;

}

object make_symbol(char* s) {
    DEBUG_MSG("Making %s as a symbol... ",s);
    object t=make_object(SFS_SYMBOL);
    strcpy(t->this.symbol,s);
    return t;

}


object make_pair(object car , object cdr ) {
    DEBUG_MSG("Making a pair of %s and %s ...",whattype(car),whattype(cdr));
    if(car == NULL || cdr == NULL)
    {
        return NULL;
    }
    object t = make_object(SFS_PAIR);
    t->this.pair.car = car;
    t->this.pair.cdr = cdr;
    return t;
}

object make_primitive(object(*function)(object)) {
    object prim = make_object(SFS_PRIMITIVE);
    prim->this.primitive = function;
    return prim;

}


/* fonction qui permet de creer un nouvel environnement sous l'environnement env */
object make_env(object env) {
    DEBUG_MSG("Making a new environnement");
    return make_pair(nil,env);
}

object make_compound(object parameters, object body, object environnement)
{
    object o=make_object(SFS_COMPOUND);
    o->this.compound.parms=parameters;
    o->this.compound.body=body;
    o->this.compound.envt=environnement;
    return o;
}

/* fonction qui permet de crer un objet sans type */
object make_no_type(void){
	DEBUG_MSG("Making a no type object");
	return make_object(SFS_NO_TYPE);
}
	
