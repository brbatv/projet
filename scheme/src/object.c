
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


/*fonction qui récupère la chaine de caractère d'un objet de type symbole et la copie dans string passe en entree. */
char* get_symbol (object symbol,char* string)
{
    strcpy(string,symbol->this.symbol);
    return string;
}

/*fonction qui récupère la chaine de caractère d'un objet de type string et la copie dans string passe en entree. */
char* get_string (object o,char* str)
{
    strcpy(str,o->this.string);
    return str;
}

int get_number (object o)
{   return o->this.number.this.integer;
}

char get_character (object o)
{   return o->this.character;
}


/*retourne le car de la pair object o, nil si object o n'est pas une pair */
object car(object o) {

    if (ispair(o))
    {
        return o->this.pair.car;
    }
    else {
        DEBUG_MSG("CALLING THE CAR OF AN ATOM");
        return nil;
    }

}

/*retourne le cdr de la pair object o, nil si object o n'est pas une pair */
object cdr(object o) {
    if (ispair(o))
    {
        return o->this.pair.cdr;
    }
    else {
        DEBUG_MSG("CALLING THE CDR OF AN ATOM");
        return nil;
    }

}

object caar(object o)
{
    return car(car(o));
}
object cadr(object o)
{
    return car(cdr(o));
}
object cddr(object o)
{
    return cdr(cdr(o));
}
object cdar(object o)
{
    return cdr(car(o));
}
object cdddr(object o)
{
    return cdr(cddr(o));
}
object caddr(object o)
{
    return car(cddr(o));
}
object cadddr(object o)
{
    return car(cdddr(o));
}

int number_of_pair(object o) /* nombre de paires jusqu'au nil*/
{
    int n=0;
    object obj_temp=o;
    while (ispair(obj_temp))
    {
        n=n+1;
        obj_temp=cdr(obj_temp);
    }
    return n;
}

object modify_car(object o, object car)
{   o->this.pair.car=car;
    return o;
}
object modify_cdr(object o, object cdr)
{   o->this.pair.cdr=cdr;
    return o;
}

char* whattype(object o)
{
    if (o==NULL)
    {
        return NULL;
    }
    if (o->type==SFS_SYMBOL) {
        return "symbol";
    }
    if (o->type==SFS_PAIR) {
        return "pair";
    }
    if (o->type==SFS_BOOLEAN) {
        return "boleean";
    }
    if (o->type==SFS_CHARACTER) {
        return "character";
    }
    if (o->type==SFS_STRING) {
        return "string";
    }
    if (o->type==SFS_NIL) {
        return "nil";
    }
    if (o->type==SFS_NUMBER) {
        return "number";
    }
    return "No type recognised";

}

