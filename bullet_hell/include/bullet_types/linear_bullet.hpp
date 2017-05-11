#ifndef __LINEAR_BULLET_HPP__
#define __LINEAR_BULLET_HPP__

class LinearBullet
{
public:
    LinearBullet (sf::Vector2f pos, sf::Vector2f vel, int team);

    void update(sf::Time dt);

    void draw(sf::RenderWindow &window);

private:
    sf::Vector2f vel;
};

#endif
