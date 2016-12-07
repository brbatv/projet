
/**
 * @file eval.h
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:10:38 2012
 * @brief Evaluation stuff for SFS.
 *
 * Evaluation stuff for SFS.
 */

#ifndef _EVAL_H_
#define _EVAL_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "object.h"

object define_eval(object input,object env);
object if_eval(object input,object env);
object and_eval(object input,object env);
object or_eval(object input,object env);
object begin_eval(object input,object env);
object lambda_eval(object input,object env);
object let_eval(object input,object env);
object sfs_eval(object input,object env);
object arguments_eval (object input,object env);

#ifdef __cplusplus
}
#endif

#endif /* _EVAL_H_ */
