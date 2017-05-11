#include "ship_controllers/input_ship_controller.hpp"

InputShipController::InputShipController(float vel)
    : vel_mod(vel)
{
}

bool InputShipController::handleKeyboard(sf::Event evn)
{
    if (evn.type == sf::Event::KeyPressed)
    {
        switch (evn.key.code)
        {
            case sf::Keyboard::W:
                pressed[0] = true;
                break;
            case sf::Keyboard::S:
                pressed[1] = true;
                break;
            case sf::Keyboard::A:
                pressed[2] = true;
                break;
            case sf::Keyboard::D:
                pressed[3] = true;
                break;
            default:
                return false;
                break;
        }
    }
    else if (evn.type == sf::Event::KeyReleased)
    {
        switch (evn.key.code)
        {
            case sf::Keyboard::W:
                pressed[0] = false;
                break;
            case sf::Keyboard::S:
                pressed[1] = false;
                break;
            case sf::Keyboard::A:
                pressed[2] = false;
                break;
            case sf::Keyboard::D:
                pressed[3] = false;
                break;
            default:
                return false;
                break;
        }
    }
    else return false;

    return true;
}

sf::Vector2f InputShipController::getVel()
{
    sf::Vector2f vel(0, 0);

    if (pressed[0]) vel.y--;
    if (pressed[1]) vel.y++;
    if (pressed[2]) vel.x--;
    if (pressed[3]) vel.x++;

    float len = sqrt(vel.x*vel.x + vel.y*vel.y);

    if (len == 0)
        return vel;

    vel /= len;
    vel *= vel_mod;

    return vel;
}


