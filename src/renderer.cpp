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

    sf::RectangleShape sth({100, 100});
    if(debug) {
        renderQuadTree(engine.root);
    }

    const auto particles = engine.getParticles();
    for(const auto &particle : particles) {
        circle.setPosition(particle.position);
        circle.setScale(particle.radius, particle.radius);
        circle.setFillColor(particle.color);
        window.draw(circle);
    }
}

void Renderer::renderQuadTree(Node *node) {
    Box *__box = node->box;
    sf::Vector2f position = __box->getLeftBottom();
    sf::Vector2f size = __box->getSize();
    sf::RectangleShape square(size);
    square.setPosition(position);
    square.setOutlineColor(sf::Color::Green);
    square.setOutlineThickness(2);
    square.setFillColor(sf::Color::Transparent);
    window.draw(square);

    for(const auto &__children : node->getChildren()) {
        renderQuadTree(__children);
    }
}

void Renderer::renderParticles(Node *node) {
    sf::CircleShape circle{1.0f};
    circle.setPointCount(32);
    if(node->isLeaf()) {
        for(const auto &particle : node->box->getParticles()) {
            circle.setPosition(particle->position);
            circle.setScale(particle->radius, particle->radius);
            circle.setFillColor(particle->color);
            window.draw(circle);
        }
        return;
    }

    for(auto &__children : node->children) {
        renderParticles(__children);
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