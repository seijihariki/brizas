#include "world.hpp"

// Constructors

World::World (
        const uint w,
        const uint h,
        sf::Time day_duration
        ) :

    w(w), h(h),
    day_duration(day_duration)
{
    map = new Tile*[w];
    for (uint i = 0; i < w; i++)
        map[i] = new Tile[h];
}

// Destructor

World::~World ()
{
    for (uint i = 0; i < w; i++)
    {
        delete map[i];
        map[i] = nullptr;
    }

    delete map;
    map = nullptr;
}

// Getters

uint World::width () const
{
    return w;
}

uint World::height () const
{
    return h;
}

sf::Time World::elapsedTime () const
{
    return clock.getElapsedTime();
}

uint World::day () const
{
    double elapsed_sec = elapsedTime().asSeconds();
    double day_dur_sec = day_duration.asSeconds();
    return (uint) (elapsed_sec / day_dur_sec + 1);
}

double World::dayTime () const
{
    double elapsed_sec = elapsedTime().asSeconds();
    double day_dur_sec = day_duration.asSeconds();
    return (elapsed_sec / day_dur_sec + 1) - day();
}

// Setters

// Other

void World::generate (MapGenerator *generator)
{
    if (!generator)
        return;

    generator->generate(map, w, h);
}

void World::update ()
{
    sf::Time delta = this->delta.restart();

    uint day = this->day();
    double day_frac = dayTime();
}

void World::draw(
        sf::RenderTarget &target,
        sf::RenderStates states
        ) const
{
    // Calculating necessay info for centralized drawing
    sf::Vector2f target_size = target.getView().getSize();
    sf::Vector2f view_top_left =
        target.getView().getCenter() - target_size / 2.f;
    
    sf::Vector2f expected_size = sf::Vector2f(
            target_size.x / w,
            target_size.y / h);
    
    double final_square_size =
        expected_size.x < expected_size.y ? expected_size.x : expected_size.y;

    sf::Vector2f initial_coords = sf::Vector2f(
            (target_size.x - final_square_size*w) / 2 + view_top_left.x,
            (target_size.y - final_square_size*h) / 2 + view_top_left.y);

    // Now the actual drawing takes place
    sf::RectangleShape tile;
    tile.setSize(sf::Vector2f(final_square_size, final_square_size));
    tile.setOutlineThickness(final_square_size/10);

    for (uint x = 0; x < w; x++)
    {
        for (uint y = 0; y < h; y++)
        {
            tile.setPosition(initial_coords
                    + sf::Vector2f(x*final_square_size, y*final_square_size));
            tile.setFillColor(map[x][y].fill_color);
            tile.setOutlineColor(map[x][y].border_color);
            target.draw(tile);
        }
    }
}
