#include <stdio.h>
#include "include/02-owl.hpp"

void Owl::greet()
{
    printf ("Hello, my name is %s and I'm an owl\n", name.c_str());
}
