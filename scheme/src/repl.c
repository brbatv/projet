/**
 * @file repl.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 18:13:02 2012
 * @brief Main REPL for SFS.
 *
 * Main REPL for SFS.
 */



#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "object.h"
#include "read.h"
#include "eval.h"
#include "print.h"
#include "primitive.h"

/* mode d'interaction avec l'interpreteur (exemple)*/
typedef enum {INTERACTIF,SCRIPT} inter_mode;


void usage_error( char *command ) {

    fprintf( stderr, "Usage: %s [file.scm]\n   If no file is given, executes in Shell mode.\n", command );
}


object nil=NULL;
object false = NULL;
object true = NULL;
object quote = NULL;

object init_interpreter ( void ) {
    nil = make_nil();
    false = make_boolean(FALSE);
    true = make_boolean(TRUE);
    object top_level = make_env(nil);


    /* primitives initialization */
    init_primitive ( top_level );

    /* forms initializaton */
    make_binding("quote",top_level);
    make_binding("define",top_level);
    make_binding("set!",top_level);
    make_binding("if",top_level);
    make_binding("and",top_level);
    make_binding("or",top_level);
    make_binding("let",top_level);
    make_binding("begin",top_level);
    make_binding("lambda",top_level);

	/* initialisation de map */
	uint here = 0;
	sfs_eval(sfs_read("(define (map  proc items) (if (null? items) '() (cons (proc (car  items)) (map  proc (cdr  items)))))",&here),top_level);

	return top_level;

}

int main ( int argc, char *argv[] ) {

    char     input[BIGSTRING];
    uint     here = 0;
    object   output = NULL;
    object   sexpr = NULL;
    inter_mode mode;
    FILE *   fp = NULL; /* le flux dans lequel les commande seront lues : stdin (mode shell) ou un fichier */

    /* exemples d'utilisation des macros du fichier notify.h */
    /* WARNING_MSG : sera toujours affiche */
    WARNING_MSG("Un message WARNING_MSG ! Bienvenue dans scheme");

    /* macro INFO_MSG : uniquement si compil avec -DVERBOSE. Cf Makefile*/
    INFO_MSG("Un message INFO_MSG : Debut du programme %s", argv[0]);

    /* macro DEBUG_MSG : uniquement si compil avec -DDEBUG (ie : compil avec make debug). Cf Makefile */
    DEBUG_MSG("Un message DEBUG_MSG ! C'est parti");

    /* La ligne suivante provoquerait l'affichage du message
       puis la sortie du programme avec un code erreur non nul (EXIT_FAILURE) */
    /* ERROR_MSG("Erreur. Arret du programme"); */

    if ( argc > 2 ) {
        usage_error( argv[0] );
        exit( EXIT_FAILURE );
    }
    if(argc == 2 && strcmp(argv[1], "-h") == 0) {
        usage_error( argv[0] );
        exit( EXIT_SUCCESS );
    }
	

    object current_env = init_interpreter();

    /*par defaut : mode shell interactif */
    fp = stdin;
    mode = INTERACTIF;
    if(argc == 2) {
        /* mode fichier de commandes */
        fp = fopen( argv[1], "r" );
        if ( fp == NULL ) {
            perror( "fopen" );
            exit( EXIT_FAILURE );
        }
        mode = SCRIPT;
    }


    while ( 1 ) {
        input[0]='\0';
        here = 0;
        output = NULL;
        sexpr = NULL;
        uint Sexpr_err;

        Sexpr_err = sfs_get_sexpr( input, fp );

        if ( S_OK != Sexpr_err) {
            /* si fichier alors on sort*/
            if (mode == SCRIPT) {
                fclose( fp );
                if (Sexpr_err==S_END) {
                    /* Cas fin de fichier script */
                    exit(EXIT_SUCCESS);
                }
                /* Cas S-Expression mal formee dans le fichier script */
                ERROR_MSG("Malformed S-expression --- Aborts");
            }
            /*sinon on rend la main a l'utilisateur*/
            continue;
        }

        if ( 0 == strlen( input ) ) {
            continue;
        }

        here  = 0;
        sexpr = sfs_read( input, &here );
        if ( NULL == sexpr ) {
            /* si fichier alors on sort*/
            if (mode == SCRIPT) {
                fclose( fp );
                /*macro ERROR_MSG : message d'erreur puis fin de programme ! */
                ERROR_MSG("Invalid S-expression --- Aborts");
            }
            /*sinon on rend la main a l'utilisateur*/
            continue ;
        }

        output = sfs_eval( sexpr , current_env );
        if( NULL == output) {
            /* si fichier alors on sort*/
            if (mode == SCRIPT) {
                fclose( fp );
                /*macro ERROR_MSG : message d'erreur puis fin de programme ! */
                ERROR_MSG("Error while evaluating input --- Aborts");
            }
            /*sinon on rend la main a l'utilisateur*/
            continue ;
        }

	if(output->type != SFS_NO_TYPE){
        printf( "==> " );
        sfs_print( output );
        printf( "\n" );
	}
    }

    if (mode == SCRIPT) {
        fclose( fp );
    }
    exit( EXIT_SUCCESS );
}
