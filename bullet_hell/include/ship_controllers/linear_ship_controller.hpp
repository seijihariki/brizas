#include <SFML/Graphics.hpp>
#include "ship_controller.hpp"

#ifndef __LINEARSHIPCONTROLLER_HPP__
#define __LINEARSHIPCONTROLLER_HPP__

class LinearShipController : public ShipController
{
public:
    LinearShipController(sf::Vector2f vel);

    sf::Vector2f getVel();

private:
    sf::Vector2f vel;
};

#endif
