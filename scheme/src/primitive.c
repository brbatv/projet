#include "object.h"

void init_primitive ( object env ){

make_and_modify_binding(env,"+",make_primitive(plus));
make_and_modify_binding(env,"-",make_primitive(minus));
make_and_modify_binding(env,"",make_primitive(multiply));

}
