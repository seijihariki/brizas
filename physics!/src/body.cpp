#include "body.hpp"

Body::Body (double mass, sf::Vector2<double> pos, sf::Vector2<double> vel)
    :mass(mass), pos(pos), vel(vel)
{
}

/***********************
 * Getters and setters *
 ***********************/

double Body::getMass()
{
    return mass;
}

sf::Vector2<double> Body::getPosition()
{
    return pos;
}

void Body::setPosition(sf::Vector2<double> pos)
{
    this->pos = pos;
}

sf::Vector2<double> Body::getSpeed()
{
    return vel;
}

void Body::setSpeed(sf::Vector2<double> vel)
{
    this->vel = vel;
}

void Body::applyForce(sf::Vector2<double> force)
{
    res += force;
}

void Body::applyImpulse(sf::Vector2<double> impulse)
{
    vel += impulse;
}

/* ******** *
 * Updating *
 * ******** */

void Body::update(sf::Time dt)
{
    vel += res*((double) dt.asSeconds());
    pos += vel*((double) dt.asSeconds());
    res = sf::Vector2<double>(0, 0);
}

/* ******* *
 * Drawing *
 * ******* */

void Body::draw(sf::RenderWindow &window)
{
    sf::CircleShape shape(5);
    shape.setOrigin(5, 5);
    shape.setPosition(sf::Vector2f(pos.x, pos.y));
    shape.setFillColor(sf::Color::Green);
    window.draw(shape);
}
