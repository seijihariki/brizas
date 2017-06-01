/*****************************************************************************
 * It's now time to use a very useful feature in c++. Operator declarations  *
 * can be great if well implemented. You can then use the default aritmetic  *
 * operations with your own classes. It is also pretty straightforward.      *
 *****************************************************************************/

#include <string>
#include <iostream>
#include <stdio.h>

// Here we include your headers. Your job this time is to implement a vector
// class. (Mathematical vectors)
#include "include/03-vector.hpp"

// Here we create two vectors and verify if they are working properly.
int main ()
{
    Vector vector1(6, 10);
    Vector vector2(5, 2);

    // Now we start the tests
    printf ("vector1: (%f, %f) - (6, 10)\n", vector1.x, vector1.y);
    printf ("vector2: (%f, %f) - (5, 2)\n", vector2.x, vector2.y);

    // Checking sum...
    Vector tmp = vector1 + vector2;
    printf ("vector1 + vector2: (%f, %f) - (11, 12)\n", tmp.x, tmp.y);

    // Checking subtraction...
    tmp = vector1 - vector2;
    printf ("vector1 - vector2: (%f, %f) - (1, 8)\n", tmp.x, tmp.y);

    // Checking dot product...
    float dot = vector1 * vector2;
    printf ("vector1 * vector2: %f - 50\n", dot);

    // Checking multiplication by scalar
    tmp = vector2 * 5;
    printf ("vector2 * 5: (%f, %f) - (25, 10)\n", tmp.x, tmp.y);

    // Checking multiplication by scalar
    tmp = vector1 / 2;
    printf ("vector1 / 2: (%f, %f) - (3, 5)\n", tmp.x, tmp.y);
    
    // Checking square brackets reference operator
    printf ("vector1[0]: %f - 6\n", vector1[0]);
    printf ("vector1[1]: %f - 10\n", vector1[1]);
    printf ("vector2[0]: %f - 5\n", vector2[0]);
    printf ("vector2[1]: %f - 2\n", vector2[1]);

    // Checking comparison with other vector
    printf (vector1 == vector2 ? "WRONG\n" : "RIGHT\n");
    vector1 = vector2;
    printf (vector1 == vector2 ? "RIGHT\n" : "WRONG\n");

    // Not necessary, just good practice
    return 0;
}
