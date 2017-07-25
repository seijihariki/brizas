#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <SFML/Graphics.hpp>

typedef unsigned int uint;

template<typename C>
class Map
{
public:
    Map (sf::Vector2u size);
    ~Map ();

    void set (sf::Vector2u coords, C value);
    C get (sf::Vector2u coords);

    sf::Vector2u getSize ();

private:
    sf::Vector2u size;

    C **map;
};

template class Map<sf::Vector2u>;
template class Map<sf::Vector2i>;
template class Map<int>;
template class Map<bool>;

#endif
