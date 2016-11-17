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
    if (number_of_pair(o)>=2)
    {
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
    else {
        WARNING_MSG("needs at least 2 parameters");
        return NULL;
    }
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
        else {
            WARNING_MSG("needs only numbers as parameters");
            return NULL;
        }
    }
    else {
        WARNING_MSG("needs at least 2 parameters");
        return NULL;
    }
}

object multiply(object o)
{
    int m=1;
    object obj_temp=o;
    if (number_of_pair(o)>=1)
    {


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
    else {
        WARNING_MSG("neeed at least 1 parameters");
        return NULL;
    }
}

object quotient(object o)
{
    if (number_of_pair(o)>=2)
    {   int q=get_number(car(o));
        object obj_temp=cdr(o);
        while(obj_temp!=nil)
        {
            int q=q/get_number(car(obj_temp));
        }
        return make_integer(q);
    }
    else if (number_of_pair(o)==1)
    {   int q=get_number(car(o));
        return make_integer(1/q);
    }
    else {
        DEBUG_MSG("needs at least 1 parameters");
        return NULL;
    }
}


object superior(object o)
{
    if (number_of_pair(o)>=2)
    {   object obj_temp=o;
        int num_temp=0;
        object resultat=true;
        while (obj_temp !=nil && isnumber(obj_temp))
        {
            num_temp=get_number(car(obj_temp));
            obj_temp=cdr(obj_temp);
            if (obj_temp!=nil)
            {
                if (num_temp<get_number(car(obj_temp)))
                {
                    obj_temp=nil;
                    resultat=false;


                }
            }

        }
        return resultat;
    }
    else {
        DEBUG_MSG("needs at least 2 parameters and only numbers");
        return NULL;
    }


}

object inferior(object o)
{
    if (number_of_pair(o)>=2)
    {   object obj_temp=o;
        int num_temp=0;
        object resultat=true;
        while (obj_temp !=nil && isnumber(obj_temp))
        {
            num_temp=get_number(car(obj_temp));
            obj_temp=cdr(obj_temp);
            if (obj_temp!=nil)
            {
                if (num_temp>get_number(car(obj_temp)))
                {
                    obj_temp=nil;
                    resultat=false;


                }
            }

        }
        return resultat;
    }
    else {
        DEBUG_MSG("needs at least 2 parameters and only numbers");
        return NULL;
    }


}



/* object remainder(object o); */

object boolean_p(object o)
{
    object resultat=true;
    object obj_temp=o;
    if (number_of_pair(o)>=1)
    {
    while (obj_temp!=nil)
    {
        if(!isboolean(car(obj_temp)))
        {
            resultat=false;
            obj_temp=nil;
        }
        else {obj_temp=cdr(obj_temp);}
    }
    return resultat;
    }
    else{DEBUG_MSG("needs at least 1 parameter"); return NULL;}

}


object symbol_p(object o)
{
    object resultat=true;
    object obj_temp=o;
    if (number_of_pair(o)>=1)
    {
    while (obj_temp!=nil)
    {
        if(!issymbol(car(obj_temp)))
        {
            resultat=false;
            obj_temp=nil;
        }
        else {obj_temp=cdr(obj_temp);}
    }
    return resultat;
    }
    else{DEBUG_MSG("needs at least 1 parameter"); return NULL;}

}


object integer_p(object o)
{
    object resultat=true;
    object obj_temp=o;
    if (number_of_pair(o)>=1)
    {
    while (obj_temp!=nil)
    {
        if(!isnumber(car(obj_temp)))
        {
            resultat=false;
            obj_temp=nil;
        }
        else {obj_temp=cdr(obj_temp);}
    }
    return resultat;
    }
    else{DEBUG_MSG("needs at least 1 parameter"); return NULL;}

}


object char_p(object o)
{
    object resultat=true;
    object obj_temp=o;
    if (number_of_pair(o)>=1)
    {
    while (obj_temp!=nil)
    {
        if(!ischar(car(obj_temp)))
        {
            resultat=false;
            obj_temp=nil;
        }
        else {obj_temp=cdr(obj_temp);}
    }
    return resultat;
    }
    else{DEBUG_MSG("needs at least 1 parameter"); return NULL;}

}


object string_p(object o)
{
    object resultat=true;
    object obj_temp=o;
    if (number_of_pair(o)>=1)
    {
    while (obj_temp!=nil)
    {
        if(!isstring(car(obj_temp)))
        {
            resultat=false;
            obj_temp=nil;
        }
        else {obj_temp=cdr(obj_temp);}
    }
    return resultat;
    }
    else{DEBUG_MSG("needs at least 1 parameter"); return NULL;}

}


object pair_p(object o)
{
    object resultat=true;
    object obj_temp=o;
    if (number_of_pair(o)>=1)
    {
    while (obj_temp!=nil)
    {
        if(!ispair(car(obj_temp)))
        {
            resultat=false;
            obj_temp=nil;
        }
        else {obj_temp=cdr(obj_temp);}
    }
    return resultat;
    }
    else{DEBUG_MSG("needs at least 1 parameter"); return NULL;}

}

object null_p(object o)
{
    object resultat=true;
    if (number_of_pair(o)==1)
    {
        if (car(o)!=nil)
        {
            resultat=false;
        }
        return resultat;
    }
    else {DEBUG_MSG("needs only one parameter"); return NULL;}
}

