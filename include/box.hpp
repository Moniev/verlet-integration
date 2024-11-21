#ifndef BOX_HPP
#define BOX_HPP


#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <memory>
#include <type_traits>
#include <iostream>
#include "particle.hpp"

class Box{
    public:
        std::vector<Particle*> particles;
        float left, bottom, width, height; 
        
        Box(float left, float bottom, float width, float height) 
            : left(left)
            , bottom(bottom)
            , width(width)
            , height(height)
            {}

        const float getRight();
        const float getTop();
        const sf::Vector2f getLeftTop();
        const sf::Vector2f getLeftBottom();
        const sf::Vector2f getCenter();
        const sf::Vector2f getSize();
        const bool contains(Box &box);
        const bool intersects(Box &box);
        const int inBox();
        const std::vector<Particle*>& getParticles();
        const bool isParticleIn(Particle *particle);
        const bool particleBelong(Particle *particle);
        void addParticle(Particle *particle);
        void removeParticle(Particle *particle);
};

#endif