#include "light.hpp"

#include <cmath>

// Constructors

Light::Light (const World *world) :
    world(world)
{
}

// Destructor

Light::~Light ()
{

}

// Other

void Light::recalculate (double final_square_size, sf::Vector2f initial_coords)
{
    for (auto component : components)
        delete component;
    components.clear();

    double r_angle = world->dayTime()*2*M_PI;
    double d_angle = world->dayTime()*360;

    sf::Vector2f direction(-cos(r_angle), sin(r_angle));
    if (direction.y < 0)
        return;


    for (int x = 0; x < world->width(); x++)
    {
        for (int y = 0; y < world->height(); y++)
        {
            Tile tile = world->getTile(x, y);

            int pt_index = 0;
            sf::Vector2f pts[5];

            if (direction.x >= 0 || direction.y <= 0)
                pts[pt_index++] =
                    sf::Vector2f(
                            x*final_square_size,
                            (y + 1)*final_square_size);
            if (direction.x >= 0 || direction.y >= 0)
                pts[pt_index++] =
                    sf::Vector2f(
                            x*final_square_size,
                            y*final_square_size);
            if (direction.x <= 0 || direction.y >= 0)
                pts[pt_index++] =
                    sf::Vector2f(
                            (x + 1)*final_square_size,
                            y*final_square_size);
            if (direction.x <= 0 || direction.y <= 0)
                pts[pt_index++] =
                    sf::Vector2f(
                            (x + 1)*final_square_size,
                            (y + 1)*final_square_size);

            pt_index = 3;
            pts[pt_index++] = pts[2] + direction*480000.0f;
            pts[pt_index++] = pts[0] + direction*480000.0f;

            sf::Vector2f c_pt = (pts[0] + pts[2])/2.0f;

            sf::Color shadow_color = sf::Color(0, 0, 0,
                    (1 - tile.transparency)*255);
            sf::ConvexShape *shape = new sf::ConvexShape();
            shape->setFillColor(shadow_color);
            shape->setPointCount(5);
            for (int i = 0; i < 5; i++)
                shape->setPoint(i, pts[i]);
            components.push_back(shape);
        }
    }
}


void Light::draw (
        sf::RenderTarget &target,
        sf::RenderStates states
        ) const
{
    for (sf::Shape *component : components)
        target.draw(*component);
}
