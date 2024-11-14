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
        Box() = default;
        Box(float left, float bottom, float width, float height) 
            : left(left)
            , bottom(bottom)
            , width(width)
            , height(height)
            {}

        const float getRight();
        const float getTop();
        const sf::Vector2f getCenter();
        const sf::Vector2f getSize();
        const bool contains(Box &box);
        const bool intersects(Box &box);
        void resolveCollisions();
        const int inBox();
        const std::vector<Particle*>& getPartciles();
        const bool isParticleIn(Particle* particle);
};

#endif