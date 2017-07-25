#include <SFML/Graphics.hpp>

#include <queue>
#include <set>
#include <random>

#include <stdio.h>

#include "map.hpp"

#define W 80
#define H 60

#define PART 1500

template<typename from, typename to>
sf::Vector2<to> conv(sf::Vector2<from> orig)
{
    return sf::Vector2<to>(orig.x, orig.y);
}

bool valid_path (Map<int> &map, sf::Vector2u from, sf::Vector2u to)
{
    sf::Vector2i from_i(from.x, from.y);
    sf::Vector2i to_i(to.x, to.y);

    bool ok = true;

    if (to_i - from_i == sf::Vector2i(1, 1))
        ok &=
            !map.get(from + sf::Vector2u(1, 0)) &&
            !map.get(from + sf::Vector2u(0, 1));

    if (to_i - from_i == sf::Vector2i(1, -1))
        ok &=
            !map.get(from + sf::Vector2u(1, 0)) &&
            !map.get(from - sf::Vector2u(0, 1));

    if (to_i - from_i == sf::Vector2i(-1, 1))
        ok &=
            !map.get(from - sf::Vector2u(1, 0)) &&
            !map.get(from + sf::Vector2u(0, 1));

    if (to_i - from_i == sf::Vector2i(-1, -1))
        ok &=
            !map.get(from - sf::Vector2u(1, 0)) &&
            !map.get(from - sf::Vector2u(0, 1));
    return !map.get(to) && ok;
}

sf::Vector2f flow_vel (Map<sf::Vector2i> &flow, sf::Vector2f position)
{
    sf::Vector2i dir =
        flow.get(conv<float, uint>(position / 10.0f));
    sf::Vector2f dirf = conv<int, float>(dir);
    float len = sqrt(dirf.x*dirf.x + dirf.y*dirf.y);
    if (len >= .5)
        dirf /= len;
    return dirf*(50.0f + rand()%10 - 5);
}

bool in_map (sf::Vector2i coords)
{
    return coords.x >= 0 && coords.y >= 0 && coords.x < W && coords.y < H;
}

void calculate_flow (Map<int> &map, Map<sf::Vector2i> &flow, sf::Vector2u dst)
{
    Map<bool> vis(map.getSize());
    std::queue<sf::Vector2u> to_explore;

    for (uint x = 0; x < W; x++)
    {
        for (uint y = 0; y < H; y++)
        {
            vis.set(sf::Vector2u(x, y), false);
            flow.set(sf::Vector2u(x, y), sf::Vector2i(0, 0));
        }
    }

    if (map.get(dst))
        return;
    to_explore.push(dst);
    vis.set(dst, true);

    sf::Vector2i sides[] = {
        sf::Vector2i(1, 0),
        sf::Vector2i(0, 1),
        sf::Vector2i(-1, 0),
        sf::Vector2i(0, -1),
        sf::Vector2i(1, 1),
        sf::Vector2i(-1, 1),
        sf::Vector2i(1, -1),
        sf::Vector2i(-1, -1),
    };

    while (!to_explore.empty())
    {
        sf::Vector2u current = to_explore.front();
        to_explore.pop();

        for (sf::Vector2i side : sides)
        {
            sf::Vector2i next_i = conv<uint, int>(current) + side;
            sf::Vector2u next = conv<int, uint>(next_i);
            if (in_map(next_i) &&
                    !vis.get(next) &&
                    valid_path(map, current, next))
            {
                flow.set(next, -side);
                to_explore.push(next);
                vis.set(next, true);
            }
        }
    }
}

sf::Vector2u mouse_coords;

sf::Vertex particles[PART];

int main ()
{
    sf::RenderWindow window(sf::VideoMode(10*W, 10*H), "teste");

    srand(time(0));

    Map<int> map(sf::Vector2u(W, H));
    Map<sf::Vector2i> flow(sf::Vector2u(W, H));

    for (uint x = 0; x < W; x++)
        for (uint y = 0; y < H; y++)
            map.set(sf::Vector2u(x, y), rand()%6?0:1);

    for (uint i = 0; i < PART; i++)
    {
        particles[i].color = sf::Color(rand()%255, rand()%255, rand()%255);
        do
            particles[i].position = sf::Vector2f(rand()%800, rand()%600);
        while (map.get(sf::Vector2u(
                        particles[i].position.x / 10,
                        particles[i].position.y / 10)));
    }

    sf::RectangleShape wall;
    wall.setSize(sf::Vector2f(10, 10));
    wall.setFillColor(sf::Color::White);

    sf::RectangleShape floor;
    floor.setSize(sf::Vector2f(10, 10));
    floor.setFillColor(sf::Color::Black);
    floor.setOutlineColor(sf::Color(100, 100, 100));
    floor.setOutlineThickness(1);

    printf("Now accepting input!\n");
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseMoved:
                {
                    sf::Vector2i new_pos(event.mouseMove.x, event.mouseMove.y);
                    sf::Vector2i coords = new_pos / 10;

                    sf::Vector2u coords_u = sf::Vector2u(coords.x, coords.y);
                    mouse_coords = coords_u;
                    break;
                }
            default:
                break;
            }
        }

        float dt = clock.restart().asSeconds();

        calculate_flow(map, flow, mouse_coords);

        for (uint i = 0; i < PART; i++)
        {
            particles[i].position += flow_vel(flow, particles[i].position)*dt;
            if (conv<float, uint>
                    (particles[i].position / 10.0f) == mouse_coords)
            {

                do
                    particles[i].position =
                        sf::Vector2f(rand()%800, rand()%600);
                while (map.get(sf::Vector2u(
                                particles[i].position.x / 10,
                                particles[i].position.y / 10)));
            }
        }

        window.clear();

        for (uint x = 0; x < W; x++)
        {
            for (uint y = 0; y < H; y++)
            {
                sf::Vertex line[2];

                line[0].position =
                    sf::Vector2f(x*10, y*10) +
                    sf::Vector2f(5, 5);

                line[1].position =
                    line[0].position +
                    sf::Vector2f(flow.get(sf::Vector2u(x, y)).x,
                            flow.get(sf::Vector2u(x, y)).y) * 3.5f;

                line[0].color = line[1].color = sf::Color(100, 100, 100);

                if (!map.get(sf::Vector2u(x, y)))
                {
                    floor.setPosition(x*10, y*10);
                    window.draw(floor);
                }
                else
                {
                    wall.setPosition(x*10, y*10);
                    window.draw(wall);
                }

                window.draw(line, 2, sf::Lines);
                window.draw(line, 1, sf::Points);
                window.draw(particles, PART, sf::Points);
            }
        }

        window.display();
    }
}
