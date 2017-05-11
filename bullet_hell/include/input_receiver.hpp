#include <SFML/Graphics.hpp>

#ifndef __INPUTRECEIVER_HPP__
#define __INPUTRECEIVER_HPP__

class InputReceiver
{
public:
    InputController();

    sf::Vector2f handleInput(sf::Event &evn);
};

#endif
