#include "object.h"
#include "mem.h"

/*fonction qui test si l'objet est une pair*/
int ispair(object o) {

    if (o == NULL)
	return FALSE;
    if (o->type == 	SFS_PAIR)
        return TRUE;
    else return FALSE;

}

/*fonction qui test si l'objet est un symbol*/
int issymbol(object o) {

     if (o == NULL)
	return FALSE;

    if (o->type ==  SFS_SYMBOL)
        return TRUE;
    else return FALSE;

}

int isnumber(object o)
{

    if (o == NULL)
	return FALSE;
    if (o->type ==  SFS_NUMBER)
        return TRUE;
    else return FALSE;


}

int ischar(object o)
{
    if (o == NULL)
	return FALSE;
    if (o->type ==  SFS_CHARACTER)
        return TRUE;
    else return FALSE;


}

int isstring(object o)
{

    if (o == NULL)
	return FALSE;
    if (o->type ==  SFS_STRING)
        return TRUE;
    else return FALSE;


}

int isboolean(object o)
{

    if (o == NULL)
	return FALSE;
    if (o->type ==  SFS_BOOLEAN)
        return TRUE;
    else return FALSE;


}

/*fonction qui test si l'objet est nil*/
int isnil(object o) {

    if (o == NULL)
	return FALSE;
    if (o == nil)
        return TRUE;
    else return FALSE;

}

/*fonction qui test si l'objet est un atom*/
int isatom(object o) {


    if (o == NULL)
	return FALSE;
    return !ispair(o);
}

/*fonction qui renvoie un booleen en fonction de si oui ou non o est le symbole quote*/
int isquote(object o) {

    if(o->type == SFS_SYMBOL && strcmp(o->this.symbol,"quote") == 0)
        return TRUE;
    else
        return FALSE;

}

/*fonction qui renvoie un booleen en fonction de si oui ou non o est le symbole define*/
int isdefine(object o) {

    if(o->type == SFS_SYMBOL && strcmp(o->this.symbol,"define") == 0)
        return TRUE;
    else
        return FALSE;

}

/*fonction qui renvoie un booleen en fonction de si oui ou non o est le symbole set!*/
int isset(object o) {

    if( o->type == SFS_SYMBOL && strcmp(o->this.symbol,"set!") == 0)
        return TRUE;
    else
        return FALSE;

}

/*fonction qui renvoie un booleen en fonction de si oui ou non o est le symbole if*/
int isif(object o) {

    if(o->type == SFS_SYMBOL && strcmp(o->this.symbol,"if") == 0)
        return TRUE;
    else
        return FALSE;

}

/*fonction qui renvoie un booleen en fonction de si oui ou non o est le symbole and*/
int isand(object o) {

    if(o->type == SFS_SYMBOL && strcmp(o->this.symbol,"and") == 0)
        return TRUE;
    else
        return FALSE;

}

/*fonction qui renvoie un booleen en fonction de si oui ou non o est le symbole or*/
int isor(object o) {

    if(o->type == SFS_SYMBOL && strcmp(o->this.symbol,"or") == 0)
        return TRUE;
    else
        return FALSE;

}

/*fonction qui renvoie un booleen en fonction de si oui ou non o est une forme*/
int isform(object o) {

    return isdefine(o) || isset(o) || isif(o) || isand(o) || isor(o);

}

/*fonction qui test si l'objet o est vrai ou faux au sens du Scheme et renvoie la valeur FASLE ou TRUE au sens du C*/
int istrue(object o) {

    if(o == false)
        return FALSE;
    else
        return TRUE;

}

/* fonction qui teste si l'objet de type primitive */
int isprimitive(object o) {

    if (o == NULL)
	return FALSE;
    if (o->type ==  SFS_PRIMITIVE)
        return TRUE;
    else return FALSE;

}
