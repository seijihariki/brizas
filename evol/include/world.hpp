/*! \file world.hpp
    \brief Header of World class

    It contains the declaration of the World class.
*/

#ifndef __WORLD_HPP__
#define __WORLD_HPP__

#include <SFML/Graphics.hpp>

#include "typedefs.hpp"


/*! \struct Tile
 *  \brief Struct that represents an tile in the world.
 *
 *  This struct represents a world tile. It stores all necessary data for a
 *  particular tile, like temperature and material.
 */
struct Tile
{
    double solid_mass;      //!< Mass of solid content (In kilograms)
    double temperature;     //!< Temperature (In celcius)
    double water_content;   //!< Amount of water (In kilograms)
    double occupied;        //!< Percentage of volume occupied by solid content
    sf::Color fill_color;   //!< Fill color of the tile
    sf::Color border_color; //!< Border color of the tile
};


/*! \class MapGenerator
 *  \brief Class that represents a generator for a map
 *
 *  This class represents a map generator. Basically, a function that sets the
 *  initial state for the map.
 */

class MapGenerator
{
public:
    virtual void generate (Tile **map, uint w, uint h) = 0;
};

/*! \class World
 *  \brief class for storing world state information.
 *         this is the base class for simulation.
 *
 *  This class stores all map information, and takes care of updating the world.
 *  it keeps track of simulation time, calculates deltas, and updates all
 *  existing nodes.
 */
class World : public sf::Drawable
{
public:
    World (const uint w,
            const uint h,
            sf::Time day_duration = sf::seconds(60));

    void update ();

    void generate (MapGenerator *generator);

    uint width () const;
    uint height () const;

    // Returns the elapsed time since the beginning of the simulation
    sf::Time elapsedTime () const;
    // Returns current day in simulation (First is day 1)
    uint day () const;
    // Returns fraction of current day passed in simulation (0 to 1)
    double dayTime () const;

    ~World ();

private:
    virtual void draw(sf::RenderTarget& target,
            sf::RenderStates states) const;


    Tile **map;             //!< Actual map, that is, a matrix of Tiles

    sf::Clock delta;        //!< In-between frame clock
    sf::Clock clock;        //!< Absolute time clock

    sf::Time day_duration;  //!< Duration of a simulation day in real time
    const uint w;           //!< Map width (in tiles)
    const uint h;           //!< Map height (in tiles)
};

#endif
