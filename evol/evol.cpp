#include <SFML/Graphics.hpp>

#include <stdio.h>
#include <string>
#include <vector>
#include <random>
#include <set>

#include <fstream>
#include <sstream>

class Terrain
{
public:
    Terrain(std::string name, sf::Color color, float tile_size = 1);

    void draw(sf::Vector2f position, sf::RenderTarget &target);

private:
    std::string name;

    sf::Color color;
    sf::RectangleShape shape;

    float tile_size;
};

Terrain::Terrain(std::string name, sf::Color color, float tile_size)
    : name(name), color(color), tile_size(tile_size)
{
    shape.setFillColor(color);
    shape.setSize(sf::Vector2f(tile_size, tile_size));
}

void Terrain::draw(sf::Vector2f position, sf::RenderTarget &target)
{
    shape.setPosition(position);
    target.draw(shape);
}

class Map
{
public:
    Map(std::string filename, float tile_size = 1, sf::Vector2f position = sf::Vector2f());

    bool loadFromFile(std::string filename);

    void draw(sf::RenderTarget &target);

private:
    float tile_size;
    sf::Vector2f pos_offset;

    sf::Vector2i map_size;

    std::vector<Terrain*> terrain_types;
    Terrain ***data;
};

Map::Map(std::string filename, float tile_size, sf::Vector2f position)
        : tile_size(tile_size), pos_offset(position)
{
    if (!loadFromFile(filename))
        printf("Failed to parse file %s\n", filename.c_str());
}

bool Map::loadFromFile(std::string filename)
{
    std::ifstream file(filename.c_str());

    if(!file.is_open())
    {
        printf("Failed opening file %s\n", filename.c_str());
        return false;
    }

    // Read terrain types
    int terrain_type_cnt;
    if (!(file >> terrain_type_cnt)) return false;

    for (int terrain_id = 0; terrain_id < terrain_type_cnt; terrain_id++)
    {
        std::string name;
        int r, g, b;
        file >> name >> r >> g >> b;
        printf("Loaded terrain '%s', with color (%d, %d, %d)\n", name.c_str(), r, g, b);
        terrain_types.push_back(new Terrain(name, sf::Color(r, g, b)));
    }

    // Read map
    int readmap;
    if (!(file >> map_size.x >> map_size.y >> readmap)) return false;

    data = new Terrain**[map_size.x];
    for (int x = 0; x < map_size.x; x++)
        data[x] = new Terrain*[map_size.y];

    for (int y = 0; y < map_size.y; y++)
    {
        for (int x = 0; x < map_size.x; x++)
        {
            int terrain_index = 0;
            if (readmap && !(file >> terrain_index)) return false;
            data[x][y] = terrain_types[terrain_index];
        }
    }
    return true;
}

void Map::draw(sf::RenderTarget &target)
{
    for (int x = 0; x < map_size.x; x++)
    {
        for (int y = 0; y < map_size.y; y++)
            data[x][y]->draw(pos_offset + sf::Vector2f(x, y) * tile_size, target);
    }
}

enum GeneFlags
{
    ZEROES,
    RANDOM,
};

struct Gene
{
    Gene (int size, double mutation_chance, GeneFlags flags = RANDOM);
    Gene (Gene &gene, double normal_dst_param = 3);

    std::vector<int> gene;
    double mutation_chance;
};

Gene::Gene(int size, double mutation_chance, GeneFlags flags)
    : gene(size), mutation_chance(mutation_chance)
{
    switch (flags)
    {
    case ZEROES:
    {
        for (int i = 0; i < size; i++)
            gene[i] = 0;
        break;
    }
    case RANDOM:
    {
        for (int i = 0; i < size; i++)
            gene[i] = rand();
        break;
    }
    }
}

Gene::Gene(Gene &gene, double normal_dst_param)
{
    std::default_random_engine generator;
    std::uniform_real_distribution<double> uniform_distribution(0.0,1.0);

    mutation_chance = gene.mutation_chance;
    for (int value : gene.gene)
    {
        double result = uniform_distribution(generator);
        if (result < mutation_chance)
            this->gene.push_back(value);
        else
        {
            std::normal_distribution<double> normal_distribution(value, normal_dst_param);
            this->gene.push_back(normal_distribution(generator));
        }
    }
}

enum GENEMAP
{
    HEIGHT = 0,
    LEAVES_SIZE = 1,
    LEAVES_DENSITY = 2,
    LEAVES_DEATH_TH = 3,
    LEAVES_COLOR_R = 4,
    LEAVES_COLOR_G = 5,
    LEAVES_COLOR_B = 6,
    LEAVES_GROWTH_RATE = 7,
    GROWTH_RATE = 8,
    GROWTH_MIN_E = 9,
    GROWTH_MIN_ROOT = 10,
    WOOD_DENSITY = 11,
    ROOT_DEPTH = 12,
    FRUIT_ENERGY = 13,
    FRUIT_MINIMUM_ENERGY = 14,
    FRUIT_FALL_DIST = 15,
    MIN_LEAVES_GROWTH = 16,
};

enum TBType
{
    LEAF,
    WOOD,
    ROOT
};


struct TreeBlock
{
    TreeBlock(sf::Vector2f pos, TBType type = WOOD);

    TBType type;

    sf::Vector2f pos;
};

TreeBlock::TreeBlock(sf::Vector2f pos, TBType type)
    : type(type), pos(pos)
{
}

class Tree
{
public:
    Tree(sf::Vector2f pos, int gene_size = 20, double mutation_rate = .01);
    Tree(sf::Vector2f pos, int initial_e, Tree *tree);

    void cycle(sf::Time dt);

    Gene &getGene();

private:
    int energy;

    Gene gene;
    std::set<TreeBlock*> tree;
};

Tree::Tree(sf::Vector2f pos, int gene_size, double mutation_rate)
    : gene(gene_size, mutation_rate)
{
    energy = 100;
    this->tree.insert(new TreeBlock(pos, WOOD));
}

Tree::Tree(sf::Vector2f pos, int initial_e, Tree *tree)
    : energy(initial_e), gene(tree->getGene())
{
    this->tree.insert(new TreeBlock(pos, WOOD));
}

void Tree::cycle(sf::Time dt)
{
}

Gene &Tree::getGene()
{
    return gene;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");

    window.setView(sf::View(sf::FloatRect(0, 0, 100, 100)));

    Map map("map.map");

    srand(time(0));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        map.draw(window);
        window.display();
    }

    return 0;
}
