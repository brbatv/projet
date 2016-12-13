
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

object define_eval(object input,object env) { /* input = parametres! */

    
    string  name_of_new_variable;
    string  str;
    object  o;

    if (number_of_pair(input)!=2)
    {
        WARNING_MSG("Wrong number of parameters for define : expected : 2");
        return NULL;
    }
    if (issymbol(car(input)))
    {
        strcpy(name_of_new_variable,get_symbol(car(input),str));
        DEBUG_MSG("%s",name_of_new_variable);
	o = sfs_eval(cadr(input),env);
	
        if(o == NULL) {
            return NULL;
        }
        else {

            make_and_modify_binding(env,name_of_new_variable,o);
	    return make_no_type();
        }
    }


    if (ispair(car(input)))
    {   DEBUG_MSG("Cas d'un compound defini directement dans define");
        if (issymbol(caar(input)))
        {
            strcpy(name_of_new_variable,get_symbol(caar(input),str));
        }
        else {
            WARNING_MSG("Wrong parameters");
            return NULL;
        }
        object parametres = cdar(input);
        object lambda = make_pair(parametres,cdr(input));
        o = lambda_eval (lambda,env);
        make_and_modify_binding(env,name_of_new_variable,o);
	return make_no_type();	
    }
    else return NULL;

}

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
    object o = search_under(name_of_first_parameter,env);
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

            return make_no_type();
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
object begin_eval(object input, object env) {
    object o = arguments_eval_primitives(input,env);
    int i;
    int  n=number_of_pair(o);
    for (i=1; i<=n-1; i++)
    {
        o=cdr(o);
    }
    return  car(o);
}

/* fonction qui evalue la forme lambda */
object lambda_eval(object input, object env) {

    int n = number_of_pair(input);
    if (n < 2) {
        WARNING_MSG("lambda needs at least 2 arguments");
        return NULL;
    }
    if (!ispair(car(input))) {
        WARNING_MSG("problem in lambda's arguments");
        return NULL;
    }
    else {
        object o = car(input);
        while (!isnil(o)) {
            if(!issymbol(car(o))) {
                WARNING_MSG("lambda's parameters must be symbols");
                return NULL;
            }
            o = cdr(o);
        }

        return make_compound(car(input),cdr(input),env);
    }
}

/* fonction qui evalue la forme let */
object let_eval(object input, object env) {

    return input;

}

/* fonction qui effectue et renvoie l'evaluation de input au sens du scheme */
object sfs_eval( object input, object env) {

    string str;
    object val;
    if(input == NULL) {
        return NULL;
    }

    DEBUG_MSG("Evaluation has started");
    if (isatom(input)) {
        if(issymbol(input)) {
	    DEBUG_MSG("Evaluating an atom symbol");
            if(isform(input)) {
                WARNING_MSG("A form has to be in a pair");
                return NULL;
            }
            get_symbol(input,str);
	    DEBUG_MSG("Searching the val of the atom symbol");
            val = search_val_under(str,env);
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
        {   DEBUG_MSG("begin recognized");

            return begin_eval(parametres,env);

        }
        /* cas lambda */
        if (islambda(symb))
        {   DEBUG_MSG("lambda recognized");

            return lambda_eval(parametres,env);

        }

        /* cas let */
        if (islet(symb))
        {   DEBUG_MSG("let recognized");

            return let_eval(parametres,env);

        }

        val = sfs_eval(symb,env);
	if (val == NULL){
		DEBUG_MSG("transmission d'erreur, cas sfs_eval avant primitive/compound");
		return NULL;
		}
	
        /* cas des primitives */
        if(isprimitive(val)) {
            DEBUG_MSG("primitive recognized");
            object arg_eval=arguments_eval_primitives(parametres,env);
            if(arg_eval==NULL)
            {
                return NULL;
            }
            return (*val->this.primitive)(arg_eval);
        }

        /* cas des agregats */
        if(iscompound(val)) {
            DEBUG_MSG("compound recognized");
            object local_env = make_env(val->this.compound.envt);
            return compound_eval(val,parametres,local_env);

        }
    }

    return NULL;
}


/* fonction qui evalue tous les arguments d'une primitives */
object arguments_eval_primitives ( object input ,object env) {

    object p = input;
    DEBUG_MSG("evaluating arguments of a primitive");
    while (!isnil(p)) {
        modify_car(p,sfs_eval(car(p),env));
        if (car(p) == NULL)
        {
            return NULL; /* pour gerer si un symbole est inconnu par exemple */
        }
        p = cdr(p);
    }
    return input;

}

/* fonction qui evalue tous les arguments d'un begin en prenant soin d'effectuer l'evalutation dans un autre arbre dupplique */
object arguments_eval_begin ( object input ,object env) {

    
    DEBUG_MSG("evaluating arguments for a begin or a compound");
    int n = number_of_pair(input);
	int i;
	object new_input;
	object p , p_new;
	
	/* recreation d'un arbre d'instructions */
	for(i = 0 ; i<n ; i++ ){
		new_input = make_pair(nil,new_input);
	}
	while(!isnil(p) && !isnil(p_new)){
		modify_car(p_new,car(p));
		p_new = cdr(p_new);
		p = cdr(p);
	}
    return arguments_eval_primitives(new_input,env);
}


/* fonction qui evalue un appel a l'agregat comp pour les valeurs de parametres par dans l'environnement env */
object compound_eval(object comp , object par_val , object env){
	DEBUG_MSG("evaluation d'un agregat");
	string str;
	string str2;	
	object par = comp->this.compound.parms;
	while(!isnil(par) && !isnil(par_val)){
		strcpy(str,get_symbol(car(par),str2));
		make_and_modify_binding(env,str,car(par_val));
		par = cdr(par);
		par_val = cdr(par_val);
	}
	return begin_eval(comp->this.compound.body,env);

}
