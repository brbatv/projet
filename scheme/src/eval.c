
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

object define_eval(object input) {

    string  name_of_new_variable;
    string  str;
    object  o = sfs_eval(caddr(input));
    if (!ispair(cdr(input))) /*expression du type (define  ) */
    {   WARNING_MSG("Define needs two parameters");
        return NULL;
    }
    if (!ispair(cddr(input))) /* expression du type (define x) */
    {   WARNING_MSG("Define needs two parameters and not only one ");
        return NULL;
    }
    if (ispair(cdddr(input))) /* note : si un cdr est !ispair <=> isnil si arbre syntaxique bien construit */
    {   WARNING_MSG("Define needs no more than two parameters");
        return NULL;
    }
    if (!issymbol(car(cdr(input))))
    {   WARNING_MSG("Define needs a symbol as first parameter");
        return NULL;
    }
    strcpy(name_of_new_variable,get_symbol(cadr(input),str));
    DEBUG_MSG("%s",name_of_new_variable);

    if(o == NULL) {
        return NULL;
    }
    else {

        return make_and_modify_binding(current_env,name_of_new_variable,o);
    }
}


/**/
object if_eval(object input) {

    object predicate = cadr(input);
    object consequence = caddr(input);
    object alternative = cadddr(input);

    if(isnil(predicate) || isnil(consequence)) {
        WARNING_MSG("Define needs two parameters");
        return NULL;
    }
    if(istrue(sfs_eval(predicate))) {
        ;
        return sfs_eval(consequence);
    }
    else {
        if(isnil(predicate)) {
            ;
            return false;
        }
        else {
            ;
            return sfs_eval(alternative);
        }
    }

}

object set_eval(object input)
{

    string  name_of_first_parameter;
    string  str;
    object  second_parameter = sfs_eval(caddr(input));
    if (!ispair(cdr(input))) /*expression du type (set!  ) */
    {   WARNING_MSG("set! needs two parameters");
        return NULL;
    }
    if (!ispair(cddr(input))) /* expression du type (set! x) */
    {   WARNING_MSG("set! needs two parameters and not only one ");
        return NULL;
    }
    if (ispair(cdddr(input))) /* note : si un cdr est !ispair <=> isnil si arbre syntaxique bien construit */
    {   WARNING_MSG("set! needs no more than two parameters");
        return NULL;
    }
    if (!issymbol(car(cdr(input))))
    {   WARNING_MSG("set! needs a symbol as first parameter");
        return NULL;
    }
    strcpy(name_of_first_parameter,get_symbol(cadr(input),str));
    object o=search_env(name_of_first_parameter,current_envwebmail phelma);
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

object and_eval(object input) {

    object o = cdr(input);
    int i = TRUE;
    while (istrue(o) && !isnil(o)) {
        i = i && istrue(car(o));
        o = cdr(o);
    }
    if(i) return true;
    else return false;

}

object or_eval(object input) {

    object o = cdr(input);
    int i = FALSE;
    while (!istrue(o) && !isnil(o)) {
        i = i || istrue(car(o));
        o = cdr(o);
    }
    if(i) return true;
    else return false;

}

/*fonction qui effectue et renvoie l'evaluation de input au sens du scheme*/
object sfs_eval( object input ) {

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
            val = search_val_env(str,current_env);
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

            val = search_val_under(get_symbol(symb,name),current_env);

            /* cas des primitives */
            if(isprimitive(val)) {
                object arg_eval=arguments_eval(parametres);
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
                return define_eval(input);
            }

            /* cas if */
            if (isif(symb))
            {   DEBUG_MSG("if recognized");
                return if_eval(input);
            }

            /* cas and */
            if (isand(symb))
            {   DEBUG_MSG("and recognized");
                return and_eval(input);
            }

            /* cas or */
            if (isor(symb))
            {   DEBUG_MSG("or recognized");
                return or_eval(input);
            }

            /* cas set! */
            if (isset(symb))
            {   DEBUG_MSG("set! recognized");

                return set_eval(input);
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
object arguments_eval ( object input ) {

	object p = input;
	DEBUG_MSG("evaluation arguments of a primitive");
	while (!isnil(p)){
		modify_car(p,sfs_eval(car(p)));
		if (car(p)==NULL)
        {
            return NULL; /* pour gerer si un symbole est inconnu par exemple */
        }
		p = cdr(p);
		}
	return input;

}
