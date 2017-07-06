#include <SFML/Graphics.hpp>
#include <vector>

#include "node.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Graph");

    std::vector<Node*> nodes;

    nodes.push_back(new Node(sf::Vector2f(100, 300)));
    nodes.push_back(new Node(sf::Vector2f(700, 100)));
    nodes.push_back(new Node(sf::Vector2f(700, 500)));
    nodes.push_back(new Node(sf::Vector2f(500, 300)));
    nodes.push_back(new Node(sf::Vector2f(300, 100)));
    nodes.push_back(new Node(sf::Vector2f(300, 500)));

    nodes[0]->point_to(nodes[3]);
    nodes[0]->point_to(nodes[4]);
    nodes[0]->point_to(nodes[5]);

    while (window.isOpen())
    {
        sf::Event evn;
        while (window.pollEvent(evn))
        {
            if (evn.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        for (Node *node : nodes)
            node->draw_edges(window);
        
        for (Node *node : nodes)
            node->draw_node(window);

        window.display();
    }
}
