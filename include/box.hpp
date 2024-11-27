#ifndef BOX_HPP
#define BOX_HPP

#include "particle.hpp"

class Box{
    public:
        std::vector<Particle*> particles;
        std::vector<Particle*> border_particles;
        float left, bottom, width, height; 
        
        Box(float left, float bottom, float width, float height) 
            : left(left)
            , bottom(bottom)
            , width(width)
            , height(height)
            {}

        const int countParticles();
        const float getRight();
        const float getTop();
        const sf::Vector2f getLeftTop();
        const sf::Vector2f getLeftBottom();
        const sf::Vector2f getCenter();
        const sf::Vector2f getSize();
        const std::vector<Particle*>& getParticles();
        void updateBorder();
        const bool isParticleNearBorder(Particle *particle);
        void considerBorderCollisions(Particle *particle);
        const bool particleBelong(Particle *particle);
        void addParticle(Particle *particle);
        void removeParticle(Particle *particle);
        const bool isAdjacent(Box *other);
};

#endif