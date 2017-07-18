#include <SFML/Graphics.hpp>

#include "world.hpp"

class FlatLand : public MapGenerator
{
public:
    void generate (Tile **map, uint w, uint h)
    {
        for (uint x = 0; x < w; x++)
        {
            for (uint y = 0; y < h; y++)
            {
                Tile &tile = map[x][y];
                if ((h - y) <= h / 10.0 || rand()%100 < 2)
                {
                    tile.fill_color   = sf::Color(0, 198, 23);
                    tile.border_color = sf::Color(46, 173, 0);
                    tile.transparency = (rand()%100)/100.0f;
                }
                else
                {
                    tile.fill_color   = sf::Color(89, 213, 255);
                    tile.border_color = sf::Color(89, 172, 255);
                    tile.transparency = 1;
                }
            }
        }
    }
};

void eventHandler (sf::Event &event, sf::RenderWindow &window)
{
    switch (event.type)
    {
    case sf::Event::Closed:
        window.close();
        break;
    default:
        break;
    }
}

int main ()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "World tester");

    World world(80, 60);
    FlatLand generator;
    world.generate(&generator);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
            eventHandler(event, window);

        window.clear();
        window.draw(world);
        window.display();
    }
}
