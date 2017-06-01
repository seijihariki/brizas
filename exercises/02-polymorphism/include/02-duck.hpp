#ifndef __DUCK_HPP__
#define __DUCK_HPP__

#include <string>

#include "02-bird.hpp"
#include "02-color.hpp"

class Duck : public Bird
{
public:
    Duck(Color color, std::string name, uint size) :
        Bird(color, name, size) {}

    // Prints greeting 'Nice to meet you! I'm <name> duck!'
    void greet();
};

#endif
