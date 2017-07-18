#ifndef __LIGHT_HPP__
#define __LIGHT_HPP__

#include <vector>

#include "world.hpp"

class Tile;
class World;

class Light : public sf::Drawable {
public:
    Light (const World *world);

    void recalculate (double final_square_size, sf::Vector2f initial_coords);

    ~Light();

private:
    virtual void draw(sf::RenderTarget& target,
            sf::RenderStates states) const;

    std::vector<sf::Shape*> components;
    const World *world;
};

#endif // __LIGHT_HPP__
