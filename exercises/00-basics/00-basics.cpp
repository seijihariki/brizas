/*****************************************************************************
 * This exercise is to check if you know the basics of OOP. Things like      *
 * classes, constructors, members and methods are some of the terminology    *
 * you will need to know do this exercise.                                   *
 *****************************************************************************/

#include <iostream>
#include <stdio.h>

// Here we include your headers. Your task is to implement the Circle class.
// You could use .h for headers, but I prefer to use .hpp to clarify that it's
// c++, not c.
#include "include/00-circle.hpp"

// Here is the main. We create two circles. Circle 1 has the default
// constructor, and circle 2 is created with a radius and position.
int main ()
{
    Circle circle1;

    {
        Circle circle2(5, 0, 0);

        // Now these are the tests of the class.
        printf ("circles: r\tx\ty\n");
        printf ("circle1: %f\t%f\t%f (0, 0, 0)\n", circle1.radius(), circle1.x(), circle1.y());
        std::cout << "circle1 area: " << circle1.area() << " (0)\n";
        printf ("circle2: %f\t%f\t%f (0, 0, 0)\n", circle2.radius(), circle2.x(), circle2.y());
        std::cout << "circle2 area: " << circle2.area() << " (+-25*PI)\n";

        // Here we finally initialize circle1 data (and test the 'set' method)
        circle1.set(2);
        printf ("circle1: %f\t%f\t%f (2, 0, 0)\n", circle1.radius(), circle1.x(), circle.y());
        circle1.set(2, 1);
        printf ("circle1: %f\t%f\t%f (2, 1, 0)\n", circle1.radius(), circle1.x(), circle.y());
        circle1.set(2, 10, 10);
        printf ("circle1: %f\t%f\t%f (2, 10, 10)\n", circle1.radius(), circle1.x(), circle.y());

        // Here we check for collisions
        printf ("circle1.collides: %d (0)\n", circle1.collides(circle2));
        printf ("circle2.collides: %d (0)\n", circle2.collides(circle1));

        // We now move circle2 to (10, 4)
        circle2.set(circle2.radius(), 10, 4);

        // Here we check again for collisions
        printf ("circle1.collides: %d (1)\n", circle1.collides(circle2));
        printf ("circle2.collides: %d (1)\n", circle2.collides(circle1));

        // Tests end! Finally, destructor test!
        printf ("Should print:\ncircle: (5, 10, 4)\n");
    }
    printf ("Should print:\ncircle: (2, 10, 10)\n");

    // Not necessary, justo good practice
    return 0;
}
