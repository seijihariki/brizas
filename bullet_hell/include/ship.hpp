#include <SFML/Graphics.hpp>
#include "ship_controller.hpp"

#ifndef __SHIP_HPP__
#define __SHIP_HPP__

class Ship
{
public:
    Ship (sf::Vector2f pos, int team, ShipController *controller);

    sf::Vector2f getPosition();
    void setPosition(sf::Vector2f pos);

    int getTeam();

    void update(sf::Time dt);

    void draw(sf::RenderWindow &window);

private:
    ShipController *controller;
    int team;
    sf::Vector2f pos;
};

#endif
