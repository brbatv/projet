
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

	struct object_t *(*primitive)(struct object_t *);
        struct object_t *special;

    struct{ struct object_t *parms;
                struct object_t *body;
                struct object_t *envt;} compound;

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
object make_primitive(object(*)(object));
object make_compound(object parameters, object body, object environnement);
int ispair(object);
int isatom (object);
int issymbol(object);
int isnil(object);
int isnumber(object );
int isstring(object);
int ischar(object);
int isboolean(object);
int isprimitive(object);
object car(object);
object cdr(object);
object caar(object);
object cadr(object);
object cddr(object);
object cdar(object);
object cdddr(object);
object caddr(object);
object cadddr(object);
/*gestion des formes*/
int isquote(object);
int isdefine(object);
int isset(object);
int isif(object);
int isand(object);
int isor(object);
int isform(object);
int isbegin(object);
int islambda(object);
int islet(object);
/*fin de gestion des formes*/
int isprimitive(object);
int iscompound(object);
int istrue(object);
/* gestion des environnements */
object make_env(object);
object make_binding(char*,object);
object modify_binding(object, object);
object make_and_modify_binding(object environment, char* name, object value);
object search_env(char*,object);
object search_val_env(char*, object);
object search_under(char*,object);
object search_val_under(char*, object);
/* fin de gestion des environnements */
char* get_symbol (object symbol,char*);
char get_character(object);
char* get_string (object string,char* str);
char* whattype(object o);
int get_number(object o);
int number_of_pair(object o);
object modify_car(object o, object car);
object modify_cdr(object o, object cdr);

#define SFS_NUMBER       0x00
#define SFS_CHARACTER    0x01
#define SFS_STRING       0x02
#define SFS_PAIR         0x03
#define SFS_NIL          0x04
#define SFS_BOOLEAN      0x05
#define SFS_SYMBOL       0x06
#define SFS_PRIMITIVE    0x07
#define SFS_COMPOUND 0x08


extern object nil;
extern object false;
extern object true;
extern object top_level;
extern object current_env;

#ifdef __cplusplus
}
#endif

#endif /* _OBJECT_H_ */
