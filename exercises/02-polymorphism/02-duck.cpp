#include <stdio.h>
#include "include/02-duck.hpp"

void Duck::greet()
{
    printf ("Nice to meet you! I'm %s duck!\n", name.c_str());
}
