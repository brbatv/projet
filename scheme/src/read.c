
/**
 * @file read.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 18:31:05 2012
 * @brief Read routine for SFS.
 *
 * Read routine for SFS.
 */

#include <stdio.h>
#include <ctype.h>
#include "read.h"



void flip( uint *i ) {

    if ( *i == FALSE ) {
        *i = TRUE;
    }
    else {
        *i = FALSE;
    }
}

/*
 * @fn char* first_usefull_char(char* line)
 *
 * @brief retourne un pointeur sur le premier caractere utile dans line
 * ou NULL si line ne contient que des espaces et des commentaires
 */
char* first_usefull_char(char* line) {

    int i=0;
    if (line == NULL) {
        return NULL;
    }
    i = 0;
    /* on saute les espaces */
    while(line[i] != '\0' && isspace(line[i])) {
        i++;
    }
    /* si fin de ligne => ligne inutile */
    if(line[i] == '\0') {
        return NULL;
    }
    /* si premier caractere non espace est ';' => ligne inutile */
    if(line[i] == ';') {
        return NULL;
    }
    return line + i; /* ligne utile */
}

/**
 * @fn uint  sfs_get_sexpr( char *input, FILE *fp )
 *
 * @brief extrait la prochaine S-Expression dans le flux fp et la stocke dans input
 * (meme si elle est repartie sur plusieurs lignes)
 * @param fp (FILE *) flux d'entree (ouvert en ecriture, mode texte)
 * @param input (char *) chaine allouee de taille BIGSTRING, dans laquelle la S-Expression sera stockée
 *
 * @return S_OK si une S-Expression apparemment valide a ete trouvee
 * @return S_KO si on n'a pas trouve de S-Expression valide
 * @return S_END si fin de fichier atteinte sans avoir lu de caractere utile.
 *
 * sfs_get_sexpr commence par lire une ligne dans fp,
 * puis compte le nombre de parentheses ouvrantes et fermantes sur la ligne.
 * Les parentheses dans des chaines et les caracteres Scheme #\( et #\)
 * ne sont pas comptes.
 *
 * Si le compte devient zero et que
 *        - la ligne est fini, la fonction retourne S_OK
 * 				- la ligne n'est pas fini la fonction retourne S_KO
 *
 * S'il y a plus de parentheses fermantes qu'ouvrantes,
 * la fonction retourne S_KO.
 * Les commentaires et espaces qui figurent a la fin de chaque ligne
 * sont remplaces par un espace.
 * Les espaces qui figurent a la fin de la S-Expression (y compris '\n')
 * sont supprimés.
 *
 * Attention : cette fonction refuse les S-Expression multiple sur une seule ligne. Ainsi :
 *    a b c
 *    (qqchose) (autrechose)
 *    (qqchose) 78
 * seront considereees comme des erreurs
 * et la fonction retournera S_KO
 *
 * @pre fp doit etre prealablement ouvert en lecture
 * @pre input doit etre prealablement alloue en memoire, de taille BIGSTRING
 */

typedef enum {
    NOTHING,        /* rien n'a ete trouve encore.. */
    STRING_ATOME,   /* la premiere trouvee dans la ligne semble etre un atome */
    BASIC_ATOME,    /* la premiere trouvee dans la ligne semble etre d'une chaine */
    S_EXPR_PARENTHESIS, /* la premiere trouvee dans la ligne semble etre une expression parenthesee */
    FINISHED        /* on a trouve une S-Expr bien formee */
} EXPRESSION_TYPE_T;

uint  sfs_get_sexpr( char *input, FILE *fp ) {
    int       parlevel = 0;
    uint      in_string = FALSE;
    uint      s = 0;
    char      k[BIGSTRING];
    char      *ret = NULL;
    char      *chunk = NULL;
    uint      i = 0;
    string    sfs_prompt;

    EXPRESSION_TYPE_T typeOfExpressionFound = NOTHING;

    parlevel = 0;
    memset( input, '\0', BIGSTRING );

    do {
        ret = NULL;
        chunk=k;
        memset( chunk, '\0', BIGSTRING );

        /* si en mode interactif*/
        if ( stdin == fp ) {
            uint nspaces = 2*parlevel;

            init_string( sfs_prompt );

            /* le prompt indique le niveau de parenthese
               et decale la prochaine entrée en fonction
               de ce niveau (un peu à la python)*/
            sprintf( sfs_prompt, "SFS:%u > ", parlevel );

            for ( i= 0; i< nspaces; i++ ) {
                sfs_prompt[strlen(sfs_prompt)] = ' ';
            }

            /* si sur plusieurs lignes, le \n équivaut à un espace*/
            if (nspaces>0) {
                input[strlen(input)+1] = '\0';
                input[strlen(input)] = ' ';
            }

            /*saisie de la prochaine ligne à ajouter dans l'input*/
            printf("%s",sfs_prompt);
            ret = fgets( chunk, BIGSTRING, fp );
            if (ret && chunk[strlen(chunk)-1] == '\n') chunk[strlen(chunk)-1] = '\0';

        }
        /*si en mode fichier*/
        else {
            ret = fgets( chunk, BIGSTRING, fp );

            if ( NULL == ret ) {
                /* fin de fichier...*/
                if ( parlevel != 0 ) {
                    WARNING_MSG( "Parse error: missing ')'" );
                    return S_KO;
                }
                return S_END;
            }

            if (strlen(chunk) == BIGSTRING-1
                    && chunk[BIGSTRING-1] != '\n'
                    && !feof(fp)) {
                WARNING_MSG( "Too long line for this interpreter!" );
                return S_KO;
            }
        }

        /* si la ligne est inutile
        	=> on va directement à la prochaine iteration */
        if (first_usefull_char(chunk) == NULL) {
            continue;
        }


        s = strlen( chunk );

        if ( s > 0 ) {
            if (strlen(input) + s > BIGSTRING-1 ) {
                WARNING_MSG( "Too long a S-expression for this interpreter!" );
                return S_KO;
            }

            for ( i = 0; i< strlen(chunk); i++ ) {
                /* si la fin de la ligne chunk est inutile,
                   on ajoute un espace dans input et on sort de la boucle*/
                if ( in_string == FALSE && first_usefull_char(chunk + i) == NULL ) {
                    chunk[i]='\0';
                    input[strlen(input)] = ' ';
                    break;
                }


                switch(chunk[i]) {
                case '(':
                    if (in_string == FALSE
                            && ! ( i>1 && chunk[i-1] == '\\' && chunk[i-2] == '#' ) ) {
                        parlevel++;
                        typeOfExpressionFound = S_EXPR_PARENTHESIS;
                    }
                    break;
                case ')':
                    if ( in_string == FALSE
                            && ! ( i>1 && chunk[i-1] == '\\' && chunk[i-2] == '#' ) ) {
                        parlevel--;
                        if (parlevel == 0 ) {
                            typeOfExpressionFound = FINISHED;
                        }
                        if ( parlevel < 0 ) {
                            WARNING_MSG( "Parse error : cannot start with ')'" );
                            return S_KO;
                        }
                    }
                    break;
                case '"':
                    if ( i<2 || chunk[i-1] != '\\' ) {
                        if ( in_string == FALSE ) {
                            if(typeOfExpressionFound == BASIC_ATOME) {
                                WARNING_MSG("Parse error: invalid string after atom : '%s'", chunk+i);
                                return S_KO;
                            }
                            in_string = TRUE;
                            if(typeOfExpressionFound != S_EXPR_PARENTHESIS) {
                                typeOfExpressionFound = STRING_ATOME;
                            }
                        }
                        else {
                            in_string = FALSE;
                            if(typeOfExpressionFound == STRING_ATOME) {
                                typeOfExpressionFound = FINISHED;
                            }
                        }
                    }
                    break;
                default:
                    if(in_string == FALSE) {
                        if(isspace(chunk[i])) {
                            if(typeOfExpressionFound == BASIC_ATOME) {
                                typeOfExpressionFound = FINISHED;
                            }
                        } else if(typeOfExpressionFound != S_EXPR_PARENTHESIS) {
                            typeOfExpressionFound = BASIC_ATOME;
                        }
                    }
                    break;
                }


                if(typeOfExpressionFound == FINISHED) {
                    char *first_useful = first_usefull_char(chunk + i + 1);
                    if( first_useful != NULL) {
                        if(*first_useful == ')' ) {
                            WARNING_MSG( "Parse error: too many closing parenthesis')'" );
                        }
                        else {
                            WARNING_MSG("Parse error: invalid trailing chars after S-Expr : '%s'", chunk+i);
                        }
                        return S_KO;
                    }
                }

                /* recopie char par char*/
                input[strlen(input)] = chunk[i];
            }
            if(in_string == TRUE) {
                WARNING_MSG( "Parse error: non terminated string on line %s", chunk );
                return S_KO;
            }
        }


        if ( parlevel > 0 && fp != stdin ) {
            if ( feof( fp ) ) {
                WARNING_MSG( "Parse error: missing ')'" );
                return S_KO;
            }

            if (input[strlen(input)-1] == '\n') input[strlen(input)-1] = ' ';
        }
    } while ( parlevel > 0 );

    /* Suppression des espaces restant a la fin de l'expression, notamment le dernier '\n' */
    while (isspace(input[strlen(input)-1])) input[strlen(input)-1] = '\0';

    return S_OK;
}

/* managing spaces */
void next_usefull_char(char *input, uint *here ) {

    while (isspace(input[*here])) {
        (*here)++;
    }

    }

object sfs_read( char *input, uint *here ) {

    next_usefull_char(input, here);


    if (input[*here]=='\'' )
    {(*here)++;
     next_usefull_char(input,here);

    return make_pair(make_symbol("quote"),sfs_read(input,here));


    }

    if ( input[*here] == '(' ) {
        if ( input[(*here)+1] == ')' ) {
            *here += 2;
            return nil;
        }
        else {
            (*here)++;
            return sfs_read_pair( input, here );
        }
    }
    else {
        return sfs_read_atom( input, here );
    }
}

/*fonction qui test si char c est un caractere special parmi ceux que l'on peut inclure dans les symboles*/
int isspecialchar(char c) {
    char s[16] = "+-!$%&*/:<=>?^_~";
    int i;
    for(i=0; i<16; i++) {
        if (s[i] == c)
            return TRUE;
    }
    return FALSE;
}
int is_not_separator(char c)
{
 if (c!= ')' && c!='(' && !isspace(c)){
return TRUE;}
return FALSE;
}

object sfs_read_atom( char *input, uint *here ) {

    enum ETATS {INIT, HASH_DETECTED, BOOL, CHAR_IN_PROG, SYMBOL, STRING, INT_IN_PROG, INT, END, EXIT, ERROR};
    enum ETATS etat = INIT;
    object atom = NULL;
    char s[256];
    int i = 0;


    /* mandatory objects for strtol */
    uint bool;
    uint base = 10;
    char *endptr;
    long int integer = 0;
    /* end of mandatory objects*/

    while (etat != EXIT || etat != ERROR)
    {
        switch(etat)
        {

        case INIT:
            if (input[*here] == '#')
            {
                etat = HASH_DETECTED;
                (*here)++;
            }
            /* on verifie si l'utilisateur rentre bien un int qui commence eventuellement par un moins ou un plus */
            else if ((input[*here] == '-' && isdigit(input[*here+1]))  || (input[*here] == '+' && isdigit(input[*here+1])) || isdigit(input[*here])) /* on verifie si l'utilisateur rentre bien un int qui commence eventuellement par un moins ou un plus */
            {
                etat = INT_IN_PROG;
            }

            else if(input[*here]=='"')
            {   etat=STRING;
                (*here)++;
            }
            else if(isspecialchar(input[*here]) || isalpha(input[*here])) {
                etat=SYMBOL;
            }
            else
                etat = EXIT;
            break;


        /* cas ou l'atome debute par un # */
        case HASH_DETECTED:
            if (input[*here] == 'f')
            {
                bool = FALSE;
                etat = BOOL;
                (*here)++;
            }
            else if (input[*here] =='t')
            {
                bool = TRUE;
                etat = BOOL;
                (*here)++;
            }
            else if (input[*here] == '\\')
            {
                (*here)++;
                etat = CHAR_IN_PROG;
            }
            else {
                WARNING_MSG("NOT A PROPER BOOLEAN OR CHARACTER");
                etat=ERROR;
            }
            break;

        /* cas booleen (on sait qu'il y a un # puis un f ou un t) */
        case BOOL:
            if (is_not_separator(input[*here]) && isgraph(input[*here]))
            {   WARNING_MSG("NOT A PROPER BOOLEAN OR CHARACTER");
                etat=ERROR;
            } /* erreur si il y a qqch apres #f ou #t */
            else {
                atom = make_boolean(bool);
                etat = END;
            }
            break;

        /* cas caractere (on sait qu'il y a un # et un antislash) */
        case CHAR_IN_PROG :

            if (isgraph(input[*here]) && isgraph(input[*here+1]) && input[*here+1] != ')') {
                if(strncmp(input + *here, "space", 5) == 0) {
                    (*here) += 5;
                    atom=make_character(' ');
                    etat=END;
                }

                else if(strncmp(input + *here, "newline", 7) == 0) {
                    (*here) += 7;
                    atom=make_character('\n');
                    etat=END;
                }

                else {
                    WARNING_MSG("NOT A PROPER CHARACTER : TOO LONG OR NOT EXACTLY NEWLINE OR SPACE");
                    etat=ERROR;
                }
            }
            else if (isgraph(input[*here]))
            {
                atom=make_character(input[*here]);
                (*here)++;
                etat=END;
            }
            else {
                WARNING_MSG("NOT A PROPER CHARACTER");
                etat=ERROR;
            }
            break;

        case SYMBOL :
	    while(isgraph(input[*here]) && is_not_separator(input[*here])){
		s[i] = input[*here];
		i++;
		(*here)++;
	    }
	    s[i] = '\0';
            atom=make_symbol(s);
            etat=END;

            break;

        case STRING:

            while(input[*here]!='"')
            {
                size_t tmp=strlen(s);
                s[tmp]=input[*here];
                s[tmp+1]='\0';
                if (input[*here]=='\\' && input[*here+1]=='\"' && isprint(input[*here+2]))
                {   s[tmp]='"';
                    *here=*here+2;
                }
                else {
                    (*here)++;
                }

            }
            (*here)++;

            atom=make_string(s);
            etat=END;
            break;

        /*cas entier*/
        case INT_IN_PROG :
            integer = strtol(input + *here, &endptr , base);
            /*gestion des erreurs avec endptr*/
            if(endptr != NULL && isgraph(*endptr) && is_not_separator(*endptr))
            {
                WARNING_MSG("NUMBER ERROR : not a number");
                etat = ERROR;
            }
            else {
                *here = endptr - input;
                etat = INT;
            }
            break;

        case INT:
            atom = make_integer(integer);
            etat = END;
            break;

        case END:
            return atom;
            etat = EXIT;
            break;
        case ERROR:
            return NULL;
            break;

        default:
            WARNING_MSG("error : switch not ended sfs_read_atom\n");
            return nil;
            etat = EXIT;
            break;

        }
    }
    return nil; /* pour eviter attention : ‘return’ with no value, in function returning non-void [-Wreturn-type] */
}


object sfs_read_pair( char *input, uint *here ) {
    object pair = NULL;
    object car = NULL;
    object cdr = NULL;

    next_usefull_char(input, here);

    if ( input[*here] == ')' ) {
        (*here)++ ;
        return nil;
    }

    car = sfs_read (input,here);
    cdr = sfs_read_pair (input,here);
    pair = make_pair(car,cdr);


    return pair;
}
