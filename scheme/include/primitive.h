#include "object.h"

void init_primitive ( object );


/*arithmetique*/
object plus(object);
object minus(object);
object multiply(object);
object quotient(object);
object superior(object);
object inferior(object);


/* predicats */
object boolean_p(object);
object symbol_p(object);
object integer_p(object);
object char_p(object);
object string_p(object);
object pair_p(object);
object null_p(object);
