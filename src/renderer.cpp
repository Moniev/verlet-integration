#include "renderer.hpp"


void Renderer::render(Engine &engine) const
{
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