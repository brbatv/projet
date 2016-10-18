
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
     DEBUG_MSG("Making a char");
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
    object t = make_object(SFS_PAIR);
    t->this.pair.car = car;
    t->this.pair.cdr = cdr;
    return t;
}


/* fonction qui permet de creer un nouvel environnement sous cdr */
object make_env(object cdr){
    DEBUG_MSG("Making a new environnement");
    return make_pair(nil,cdr);}

/*fonction qui permet de créer un nouveau binding en fin d'environnement, avec une valeur encore vide + le nouveau nil en fin d'environnement*/
object make_binding(char* name, object environment){
 DEBUG_MSG("Making a new binding...");
  object obj_temp=car(environment);
  while (cdr(obj_temp)!=nil)
    {
    obj_temp=cdr(obj_temp);
    }
    obj_temp=make_pair(nil,nil);
    obj_temp=car(obj_temp);
    obj_temp=make_pair(make_symbol(name),nil); /* le cdr nil de cette ligne sera remplace par la valeur prise par la variable plus tard ie cdr(make_binding(name,env))=valeur*/
    DEBUG_MSG("Binding created successfully : name of variable is %s.",name);
    return obj_temp; /* renvoie la paire tq car (paire) = nom variable et cdr (paire) = nil*/
}

object search_env(char* name, object env)
{ DEBUG_MSG("Searching %s in environment...",name);
 object obj_temp=car(env);
 string string;
 if (obj_temp==nil)
    {
    DEBUG_MSG("Environment is empty you stupid. Returning NIL");
    return nil;
    }
while (ispair(obj_temp))
    {
        if(get_symbol(caar(obj_temp),string)==name)
        {
            DEBUG_MSG("%s has been found !",name);
            return car(obj_temp);
        }
        obj_temp=cdr(obj_temp); /* a la fin du while obj_temp vaudra nil S et ne sera plus une paire*/
    }

return nil;
}

object search_under(char* name,object env){
object env_temp=env;

while (env_temp!=nil)
    {
    if (search_env(name,env)!=nil)
        {
        return search_env(name,env);
        }
     env_temp=cdr(env_temp);
    }
return nil;

}


/*fonction qui récupère la chaine de caractère d'un objet de type symbole et la copie dans string passe en entree. On pourrait utiliser strcmp aussi surement*/
char* get_symbol (object symbol,char* string)
{

    strcpy(string,symbol->this.symbol);
    return string;
}
/*fonction qui test si l'objet est une pair*/
int ispair(object o) {

    if (o->type == 	SFS_PAIR)
        return TRUE;
    else return FALSE;

}

/*fonction qui test si l'objet est un atom*/
int isatom(object o) {

    return !ispair(o);

}

/*retourne le car de la pair object o, nil si object o n'est pas une pair aisni qu'un message d'erreur*/
object car(object o) {

    if (ispair(o))
        return o->this.pair.car;
    else {
        WARNING_MSG("CALLING THE CAR OF AN ATOM");
        return nil;
    }

}

/*retourne le cdr de la pair object o, nil si object o n'est pas une pair aisni qu'un message d'erreur*/
object cdr(object o) {

    if (ispair(o))
        return o->this.pair.cdr;
    else {
        WARNING_MSG("CALLING THE CDR OF AN ATOM");
        return nil;
    }

}

object caar(object o)
{return car(car(o));}
object cadr(object o)
{return car(cdr(o));}
object cddr(object o)
{return cdr(cdr(o));}
object cdar(object o)
{return cdr(car(o));}

char* whattype(object o)
{if (o->type==SFS_SYMBOL)
    {
    return "symbol";
    }
if (o->type==SFS_PAIR) {return "pair";}
if (o->type==SFS_BOOLEAN) {return "boleean";}
if (o->type==SFS_CHARACTER) {return "character";}
if (o->type==SFS_STRING){return "string";}
if (o->type==SFS_NIL) {return "nil";}
if (o->type==SFS_NUMBER) {return "number";}
return "No type recognised";
}
/*fonction qui renvoie un booleen en fonction de si oui ou non o est le symbole quote*/
int isquote(object o) {

    if(o->type == SFS_SYMBOL && strcmp(o->this.symbol,"quote") == 0)
        return TRUE;
    else
        return FALSE;

}

/*fonction qui renvoie un booleen en fonction de si oui ou non o est le symbole define*/
int isdefine(object o) {

    if(o->type == SFS_SYMBOL && strcmp(o->this.symbol,"define") == 0)
        return TRUE;
    else
        return FALSE;

}

/*fonction qui renvoie un booleen en fonction de si oui ou non o est le symbole set!*/
int isset(object o) {

    if( o->type == SFS_SYMBOL && strcmp(o->this.symbol,"set!") == 0)
        return TRUE;
    else
        return FALSE;

}

/*fonction qui renvoie un booleen en fonction de si oui ou non o est le symbole if*/
int isif(object o) {

    if(o->type == SFS_SYMBOL && strcmp(o->this.symbol,"if") == 0)
        return TRUE;
    else
        return FALSE;

}

/*fonction qui renvoie un booleen en fonction de si oui ou non o est le symbole and*/
int isand(object o) {

    if(o->type == SFS_SYMBOL && strcmp(o->this.symbol,"and") == 0)
        return TRUE;
    else
        return FALSE;

}

/*fonction qui renvoie un booleen en fonction de si oui ou non o est le symbole or*/
int isor(object o) {

    if(o->type == SFS_SYMBOL && strcmp(o->this.symbol,"or") == 0)
        return TRUE;
    else
        return FALSE;

}
