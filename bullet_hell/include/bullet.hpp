#include <SFML/Graphics.hpp>

#ifndef __BULLET_HPP__
#define __BULLET_HPP__

class Bullet
{
public:
    Bullet (sf::Vector2f pos, int team);

    sf::Vector2f getPosition();

    int getTeam();

    virtual void update(sf::Time dt) = 0;

    virtual void draw(sf::RenderWindow &window) = 0;

private:
    int team;
    sf::Vector2f pos;
};

#endif
