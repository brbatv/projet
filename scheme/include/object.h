
/**
 * @file object.h
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 17:49:46 2012
 * @brief Object definition for SFS.
 *
 * Object definition for SFS.
 */

#ifndef _OBJECT_H_
#define _OBJECT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "number.h"


typedef struct object_t {

    uint type;

    union {

        num              number;
        char             character;
        string           string;
        string           symbol;

        struct pair_t {
            struct object_t *car;
            struct object_t *cdr;
        }                pair;

        struct object_t *special;

    } this;

} *object;


object make_object(uint);
object make_nil(void);
object make_integer(int);
object make_boolean(uint);
object make_character(char);
object make_pair(object,object);
object make_string(char*);
object make_symbol(char*);
int ispair(object);
int isatom (object);
object car(object);
object cdr(object);
object caar(object);
object cadr(object);
object cddr(object);
object cdar(object);
/*gestion des formes*/
int isquote(object);
int isdefine(object);
int isset(object);
int isif(object);
int isand(object);
int isor(object);
object make_env(object);
object make_binding(char*,object);
object search_env(char*,object);
object search_under(char*,object);
char* get_symbol (object symbol,char*);
char* whattype(object o);


#define SFS_NUMBER       0x00
#define SFS_CHARACTER    0x01
#define SFS_STRING       0x02
#define SFS_PAIR         0x03
#define SFS_NIL          0x04
#define SFS_BOOLEAN      0x05
#define SFS_SYMBOL       0x06


extern object nil;
extern object false;
extern object true;
extern object top_level;

#ifdef __cplusplus
}
#endif

#endif /* _OBJECT_H_ */
