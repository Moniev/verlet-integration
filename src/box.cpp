#include "box.hpp"


const int Box::countParticles() {
    return particles.size();
}

const float Box::getRight() {
    return left + width;
}   

const float Box::getTop() {
    return bottom + height;
}

const sf::Vector2f Box::getLeftBottom() {
    return {left, bottom};
}

const sf::Vector2f Box::getLeftTop() {
    return {left, getTop()};
}

const std::vector<Particle*>& Box::getParticles() {
    return particles;
}

const sf::Vector2f Box::getCenter() {
    return sf::Vector2f{left + width / 2, bottom + height/2};
}

const sf::Vector2f Box::getSize() {
    return sf::Vector2f{width, height};
}

const bool Box::isAdjacent(Box *other) {
    const bool is_vertically_adjacent = (getTop() == other->bottom || bottom == other->getTop());
    const bool is_horizontally_adjacent = (getRight() == other->left || left == other->getRight());
    return is_horizontally_adjacent || is_vertically_adjacent;
}

void Box::considerBorderCollisions(Particle *particle) {
    border_particles.push_back(particle);
}

void Box::updateBorder() {
    for(auto &particle : border_particles) {
        if(!isParticleNearBorder(particle)) {
            border_particles.erase(find(border_particles.begin(), border_particles.end(), particle));
        }
    }
}

const bool Box::isParticleNearBorder(Particle *particle) {
    sf::Vector2f position = particle->position;
    float radius = particle->radius;
    return fabs(position.x - left) + radius < 5.0f 
        || fabs(position.x - getRight()) + radius < 5.0f 
        || fabs(position.y - bottom) + radius < 5.0f 
        || fabs(position.y - getTop()) + radius < 5.0f;
}

void Box::addParticle(Particle *particle) {
    particles.push_back(particle);
}

void Box::removeParticle(Particle *particle) {
    particles.erase(find(particles.begin(), particles.end(), particle));
}