#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "object.h"
#include "read.h"
#include "eval.h"
#include "print.h"
#include "primitive.h"

void init_primitive ( object env ) {

    make_and_modify_binding(env,"+",make_primitive(plus));
    make_and_modify_binding(env,"-",make_primitive(minus));
    make_and_modify_binding(env,"*",make_primitive(multiply));
    make_and_modify_binding(env,"quotient",make_primitive(quotient));

}

/* arithmetique */
object plus(object o) /* besoin en parametre l'obj dont le car est le 1er nombre à sommer ; retourne la somme en object*/
{
    int s=0;
    object obj_temp=o;
    while (obj_temp!=nil)
    {   if(isnumber(car(obj_temp)))
        {   s=s+get_number(car(obj_temp));
            obj_temp=cdr(obj_temp);
        }
        else {
            WARNING_MSG("needs only numbers as parameters");
            return NULL;
        }
    }
    return make_integer(s);
}

object minus(object o) /* renvoie x1 - ( x2 + x3 + ... xn) */
{

    object obj_temp=cdr(o);
    if (isnumber(car(o)))
    {
        int s=get_number(car(o));
        s=s-get_number(plus(obj_temp));
        return make_integer(s);
    }
    else {
        WARNING_MSG("needs only numbers as parameters");
        return NULL;
    }

}

object multiply(object o)
{
    int m=1;
    object obj_temp=o;
    while (obj_temp!=nil)
    {   if(isnumber(car(obj_temp)))
        {   m=m*get_number(car(obj_temp));
            obj_temp=cdr(obj_temp);
        }
        else {
            WARNING_MSG("needs only numbers as parameters");
            return NULL;
        }
    }
    return make_integer(m);

}

object quotient(object o)
{
    if (isnil(cddr(o)))
    {
        return NULL;
    }
    return NULL;
}
