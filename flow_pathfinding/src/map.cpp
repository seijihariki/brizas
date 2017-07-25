#include "map.hpp"

template<typename C>
Map<C>::Map (sf::Vector2u size) :
    size(size)
{
    map = new C*[size.x];
    for (uint x = 0; x < size.x; x++)
        map[x] = new C[size.y];
}

template<typename C>
Map<C>::~Map ()
{
    for (uint x = 0; x < size.x; x++)
        delete map[x];
    delete map;
}

template<typename C>
void Map<C>::set (sf::Vector2u coords, C value)
{
    map[coords.x][coords.y] = value;
}

template<typename C>
C Map<C>::get (sf::Vector2u coords)
{
    return map[coords.x][coords.y];
}

template<typename C>
sf::Vector2u Map<C>::getSize ()
{
    return size;
}
