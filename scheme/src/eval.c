
/**
 * @file eval.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:11:30 2012
 * @brief Evaluation stuff for SFS.
 *
 * Evaluation stuff for SFS.
 */

#include "eval.h"

object sfs_eval( object input ) {
    DEBUG_MSG("Evaluation has started");
    /* cas quote */
    if (ispair(input))
{
    if (isquote(car(input)))
    {   DEBUG_MSG("quote recognized");

        return car(cdr(input));
    }
}
    else {WARNING_MSG("Attention t'a juste mis un atome pourri");}
    return input;
}
