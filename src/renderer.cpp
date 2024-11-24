#include "renderer.hpp"


void Renderer::render(Engine &engine, bool debug) {
    sf::CircleShape circle{1.0f};
    circle.setPointCount(32);
    const sf::Vector3f boundary = engine.getBoundary();
    sf::CircleShape boundary_background{boundary.z};
    boundary_background.setOrigin(boundary.z, boundary.z);
    boundary_background.setFillColor(sf::Color::Black);
    boundary_background.setPosition(boundary.x, boundary.y);
    boundary_background.setPointCount(1280);
    window.draw(boundary_background);

    if(debug) {
        renderQuadTree(engine.root);
    }

    const auto particles = engine.getParticles();
    for(const auto &particle : particles) {
        circle.setPosition(particle->position);
        circle.setScale(particle->radius, particle->radius);
        circle.setFillColor(particle->color);
        window.draw(circle);
    }
}

void Renderer::renderQuadTree(Node *node) {
    Box *box = node->box;
    const sf::Vector2f position = box->getLeftBottom();
    const sf::Vector2f size = box->getSize();
    sf::RectangleShape square(size);

    square.setPosition(position);
    square.setOutlineColor(sf::Color::Green);
    square.setOutlineThickness(2);
    square.setFillColor(sf::Color::Transparent);
    window.draw(square);

    std::vector<Node*> children = node->getChildren(); 
    for(auto &__children : children) {
        renderQuadTree(__children);
    }
}

void Renderer::renderBoundaries(Engine &engine) {
    const sf::Vector3f boundary = engine.getBoundary();
    sf::CircleShape boundary_background{boundary.z};
    boundary_background.setOrigin(boundary.z, boundary.z);
    boundary_background.setFillColor(sf::Color::Black);
    boundary_background.setPosition(boundary.x, boundary.y);
    boundary_background.setPointCount(1280);
    window.draw(boundary_background);
}