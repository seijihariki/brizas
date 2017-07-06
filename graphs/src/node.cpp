#include "node.hpp"

sf::Vector2f Node::getPos()
{
    return pos;
}

void Node::point_to(Node *node)
{
    pointing.push_back(node);
}

void Node::draw_edges(sf::RenderWindow &window)
{
    sf::Vertex line[] = 
    {
        sf::Vertex(pos),
        sf::Vertex(pos),
    };

    for (Node *node : pointing)
    {
        line[1] = node->getPos();

        window.draw(line, 2, sf::Lines);
    }
}

void Node::draw_node(sf::RenderWindow &window)
{
    sf::CircleShape shape(10);
    shape.setFillColor(sf::Color(127, 0, 127));
    shape.setOrigin(10, 10);
    shape.setPosition(pos);

    window.draw(shape);
}
