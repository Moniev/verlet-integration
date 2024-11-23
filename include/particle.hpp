#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>
#include <memory>
#include <type_traits>
#include <iostream>

class Particle {
    public:
        sf::Vector2f position;
        sf::Vector2f last_position;
        sf::Vector2f acceleration;
        sf::Color color;
        float radius;
        float mass;

        Particle() = default;
        Particle(sf::Vector2f __position, float __radius, sf::Color __color)
            : acceleration(2.f, 2.f)
            , position(__position)
            , last_position(__position)
            , radius(__radius)
            , color(__color)
        {}

        void accelerate(sf::Vector2f a);
        void addVelocty(sf::Vector2f v, float dt);
        void setVelocity(sf::Vector2f v, float dt);
        sf::Vector2f getPosition();
        sf::Vector2f getVelocity(float dt);
        
        void update(float dt);
};

#endif