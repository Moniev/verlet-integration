#include "box.hpp"

const float Box::getRight()
{
    return left + width;
}   

const float Box::getTop()
{
    return bottom + height;
}

const sf::Vector2f Box::getCenter()
{
    return sf::Vector2f{left + width / 2, bottom + height/2};
}


const sf::Vector2f Box::getSize()
{
    return sf::Vector2f{width, height};
}

const bool Box::contains(Box &box)
{
    return left <= box.left 
    && box.getRight() <= getRight() 
    && getTop() <= box.getTop()
    && bottom <= box.bottom;
}

const bool Box::intersects(Box &box)
{
    return !(left >= box.getRight() 
    || getRight() <= box.left 
    || bottom >= box.getTop()
    || getTop() <= box.bottom);
}

void Box::resolveCollisions() {
    const float response_coef = 0.75f;
    for(int i = 0; i < particles.size(); i++) {
        Particle *particle_i = particles[i];
        for(int j = 0; j < particles.size(); j++) {
            Particle *particle_j = particles[j];
            const sf::Vector2f v = particle_i->position - particle_j->position;
            const float pre_dist = v.x * v.x + v.y * v.y;
            const float min_dist = particle_i->radius + particle_j->radius;
            if(pre_dist < min_dist * min_dist) {
                const float dist = sqrt(pre_dist);
                const sf::Vector2f n = v / dist;
                const float mass_ratio_1 = particle_i->radius / (particle_i->radius + particle_j->radius);
                const float mass_ratio_2 = particle_j->radius / (particle_i->radius + particle_j->radius); 
                const float delta = 0.5f * response_coef * (dist - min_dist);
                particle_i->position -= n * (mass_ratio_2 * delta); 
                particle_j->position += n * (mass_ratio_1 * delta); 
            }
        }
    }
}

const bool Box::isParticleIn(Particle *particle) {
    for(auto &particle_i = particles.front(); particle_i != particles.back(); particle_i++) {
        if(particle_i == particle) {
            return true;
        }
    }
    return false;
}