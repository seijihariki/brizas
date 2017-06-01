
#ifndef __COLOR_HPP__
#define __COLOR_HPP__

typedef unsigned int uint;

struct Color
{
public:
    Color(uint r, uint g, uint b) : r(r), g(g), b(b) {}

    const uint r, g, b;
};

#endif
