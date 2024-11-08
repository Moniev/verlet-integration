#ifndef ENGINE_HPP
#define ENGINE_HPP
#include "particle.hpp"


class Engine {
    
    public:
        float m_time = 0;
        float m_frame_dt = 0;

        Engine() = default;
        Particle& addParticle(sf::Vector2f position, float radius, sf::Color color);
        std::vector<Particle>& getParticles();
        std::vector<Particle> particles;
        void update();
        void resolveGravity();
        void setSubStepCount(uint32_t steps);
        float getTime() const;
        void setBoundary(sf::Vector2f position, float radius);
        sf::Vector3f getBoundary() const;
        void applyBoundary(float substep_dt);
        void updateObjects(const float dt);
        void checkColliosions();
        void mousePull(sf::Vector2f position);
        void mousePush(sf::Vector2f position);
        void setParticleVelocity(Particle &particle, sf::Vector2f v);
        void setSimulationUpdateRate(uint32_t rate);
        void checkCollisions();

    private:
        sf::Vector2f gravity = {0.0f, 1000.0f};
        float step_dt = 1.0f / 60;
        uint32_t sub_steps = 8;
        sf::Vector2f boundary_center = {420.0f, 420.0f};
        float boundary_radius = 100.0f;
        void applyGravity();
        void updateParticles(const float dt);
};

#endif