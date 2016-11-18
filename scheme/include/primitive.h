#include "object.h"

void init_primitive ( object );


/*arithmetique*/
object plus(object);
object minus(object);
object multiply(object);
object quotient(object);
object superior(object);
object inferior(object);
object equal(object);


/* predicats */
object boolean_p(object);
object symbol_p(object);
object integer_p(object);
object char_p(object);
object string_p(object);
object pair_p(object);
object null_p(object);


/* manip de listes */

object cons(object);
object car_p(object);
object cdr_p(object);

/* convertion de type */
object chtoint (object);
object inttoch (object);
object numbtostr (object);
object strtonumb (object);
object symtostr (object);
object strtosym (object);

