#include <SFML/Graphics.hpp>
#include "ship_controller.hpp"

#ifndef __INPUTSHIPCONTROLLER_HPP__
#define __INPUTSHIPCONTROLLER_HPP__

class InputShipController : public ShipController
{
public:
    InputShipController(float vel);

    bool handleKeyboard(sf::Event evn);

    sf::Vector2f getVel();

private:
    bool pressed[4]; // UP, DOWN, LEFT, RIGHT
    float vel_mod;
    sf::Vector2f vel;
};

#endif
