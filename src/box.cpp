#include "box.hpp"

const float Box::getRight() {
    std::cout << "getRight" << std::endl;
    return left + width;
}   

const float Box::getTop() {
    std::cout << "getTop" << std::endl;
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

const bool Box::contains(Box &box) {
    return left <= box.left 
    && box.getRight() <= getRight() 
    && getTop() <= box.getTop()
    && bottom <= box.bottom;
}

const bool Box::intersects(Box &box) {
    return !(left >= box.getRight() 
    || Box::getRight() <= box.left 
    || bottom >= box.getTop()
    || Box::getTop() <= box.bottom);
}

const bool Box::isParticleIn(Particle *particle) {
    for(const auto &particle__i : particles) {
        if(particle__i == particle) {
            return true;
        }
    }
    return false;
}

void Box::addParticle(Particle *particle) {
    std::cout << "addParticle" << std::endl;
    particles.emplace_back(particle);
}

void Box::removeParticle(Particle *particle) {
    particles.erase(find(particles.begin(), particles.end(), particle));
}