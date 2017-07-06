#ifndef __NODE_HPP__
#define __NODE_HPP__

#include <SFML/Graphics.hpp>

class Node
{
public:
    Node (sf::Vector2f position) : pos(position) {}

    sf::Vector2f getPos();

    void point_to(Node* node);

    void draw_edges(sf::RenderWindow &window);
    void draw_node(sf::RenderWindow &window);

private:
    sf::Vector2f pos;
    std::vector<Node*> pointing;
};

#endif
