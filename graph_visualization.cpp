#include <SFML/Graphics.hpp>
#include <vector>

// g++ file*.cpp -lsfml-graphics -lsfml-window -lsfml-system  

struct Node {
    sf::CircleShape shape;
    sf::Vector2f position;

    Node(float radius, sf::Vector2f pos) : shape(radius), position(pos) {
        shape.setPosition(position);
        shape.setFillColor(sf::Color::Red);
        shape.setOrigin(radius, radius); // Center the circle
    }
};

struct Edge {
    sf::Vertex line[2];

    Edge(sf::Vector2f start, sf::Vector2f end) {
        line[0] = sf::Vertex(start, sf::Color::White);
        line[1] = sf::Vertex(end, sf::Color::White);
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Graph Visualization");

    // Nodes
    std::vector<Node> nodes = {
        Node(10.f, {200.f, 150.f}),
        Node(10.f, {400.f, 300.f}),
        Node(10.f, {600.f, 150.f})
    };

    // Edges
    std::vector<Edge> edges = {
        Edge({200.f, 150.f}, {400.f, 300.f}),
        Edge({400.f, 300.f}, {600.f, 150.f})
    };

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // Draw edges
        for (const auto& edge : edges) {
            window.draw(edge.line, 2, sf::Lines);
        }

        // Draw nodes
        for (const auto& node : nodes) {
            window.draw(node.shape);
        }

        window.display();
    }

    return 0;
}
