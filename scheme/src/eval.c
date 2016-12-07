
/**
 * @file eval.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:11:30 2012
 * @brief Evaluation stuff for SFS.
 *
 * Evaluation stuff for SFS.
 */

#include "eval.h"
#include "print.h"
#include "object.h"

object define_eval(object input,object env) /* input = parametres! */ {

    string  name_of_new_variable;
    string  str;
    object  o = sfs_eval(cadr(input),env);
    if (number_of_pair(input)!=2)
    {
        WARNING_MSG("Wrong number of parameters for define : expected : 2");
        return NULL;
    }
    if (issymbol(car(input)))
    {
    strcpy(name_of_new_variable,get_symbol(car(input),str));
    DEBUG_MSG("%s",name_of_new_variable);

    if(o == NULL) {
        return NULL;
    }
    else {

        return make_and_modify_binding(env,name_of_new_variable,o);
            }
    }


    if (ispair(car(input)))
    {
        if (issymbol(caar(input)))
            return NULL;

    }
    else return NULL;

}

/* if (!issymbol(car(input)))
    {   WARNING_MSG("Define needs a symbol as first parameter");
        return NULL;
    } */
/**/
object if_eval(object input,object env) {

    object predicate = car(input);
    object consequence = cadr(input);
    object alternative = caddr(input);

    if(isnil(predicate) || isnil(consequence)) {
        WARNING_MSG("if needs two parameters");
        return NULL;
    }
    if(istrue(sfs_eval(predicate,env))) {
        ;
        return sfs_eval(consequence,env);
    }
    else {
        if(isnil(predicate)) {
            ;
            return false;
        }
        else {
            ;
            return sfs_eval(alternative,env);
        }
    }

}

object set_eval(object input,object env)
{

    string  name_of_first_parameter;
    string  str;
    object  second_parameter = sfs_eval(cadr(input),env);
    if (!ispair(cdr(input))) /*expression du type (set!  ) */
    {   WARNING_MSG("set! needs two parameters");
        return NULL;
    }
    if (!ispair(cdr(input))) /* expression du type (set! x) */
    {   WARNING_MSG("set! needs two parameters and not only one ");
        return NULL;
    }
    if (ispair(cddr(input))) /* note : si un cdr est !ispair <=> isnil si arbre syntaxique bien construit */
    {   WARNING_MSG("set! needs no more than two parameters");
        return NULL;
    }
    if (!issymbol(car(input)))
    {   WARNING_MSG("set! needs a symbol as first parameter");
        return NULL;
    }
    strcpy(name_of_first_parameter,get_symbol(car(input),str));
    object o=search_env(name_of_first_parameter,env);
    if (isnil(o))
    {   WARNING_MSG("set! needs a symbol already defined, %s is not defined",name_of_first_parameter);
        return NULL;
    }
    else {
        if(second_parameter== NULL) {
            return NULL;
        }
        else {

            modify_binding(o,second_parameter);

            return car(o);
        }

    }
}

/* fonction qui evalue la forme and */
object and_eval(object o,object env) {

    int i = TRUE;
    while (i && !isnil(o)) {
        i = istrue(sfs_eval(car(o),env));
        o = cdr(o);
    }
    if(i) return true;
    else return false;

}

/* fonction qui evalue la forme or */
object or_eval(object o,object env) {

    int i = FALSE;
    while (!i && !isnil(o)) {
        i = istrue(sfs_eval(car(o),env));
        o = cdr(o);
    }
    if(i) return true;
    else return false;

}

/* fonction qui evalue la forme begin */
object begin_eval(object input, object env){
object o=arguments_eval(input,env);
int i;
int  n=number_of_pair(o);
for (i=1; i<=n-1;i++)
{
o=cdr(o);
}
return  car(o);
}

/* fonction qui effectue et renvoie l'evaluation de input au sens du scheme*/
object sfs_eval( object input, object env) {

    string str;
    object val;
    if(input == NULL) {
        return NULL;
    }

    DEBUG_MSG("Evaluation has started");
    if (isatom(input)) {
        if(issymbol(input)) {
            if(isform(input)) {
                WARNING_MSG("A form has to be in a pair");
                return NULL;
            }
            get_symbol(input,str);
            val = search_val_env(str,env);
            if(val!=NULL) return val; /* le symbole est bien defini dans l'environnement courant */
            else {
                WARNING_MSG("Unknown symbol %s",str);
                return NULL;
            }

        }
	DEBUG_MSG("Evaluating an auto-evaluating object");
        return input;
	}

    if (ispair(input)) {


        object 	symb = car(input);
        object 	parametres = cdr(input);
        object	val = NULL;
        char 	name[256];



        if (!issymbol(symb)) {
            WARNING_MSG("A pair has to begin with a symbol");
            return NULL;
        }
        else {

            val = search_val_under(get_symbol(symb,name),env);

            /* cas des primitives */
            if(isprimitive(val)) {
                object arg_eval=arguments_eval(parametres,env);
                if(arg_eval==NULL)
                {
                    return NULL;
                }

                DEBUG_MSG("primitive recognized");
                return (*val->this.primitive)(arg_eval);

            }

            /* cas quote */
            if (isquote(symb))
            {   DEBUG_MSG("quote recognized");
                if(isnil(parametres)) {

                    WARNING_MSG("Quote needs at least one parameter");
                    return NULL;
                }
                return car(parametres);
            }

            /* cas define */
            if(isdefine(symb))
            {   DEBUG_MSG("define recognized");
                return define_eval(parametres,env);
            }

            /* cas if */
            if (isif(symb))
            {   DEBUG_MSG("if recognized");
                return if_eval(parametres,env);
            }

            /* cas and */
            if (isand(symb))
            {   DEBUG_MSG("and recognized");
                return and_eval(parametres,env);
            }

            /* cas or */
            if (isor(symb))
            {   DEBUG_MSG("or recognized");
                return or_eval(parametres,env);
            }

            /* cas set! */
            if (isset(symb))
            {   DEBUG_MSG("set! recognized");

                return set_eval(parametres,env);
            }
	    /* cas begin */
            if (isbegin(symb))
            { DEBUG_MSG("begin recognized");

            return begin_eval(parametres,env);

            }


            else {
                DEBUG_MSG("Aucune forme détectée... pour l'instant. Input est de type %s",whattype(input));
                WARNING_MSG("undefined symbol %s",get_symbol(symb,name));
	    return NULL;
            }
        }
    }


    return NULL;
}


/* fonction qui evalue tous les arguments d'une primitives */
object arguments_eval ( object input ,object env) {

	object p = input;
	DEBUG_MSG("evaluation arguments of a primitive");
	while (!isnil(p)){
		modify_car(p,sfs_eval(car(p),env));
		if (car(p)==NULL)
        {
            return NULL; /* pour gerer si un symbole est inconnu par exemple */
        }
		p = cdr(p);
		}
	return input;

}
