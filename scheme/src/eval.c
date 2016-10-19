
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

object sfs_eval( object input ) {
    DEBUG_MSG("Evaluation has started");
    string string;
    char* name_of_new_variable;
    name_of_new_variable=get_symbol(cadr(input),string);
    if (ispair(input))
{    /* cas quote */
    if (isquote(car(input)))
    {   DEBUG_MSG("quote recognized");

        return car(cdr(input));
    }

   /* cas define*/
    if (isdefine(car(input)))
    { DEBUG_MSG("define recognized");
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

        if (isatom(sfs_eval(car(cddr(input))))) /* si le 2eme parametre s'evalue en tant qu'atome*/
            {
            if (search_under(name_of_new_variable,current_env)==nil) /* si la nouvelle variable n'existe pas encore */
            {
                if (issymbol(sfs_eval(car(cddr(input)))) && search_under(get_symbol(car(cddr(input)),string),current_env)!=nil)/* si le 2eme parametre est un symbole connu */
                {
                    DEBUG_MSG("%s has been found in environment. Assigning its value to %s",get_symbol(car(cddr(input)),string),name_of_new_variable);

                    make_and_modify_binding(current_env,name_of_new_variable,search_under(get_symbol(car(cddr(input)),string),current_env));
                    DEBUG_MSG("Done.");
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
                return NULL;

                }

            }
            else /* si la nouvelle variable existe déjà => sujet : on ne modifie pas, repl.it : on remplace sa valeur (ou alors on la cree dans un nouvel environnement ??)*/
            {
                DEBUG_MSG("%s already exists in environment. NOT Replacing its value with %s",name_of_new_variable,whattype(sfs_eval(car(cddr(input)))));

            }




            }
        else {WARNING_MSG("Define needs an atom as second parameter"); return NULL;}

    }
}
    else {WARNING_MSG("Attention t'a juste mis un atome pourri");}
    return input;
}
