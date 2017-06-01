/*****************************************************************************
 * Now you should use the classes, instead of just implementing them. You    *
 * may want to give a look at the main of the last exercise to see how it's  *
 * done. It also forces you to use some implemented c++ std facilities.      *
 *****************************************************************************/

#include <string>
#include <iostream>
#include <stdio.h>
// Provides std::vector (dinamically resizing stack)
#include <vector>
// Provides rand()
#include <cstdlib>
// Just for seeding the prng
#include <time.h>

// Here I include my headers. You shouldn't modify them
#include "include/02-color.hpp"
#include "include/02-bird.hpp"
#include "include/02-ostrich.hpp"
#include "include/02-duck.hpp"
#include "include/02-owl.hpp"

// This function puts n random birds in the vector
void genbirds (std::vector<Bird*> &bird_vec, int n)
{
}

// This time, your work is to create the main. It must run the function
// 'genbirds', you must implement above, and print their name (type String),
// size (type int: 0, 1 or 2) and their color (type Color). After all that, it
// must run all greetings.
int main ()
{
    // Seeds the random number generator
    srand(time(0));

    // Here is your code:


    // Not necessary, just good practice
    return 0;
}
