#include <SFML/Graphics.hpp>

#include <vector>
#include <math.h>

class Spring;

class Node
{
    friend Spring;
public:
    Node(sf::Vector2f pos, sf::Vector2f vel = sf::Vector2f(0, 0), float mass = 10, float radius = .1);

    void update(sf::Time dt);
    void applyForce(sf::Vector2f force);

    void setPosition(sf::Vector2f pos);

    void draw(sf::RenderWindow &window, sf::Color color = sf::Color::Cyan);

private:
    sf::CircleShape shape;

    sf::Vector2f pos, vel, facc;
    float mass;
};

Node::Node(sf::Vector2f pos, sf::Vector2f vel, float mass, float radius)
    :shape(radius), pos(pos), vel(vel), mass(mass)
{
    shape.setOrigin(radius, radius);
}

void Node::update(sf::Time dt)
{
    sf::Vector2f acc = facc/mass;
    facc = sf::Vector2f(0, 0);
    vel += acc * dt.asSeconds();
    vel *= .999f;
    pos += vel * dt.asSeconds();
    if (pos.x > 7.9)
        pos.x = 7.9;
    if (pos.x < .1)
        pos.x = .1;
    if (pos.y > 5.9)
        pos.y = 5.9;
    if (pos.y < .1)
        pos.y = .1;
}

void Node::applyForce(sf::Vector2f force)
{
    facc += force;
}

void Node::setPosition(sf::Vector2f pos)
{
    this->pos = pos;
}

void Node::draw(sf::RenderWindow &window, sf::Color color)
{
    shape.setFillColor(color);
    shape.setPosition(pos);
    window.draw(shape);
}

class Spring
{
public:
    Spring(Node *a, Node *b, float k, float z);

    void apply();

    void draw(sf::RenderWindow &window);

private:
    Node *a, *b;
    float k, z;
};

Spring::Spring(Node *a, Node *b, float k, float z)
    :a(a), b(b), k(k), z(z)
{
}

void Spring::apply()
{
    sf::Vector2f a_to_b = b->pos - a->pos;
    float dist = sqrt(a_to_b.x*a_to_b.x + a_to_b.y*a_to_b.y);
    sf::Vector2f a_to_b_norm = a_to_b / dist;

    a->applyForce(a_to_b_norm * (dist - z) * k);
    b->applyForce(a_to_b_norm * (z - dist) * k);
}

void Spring::draw(sf::RenderWindow &window)
{
    sf::Vertex line[] =
    {
        sf::Vertex(a->pos),
        sf::Vertex(b->pos)
    };
    window.draw(line, 2, sf::Lines);
}
int selected_node = 0;
std::vector<Node *> nodes;
std::vector<Spring *> springs;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    bool paused = false;

    float controller_force = 300;

    window.setView(sf::View(sf::FloatRect(0, 0, 8, 6)));

    nodes.push_back(new Node(sf::Vector2f(4, 3)));
    nodes.push_back(new Node(sf::Vector2f(6, 3)));
    nodes.push_back(new Node(sf::Vector2f(6, 4)));
    nodes.push_back(new Node(sf::Vector2f(6, 2)));
    nodes.push_back(new Node(sf::Vector2f(6, 1)));
    springs.push_back(new Spring(nodes[0], nodes[1], 10000, .5));
    springs.push_back(new Spring(nodes[1], nodes[2], 10000, .5));
    springs.push_back(new Spring(nodes[0], nodes[2], 10000, .5));
    springs.push_back(new Spring(nodes[3], nodes[0], 10000, .5));
    springs.push_back(new Spring(nodes[3], nodes[1], 10000, .5));
    springs.push_back(new Spring(nodes[4], nodes[0], 10000, .5));
    springs.push_back(new Spring(nodes[4], nodes[3], 10000, .5));

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyReleased)
            {
                switch(event.key.code)
                {
                case sf::Keyboard::Space:
                    paused = !paused;
                    break;
                case sf::Keyboard::Q:
                    selected_node++;
                    selected_node %= nodes.size();
                    break;
                }
            }
        }

        sf::Time dt = clock.restart();

        if (!paused)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                nodes[selected_node]->applyForce(sf::Vector2f(0, -controller_force));
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                nodes[selected_node]->applyForce(sf::Vector2f(0, controller_force));
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                nodes[selected_node]->applyForce(sf::Vector2f(controller_force, 0));
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                nodes[selected_node]->applyForce(sf::Vector2f(-controller_force, 0));


            for (Node *node : nodes)
                node->applyForce(sf::Vector2f(0, 98));
            for (Spring *spring : springs)
                spring->apply();
            for (Node *node : nodes)
                node->update(dt);
        }

        window.clear();
        for (Spring *spring : springs)
            spring->draw(window);
        for (Node *node : nodes)
            node->draw(window, node == nodes[selected_node]? sf::Color::Red : sf::Color::Cyan);
        window.display();
    }

    return 0;
}
