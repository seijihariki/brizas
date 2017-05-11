#include <SFML/Graphics.hpp>
#include <vector>

#include "body.hpp"

std::vector<Body*> bodies;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");

    bodies.push_back(new Body(
                50000,
                sf::Vector2<double>(500, 400),
                sf::Vector2<double>(0, -100)
                ));
    
    bodies.push_back(new Body(
                50000,
                sf::Vector2<double>(300, 400),
                sf::Vector2<double>(0, 100)
                ));

    bodies.push_back(new Body(
                50000,
                sf::Vector2<double>(400, 300),
                sf::Vector2<double>(-100, 0)
                ));
    
    bodies.push_back(new Body(
                50000,
                sf::Vector2<double>(400, 500),
                sf::Vector2<double>(100, 0)
                ));
    
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Time time = clock.restart();
        for (Body *body1 : bodies)
        {
            for (Body *body2 : bodies)
            {
                if (body1 == body2)
                    continue;
                sf::Vector2<double> diff = body2->getPosition() - body1->getPosition();
                double dist = diff.x*diff.x + diff.y*diff.y;
                diff /= dist;
                body1->applyForce(diff*(body1->getMass() + body2->getMass()/dist));
            }
        }

        for (Body *body : bodies)
            body->update(time);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        for (Body *body : bodies)
            body->draw(window);
        window.display();
    }

    return 0;
}
