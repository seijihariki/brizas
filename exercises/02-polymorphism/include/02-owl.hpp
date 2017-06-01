#ifndef __OWL_HPP__
#define __OWL_HPP__

#include <string>

#include "02-bird.hpp"
#include "02-color.hpp"

class Owl : public Bird
{
public:
    Owl(Color color, std::string name, uint size) :
        Bird(color, name, size) {}

    // Prints greeting 'Hello, my name is <name> and I'm an owl'
    void greet();
};

#endif
