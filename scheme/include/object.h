
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
		int isroot; /*permet de savoir si il s'agit de la racine l'arbre ou non*/
        }                pair;

        struct object_t *special;

    } this;

} *object;


object make_object(uint);
object make_nil(void);
object make_integer(int);
object make_boolean(uint);
object make_character(char);
object make_pair(object,object,int);
object make_scharacter(char*);
object make_string(char*);
object make_symbol(char*);
int ispair(object);
int isatom (object);
int isroot(object);
object car(object);
object cdr(object);

#define SFS_NUMBER       0x00
#define SFS_CHARACTER    0x01
#define SFS_STRING       0x02
#define SFS_PAIR         0x03
#define SFS_NIL          0x04
#define SFS_BOOLEAN      0x05
#define SFS_SYMBOL       0x06
#define SFS_SCHARACTER   0x07


extern object nil;
extern object false;
extern object true; 

#ifdef __cplusplus
}
#endif

#endif /* _OBJECT_H_ */
