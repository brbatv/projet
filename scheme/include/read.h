
/**
 * @file read.h
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 18:30:11 2012
 * @brief Read routine for SFS.
 *
 * Read routine for SFS.
 */

#ifndef _READ_H_
#define _READ_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#include "object.h"

enum {S_OK, S_KO, S_END};

uint   sfs_get_sexpr( string input, FILE *fp );

object sfs_read( char *input, uint *here );
object sfs_read_atom( char *input, uint *here );
object sfs_read_pair( char *stream, uint *i );



#ifdef __cplusplus
}
#endif

#endif /* _READ_H_ */

#define INIT 0x00
#define INT_IN_PROG 0x01
#define INT 0x02
#define HASH_DETECTED 0x03
#define BOOL_IN_PROG 0x04
#define BOOL 0x05
#define CHAR_IN_PROG 0x06
#define CHAR 0x07

