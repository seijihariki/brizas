#ifndef __OSTRICH_HPP__
#define __OSTRICH_HPP__

#include <string>

#include "02-bird.hpp"
#include "02-color.hpp"

class Ostrich : public Bird
{
public:
    Ostrich(Color color, std::string name, uint size) :
        Bird(color, name, size) {}

    // Prints greeting 'Hi, I'm <name> the ostrich'
    void greet();
};

#endif
