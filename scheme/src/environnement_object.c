#include "object.h"
#include "mem.h"
#include "print.h"

/* fonction qui permet de créer un nouveau binding en tete d'environnement de nom name et de valeur nil */
object make_binding(char* name, object environment) {
    DEBUG_MSG("Making a new binding...");
    object binding = make_pair(nil,car(environment));
    modify_car(binding,make_pair(make_symbol(name),nil));
    modify_car(environment,binding);

    DEBUG_MSG("New binding created successfully : name of variable is %s.",name);
    return car(binding); /* la nouvelle paire du binding tq car(pair) = nom et cdr(pair)=valeur*/
}

object modify_binding(object binding, object value)
{   string string;
    modify_cdr(binding,value);
    DEBUG_MSG("Modifying value for %s ; type of existing value is %s and the new value is %s",get_symbol(car(binding),string),whattype(cdr(binding)),whattype(value));
    return cdr(binding); /* renvoie la valeur du binding*/
}

object make_and_modify_binding(object environment, char* name, object value) /* fonction qui cree directement un nouveau binding et assigne la valeur value et renvoie l'object symbole */
{
    object o = make_binding(name,environment);
    modify_binding(o,value);
    return car(o);
}

/* fonction qui cherche une variable dans 1'environnement et renvoie binding si trouve, sinon renvoie NULL */
object search_env(char* name, object env)
{   DEBUG_MSG("Searching %s in an environment",name);
	/*print_env(env); */
    object obj_temp=car(env);
    string string;
    if (obj_temp==nil)
    {
        DEBUG_MSG("Environment is empty you stupid. Returning NULL");
        return NULL;
    }
    while (ispair(obj_temp))
    {
        if(!strcmp(get_symbol(caar(obj_temp),string),name))
        {
            /* DEBUG_MSG("Tried to compare %s with %s and found they were the same",get_symbol(caar(obj_temp),string),name); */
            DEBUG_MSG("%s has been found !",name);
            return car(obj_temp);
        }
        else {
            /*DEBUG_MSG("Tried to compare %s with %s and found they were different",get_symbol(caar(obj_temp),string),name);*/
        }
        obj_temp=cdr(obj_temp); /* a la fin du while obj_temp vaudra nil et ne sera plus une paire */
    }
    DEBUG_MSG("Not found");

    return NULL ;
}

/* fonction qui cherche une variable dans 1'environnement et renvoie sa valeur si trouve, sinon renvoie NULL */
object search_val_env(char* name, object env) {
    DEBUG_MSG("Searching the value of %s in an environment",name);
    object o = search_env(name,env);
    if(o == NULL)
        return NULL;
    else return cdr(o);

}


/* fonction qui cherche une variable dans ts les environnements en dessous et renvoie binding si trouve, sinon renvoie NULL */
object search_under(char* name,object env) {
    DEBUG_MSG("Searching %s in the environments under",name);
    object env_temp = env;
    object o;
    while (env_temp!=nil)
    {
	o = search_env(name,env_temp);
        if (o != NULL)
        {
            return o;
        }
        env_temp=cdr(env_temp);
    }
    return NULL;

}

/* fonction qui cherche une variable dans ts les environnement en dessous et renvoie sa valeur si trouve, sinon renvoie NULL */
object search_val_under(char* name,object env) {
    DEBUG_MSG("Searching the value of %s in the environments under",name);
    object o = search_under(name,env);
    if(o == NULL)
        return NULL;
    else return cdr(o);

}
