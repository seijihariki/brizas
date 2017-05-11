#include "bullet.hpp"

Bullet::Bullet (sf::Vector2f pos, int team)
    : team(team), pos(pos)
{
}

/***********************
 * Getters and setters *
 ***********************/

sf::Vector2f Bullet::getPosition()
{
    return pos;
}

int Bullet::getTeam()
{
    return team;
}
