#include <SFML/Graphics.hpp>

class Body
{
public:
    Body (double mass, sf::Vector2<double> pos, sf::Vector2<double> vel);

    double getMass();

    sf::Vector2<double> getPosition();
    void setPosition(sf::Vector2<double> pos);

    sf::Vector2<double> getSpeed();
    void setSpeed(sf::Vector2<double> vel);

    void applyForce(sf::Vector2<double> force);
    void applyImpulse(sf::Vector2<double> impulse);

    void update(sf::Time dt);

    void draw(sf::RenderWindow &window);

private:
    double mass;
    sf::Vector2<double> res;
    sf::Vector2<double> pos, vel;
};
