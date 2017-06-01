/*****************************************************************************
 * Here we see if you know how to implement classes with basic inheritance,  *
 * access conditions (public, private and protected) and constructor         *
 * initializers. You should obey the rules in each hpp file.                 *
 *****************************************************************************/

#include <iostream>
#include <stdio.h>

// Here we include your headers.

// Your task is to implement the Circle class, the
// Square class and the Shape class.

// You could use .h for headers, but I prefer to use .hpp to clarify that it's
// c++, not c.
#include "include/01-shape.hpp"
#include "include/01-circle.hpp"
#include "include/01-square.hpp"

// Here is the main. We create a circle and a square. We then create a vector of
// Shape pointers (polymorphism - don't worry about this on this exercise). We
// then test them both. The circle class may be based on code from exercise 00.
int main ()
{
    // Creates a circle and a square
    Circle circle (5, 2, 4); // radius, x and y
    Square square (3, 5, 6); // side size, x and y

    // Creates vector of Shape pointers
    Shape *shapes[2];

    shapes[0] = &circle;
    shapes[1] = &square;

    // Now these are the tests of the classes
    printf ("circle_std : r\tx\ty\n");
    printf ("square_std : s\tx\ty\n");

    printf ("circle_poly: a\tx\ty\n");
    printf ("square_poly: a\tx\ty\n");

    // Testing circle and its array entry
    printf ("circle_std : %f\t%f\t%f (5, 2, 4)\n",
            circle.radius(),
            circle.x(),
            circle.y()
            );

    printf ("circle_poly: %f\t%f\t%f (~78.5, 2, 4)\n",
            shapes[0]->area(),
            shapes[0]->x(),
            shapes[0]->y()
            );

    // Testing square and its array entry
    printf ("square_std : %f\t%f\t%f (3, 5, 6)\n",
            square.radius(),
            square.x(),
            square.y()
            );

    printf ("square_poly: %f\t%f\t%f (9, 5, 6)\n",
            shapes[0]->area(),
            shapes[1]->x(),
            shapes[1]->y()
            );
    // Not necessary, justo good practice
    return 0;
}
