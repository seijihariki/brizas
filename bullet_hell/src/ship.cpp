#include "ship.hpp"


Ship::Ship (sf::Vector2f pos, int team, ShipController *controller)
    : controller(controller), team(team), pos(pos)
{
}

/***********************
 * Getters and setters *
 ***********************/

sf::Vector2f Ship::getPosition()
{
    return pos;
}

void Ship::setPosition(sf::Vector2f pos)
{
    this->pos = pos;
}

int Ship::getTeam()
{
    return team;
}

/* ******** *
 * Updating *
 * ******** */

void Ship::update(sf::Time dt)
{
    pos += controller->getVel()*dt.asSeconds();
}

/* ******* *
 * Drawing *
 * ******* */

void Ship::draw(sf::RenderWindow &window)
{
    sf::RectangleShape rect;
    rect.setSize({20, 20});
    rect.setOrigin(10, 5);
    rect.setPosition(pos);
    rect.setFillColor(sf::Color::Blue);
    window.draw(rect);
}
