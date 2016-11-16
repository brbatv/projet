#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "object.h"
#include "read.h"
#include "eval.h"
#include "print.h"
#include "primitive.h"

void init_primitive ( object env ){

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
    if (number_of_pair(o)>=2)
    {
    while (obj_temp!=nil)
    {   if(isnumber(car(obj_temp)))
        {s=s+get_number(car(obj_temp));
        obj_temp=cdr(obj_temp);
        }
        else {WARNING_MSG("needs only numbers as parameters"); return NULL;}
    }
    return make_integer(s);}
    else {WARNING_MSG("needs at least 2 parameters"); return NULL;}
}

object minus(object o) /* renvoie x1 - ( x2 + x3 + ... xn) */
{

    object obj_temp=cdr(o);
    if (number_of_pair(o)>=2)
    {


    if (isnumber(car(o)))
    {
        int s=get_number(car(o));
         s=s-get_number(plus(obj_temp));
    return make_integer(s);
    }
    else {WARNING_MSG("needs only numbers as parameters"); return NULL;}
    }
    else {WARNING_MSG("needs at least 2 parameters");  return NULL;}
}

object multiply(object o)
{
    int m=1;
    object obj_temp=o;
    if (number_of_pair(o)>=1)
    {


    while (obj_temp!=nil)
    {   if(isnumber(car(obj_temp)))
        {m=m*get_number(car(obj_temp));
        obj_temp=cdr(obj_temp);
        }
        else {WARNING_MSG("needs only numbers as parameters"); return NULL;}
    }
    return make_integer(m);
    }
    else {WARNING_MSG("neeed at least 1 parameters"); return NULL;}
}

object quotient(object o)
{
    if (number_of_pair(o)>=2)
    {   int q=get_number(car(o));
        object obj_temp=cdr(o);
        while(obj_temp!=nil)
        {
        int q=q/car(obj_temp);
        }
        return make_integer(q);
    }
    else if (number_of_pair(o)==1)
    {   int q=get_number(car(o));
        return make_integer(1/q);
    }
    else {DEBUG_MSG("needs at least 1 parameters"); return NULL;}
}


/* object superior(object o)
{
    if (number_of_pair(o)>=2)
    { object obj_temp=o;
        for (i=0;i<5;i++)
        { if (get_number(car(obj_temp)) >= get_number(cadr(obj_temp)))
            {
                obj_temp=cdr(obj)
            }




        }





    }

}
*/
