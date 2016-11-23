#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "object.h"
#include "read.h"
#include "eval.h"
#include "print.h"
#include "primitive.h"

void init_primitive ( object env ) {

    /* arithmetique */
    make_and_modify_binding(env,"+",make_primitive(plus));
    make_and_modify_binding(env,"-",make_primitive(minus));
    make_and_modify_binding(env,"*",make_primitive(multiply));
    make_and_modify_binding(env,"quotient",make_primitive(quotient));
    make_and_modify_binding(env,">",make_primitive(superior));
    make_and_modify_binding(env,"<",make_primitive(inferior));
    make_and_modify_binding(env,"=",make_primitive(equal));

    /* type test */
    make_and_modify_binding(env,"boolean?",make_primitive(boolean_p));
    make_and_modify_binding(env,"symbol?",make_primitive(symbol_p));
    make_and_modify_binding(env,"integer?",make_primitive(integer_p));
    make_and_modify_binding(env,"char?",make_primitive(integer_p));
    make_and_modify_binding(env,"string?",make_primitive(string_p));
    make_and_modify_binding(env,"pair?",make_primitive(pair_p));
    make_and_modify_binding(env,"null?",make_primitive(null_p));


    /* convertion de type */
    make_and_modify_binding(env,"char->integer",make_primitive(chtoint));
    make_and_modify_binding(env,"integer->char",make_primitive(inttoch));
    make_and_modify_binding(env,"number->string",make_primitive(numbtostr));
    make_and_modify_binding(env,"string->number",make_primitive(strtonumb));
    make_and_modify_binding(env,"symbol->string",make_primitive(symtostr));
    make_and_modify_binding(env,"string->symbol",make_primitive(strtosym));

    /* manipulation de listes */
    make_and_modify_binding(env,"car",make_primitive(car_p));
    make_and_modify_binding(env,"cdr",make_primitive(cdr_p));
    make_and_modify_binding(env,"list",make_primitive(list_p));
    make_and_modify_binding(env,"cons",make_primitive(cons));
    make_and_modify_binding(env,"set-car!",make_primitive(set_car));
    make_and_modify_binding(env,"set-cdr!",make_primitive(set_cdr));

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

object multiply(object o) /* multiplie lles parametres */
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

object quotient(object o) /* divise successivement les parametres... si un seul retourne 1/parametre */
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
        WARNING_MSG("needs at least 1 parameters");
        return NULL;
    }
}


object superior(object o) /* teste si la liste est decroissante */
{
    if (number_of_pair(o)>=2)
    {   object obj_temp=o;
        int num_temp=0;
        object resultat=true;
        while (obj_temp !=nil && isnumber(car(obj_temp)))
        {   DEBUG_MSG("Entering while");
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
        WARNING_MSG("needs at least 2 parameters and only numbers");
        return NULL;
    }


}



object equal(object o) /* teste si les nombres de la liste sont egaux */
{
    if (number_of_pair(o)>=2)
    {   object obj_temp=o;
        int num_temp=0;
        object resultat=true;
        while (obj_temp !=nil && isnumber(car(obj_temp)))
        {
            num_temp=get_number(car(obj_temp));
            obj_temp=cdr(obj_temp);
            if (obj_temp!=nil)
            {
                if (num_temp!=get_number(car(obj_temp)))
                {
                    obj_temp=nil;
                    resultat=false;


                }
            }

        }
        return resultat;
    }
    else {
        WARNING_MSG("needs at least 2 parameters and only numbers");
        return NULL;
    }


}

object inferior(object o) /* teste si la liste est croissante */
{
    if (number_of_pair(o)>=2)
    {   object obj_temp=o;
        int num_temp=0;
        object resultat=true;
        while (obj_temp !=nil && isnumber(car(obj_temp)))
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
        WARNING_MSG("needs at least 2 parameters and only numbers");
        return NULL;
    }


}



/* object remainder(object o); */

object boolean_p(object o) /* teste si les elements de la liste sont des boolean*/
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
    else{WARNING_MSG("needs at least 1 parameter"); return NULL;}

}


object symbol_p(object o) /* teste si les elements de la liste sont des symboles */
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
    else{WARNING_MSG("needs at least 1 parameter"); return NULL;}

}


object integer_p(object o) /* teste si les elements de la liste sont des int */
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
    else{WARNING_MSG("needs at least 1 parameter"); return NULL;}

}


object char_p(object o) /* teste si les elements de la liste sont des caracteres */
{   printf("wesh gros");
    object resultat=true;
    object obj_temp=o;
    if (number_of_pair(o)>=1)
    {
    while (obj_temp!=nil)
    {   DEBUG_MSG("type is %s",whattype(obj_temp));
        if(!ischar(car(obj_temp)))
        {   DEBUG_MSG("this is not char");
            resultat=false;
            obj_temp=nil;
        }
        else {obj_temp=cdr(obj_temp);}
    }
    return resultat;
    }
    else{WARNING_MSG("needs at least 1 parameter"); return NULL;}

}


object string_p(object o) /* teste si les elements de la liste sont des string */
{
    object resultat=true;
    object obj_temp=o;
    if (number_of_pair(o)>=1)
    {
    while (obj_temp!=nil)
    {   DEBUG_MSG("type is %s",whattype(obj_temp));
        if(!isstring(car(obj_temp)))
        {
            resultat=false;
            obj_temp=nil;
        }
        else {obj_temp=cdr(obj_temp);}
    }
    return resultat;
    }
    else{WARNING_MSG("needs at least 1 parameter"); return NULL;}

}


object pair_p(object o) /* teste si les elements de la liste sont des paires */
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
    else{WARNING_MSG("needs at least 1 parameter"); return NULL;}

}

object null_p(object o) /* teste si les elements de la liste sont nil */
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


object cons(object o) /* cree une liste, sans nil a la fin, avec deux objets passe en parametre */
{
    if (number_of_pair(o)==2)
    {
        object result=NULL;
        result=make_pair(car(o),cadr(o));
        return result;

    }
    else {WARNING_MSG("needs exactly two parameters bitch"); return NULL;}

}


object car_p(object o)
{
    if (number_of_pair(o)==1)
    {
        return (caar(o));
    }
    else {WARNING_MSG("needs exactly one parameter"); return NULL;}

}

object cdr_p(object o)
{
    if (number_of_pair(o)==1)
    {
        return (cdar(o));
    }
    else {WARNING_MSG("needs exactly one parameter"); return NULL;}

}

object list_p(object o) /* cree une liste scheme, cad forme une S-expression avec les parametres */
{
    if(number_of_pair(o)==0)
    {
        return nil;
    }
    else
    {object liste=make_pair(car(o),nil);
    object obj_temp=cdr(o);
    object last_element_of_list=liste;
        while (!isnil(obj_temp))
        {
            modify_cdr(last_element_of_list,make_pair(car(obj_temp),nil));
            obj_temp=cdr(obj_temp);
            last_element_of_list=cdr(last_element_of_list);


        }
        return liste;
    }
}

object set_car(object o)
{
    if(number_of_pair(o)==2 && ispair(car(o)))
    {
        modify_car(car(o),cadr(o));
        return car(o);
    }
    else{WARNING_MSG("set-car! : Wrong number of argument (must be 2) or 1st argument is not a pair"); return NULL;}

}

object set_cdr(object o)
{
    if(number_of_pair(o)==2 && ispair(car(o)))
    {
        modify_cdr(car(o),cadr(o));
        return car(o);
    }
    else{WARNING_MSG("set-cdr! : Wrong number of argument (must be 2) or 1st argument is not a pair"); return NULL;}

}


object chtoint (object o){

	if(!ischar(car(o))){
		WARNING_MSG("char->integer need an integer as argument");
		return NULL;
		}
	if(cdr(o)!=nil){
		WARNING_MSG("too many arguments in char->integer");
		return NULL;
		}

	return make_integer((int)get_character(car(o)));

	}

object inttoch (object o){

	if(!ischar(car(o))){
		WARNING_MSG("integer->char need a character as argument");
		return NULL;
		}
	if(cdr(o)!=nil){
		WARNING_MSG("too many arguments in integer->char");
		return NULL;
		}

	return make_character((char)get_number(car(o)));

	}

object numbtostr (object o){

	return o;

	}

object strtonumb (object o){

	return o;

	}

object symtostr (object o){

	return o;

	}

object strtosym (object o){

return o;

}

