#include "renderer.hpp"


void Renderer::render(Engine &engine, bool debug) {
    //boundaries
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
        Node *root = engine.getQuadTree();
        Renderer::renderQuadTree(root);

    }

    const auto particles = engine.getParticles();
    for(const auto &particle : particles)
    {
        //draw particles
        circle.setPosition(particle.position);
        circle.setScale(particle.radius, particle.radius);
        circle.setFillColor(particle.color);
        window.draw(circle);
    }
}

void Renderer::renderQuadTree(Node *node) {
    for(const auto &__children : node->getChildren()) {
        Box __box = node->box;
        sf::Vector2f position = __box.getCenter();
        sf::Vector2f size = __box.getSize();
        sf::RectangleShape square;
        square.setSize(size);
        square.setPosition(position);
        square.setOutlineColor(sf::Color::White);
        square.setFillColor(sf::Color::Black);
        window.draw(square);
        Renderer::renderQuadTree(__children);
    }
}

void Renderer::renderParticles(Node *node) {
    Box box = node->box;
    for(const auto &particle : box.particles) {
        
    }
}