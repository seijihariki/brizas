#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <SFML/Graphics.hpp>

struct Material;
struct Tile;
class MapGenerator;
class Map;

typedef std::map<std::string, Material*> MaterialList;

/* Struct representing materials: Stores material properties, like thermal  *
 * conductivity and density                                                 *
 *                                                                          *
 *                                                                          */
struct Material {
    Material();
};

/* Struct representing tiles: Stores tile information, such as pressure,    *
 * humidity and material information                                        *
 *                                                                          *
 *                                                                          */
struct Tile {
    Tile();
};


/* Base abstract class for generating Maps. Should be used for different    *
 * map generation algorithms                                                *
 *                                                                          *
 *                                                                          */
class MapGenerator {
    friend Map;
private:
    // Function generates a map
    virtual void generateMap(int w, int h, long int seed = time(0)) = 0;
};

/* Represents a map: Represents a map and simulates it. Can be thought of   *
 * as the world.                                                            *
 *                                                                          *
 *                                                                          */
class Map : public sf::Drawable {
// Methods
public:
    Map(int w, int h);
    Map(int w, int h, MapGenerator *generator);

    void update(sf::Time dt);

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states);

// Variables
public:
private:
    int w, h;
    Tile **data;

    MaterialList materials;
};

#endif
