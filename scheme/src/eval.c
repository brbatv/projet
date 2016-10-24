
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

object define_eval(object input){
	
    	string name_of_new_variable;
        string str;
	if (!ispair(cdr(input))) /*expression du type (define  ) */
            {WARNING_MSG("Define needs two parameters");
            return NULL;}
        if (!ispair(cddr(input))) /* expression du type (define x) */
            {WARNING_MSG("Define needs two parameters and not only one ");
            return NULL;}
        if (ispair(cdr(cddr(input)))) /* note : si un cdr est !ispair <=> isnil si arbre syntaxique bien construit */
            {WARNING_MSG("Define needs no more than two parameters");
             return NULL;}
        if (!issymbol(car(cdr(input))))
            {WARNING_MSG("Define needs a symbol as first parameter");
             return NULL;}
        strcpy(name_of_new_variable,get_symbol(cadr(input),str));
        DEBUG_MSG("%s",name_of_new_variable);
        if (isatom(sfs_eval(car(cddr(input))))) /* si le 2eme parametre s'evalue en tant qu'atome*/
            {DEBUG_MSG("je passe par la 1");
            if (search_under(name_of_new_variable,current_env)==nil) /* si la nouvelle variable n'existe pas encore */
            {DEBUG_MSG("je passe par la 2");
                if (issymbol(sfs_eval(car(cddr(input)))) && search_under(get_symbol(sfs_eval(car(cddr(input))),str),current_env)!=nil)/* si le 2eme parametre est un symbole connu */
                {DEBUG_MSG("je passe par la 3");
                    DEBUG_MSG("%s has been found in environment. Assigning its value to %s ..",get_symbol(car(cddr(input)),str),name_of_new_variable);
                    char* symbol_second_parameter=get_symbol(car(cddr(input)),str);
                    make_and_modify_binding(current_env,name_of_new_variable,cdr(search_under(symbol_second_parameter,current_env)));
                    DEBUG_MSG("...done");
                    DEBUG_MSG("%s",name_of_new_variable);
                    print_env(current_env);
                    return NULL;
                }

                else if (issymbol(sfs_eval(car(cddr(input))))) /* si le 2eme parametre est un symbole inconnu*/
                {WARNING_MSG("Define can use a symbol as second parameter only if it already exists!");
                return NULL;}

                else /* 2eme parametre est un atome qui n'est pas un symbole*/
                {DEBUG_MSG("Assigning type %s to new variable %s",whattype(sfs_eval(car(cddr(input)))),name_of_new_variable);
                make_and_modify_binding(current_env,name_of_new_variable,car(cddr(input)));
                DEBUG_MSG("Done.");
                print_env(current_env);		
		DEBUG_MSG("je passe par la 10");
                return NULL;

                }

            }
            else /* si la nouvelle variable existe déjà => sujet : on ne modifie pas, repl.it : on remplace sa valeur (ou alors on la cree dans un nouvel environnement ??)*/
            {
                DEBUG_MSG("%s already exists in environment. NOT Replacing its value with %s",name_of_new_variable,whattype(sfs_eval(car(cddr(input)))));
                print_env(current_env);
                return NULL;

            }
            }
        else {WARNING_MSG("Define needs an atom as second parameter"); return NULL;}
}	
	
object if_eval(object input){

	object predicate = cadr(input);
	object consequence = caddr(input);
	object alternative = cadddr(input);
	
	if(isnil(predicate) || isnil(consequence)){
		WARNING_MSG("Define needs two parameters");
        	return NULL;
		}
	if(istrue(sfs_eval(predicate))){
		DEBUG_MSG("JE PASSE PAR LA 1");
		return sfs_eval(consequence);
		}
	else{
		if(isnil(predicate)){
			DEBUG_MSG("JE PASSE PAR LA 2");
			return false;
			}
		else{
			DEBUG_MSG("JE PASSE PAR LA 3");
			return sfs_eval(alternative);
		}
	}
			
}

object sfs_eval( object input ) {

    DEBUG_MSG("Evaluation has started");
    if (isatom(input)){
	if(issymbol(input)){
		return NULL;
		}
	else{
		if(istrue(input)){
			return input;
			}
		else return false;
		}
	}
    if (ispair(input)){
	if (!issymbol(car(input))){
		WARNING_MSG("A pair has to begin with a symbol");
            return NULL;
		}
	else {
		
    /* cas quote */
    if (isquote(car(input)))
    {   DEBUG_MSG("quote recognized");

        return car(cdr(input));
    }

   /* cas define */
    if(isdefine(car(input)))
    { DEBUG_MSG("define recognized");
	return define_eval(input);}

    /* cas if */
    if (isif(car(input)))
    {   DEBUG_MSG("if recognized");
        return if_eval(input);
    }
}
}

    else {DEBUG_MSG("Aucune forme détectée... pour l'instant. Input est de type %s ",whattype(input));}
    return input;
}
