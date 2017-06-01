#include <stdio.h>
#include "include/02-ostrich.hpp"

void Ostrich::greet()
{
    printf ("Hi, I'm %s the ostrich\n", name.c_str());
}
