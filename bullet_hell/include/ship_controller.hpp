#include <SFML/Graphics.hpp>

#ifndef __SHIPCONTROLLER_HPP__
#define __SHIPCONTROLLER_HPP__

class ShipController
{
public:
    virtual sf::Vector2f getVel() = 0;
};

#endif
