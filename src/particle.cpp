#include "particle.hpp"

void Particle::accelerate(sf::Vector2f a) {
    acceleration += a;
}

void Particle::setVelocity(sf::Vector2f v, float dt) {
    last_position = position - (v * dt);
}

void Particle::addVelocty(sf::Vector2f v, float dt) {
    last_position -= v * dt;
}

sf::Vector2f Particle::getVelocity(float dt) {
    return (position - last_position);
} 

void Particle::update(float dt) {
    sf::Vector2f displacement = position - last_position;
    last_position = position;
    position = position + displacement + acceleration * (dt * dt);
    acceleration = {};
}

