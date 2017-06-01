#ifndef __BIRD_HPP__
#define __BIRD_HPP__

#include <string>

#include "02-color.hpp"

class Bird
{
public:
    Bird(Color color, std::string name, uint size) :
        color(color), name(name), size(size) {}

    // Prints greeting
    virtual void greet() = 0;

    Color getColor();
    std::string getName();
    uint getSize();

protected:
    Color color;
    std::string name;
    uint size;
};

#endif
