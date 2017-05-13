#include <SFML/Graphics.hpp>
#include <vector>

#include "ship_controllers/input_ship_controller.hpp"
#include "ship_controllers/linear_ship_controller.hpp"
#include "ship.hpp"

#include "bullet.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");

    InputShipController *input_controller = new InputShipController(500);

    std::vector<Ship*> ships;
    std::vector<Bullet*> bullet;
    ships.push_back(new Ship(sf::Vector2f(400, 780), 0, input_controller));

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Time time = clock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            input_controller->handleKeyboard(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for (Ship *ship : ships)
            ship->update(time);

        window.clear();
        for (Ship *ship : ships)
            ship->draw(window);
        window.display();
    }

    return 0;
}
