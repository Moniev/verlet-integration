#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "engine.hpp"
#include "particle.hpp"


class Renderer {
    public:
        sf::RenderWindow& window;
        std::vector<Particle> particles;

        Renderer() = default;
        Renderer(sf::RenderWindow& __window)
            : window(__window)
        {}
    
        void render(Engine &engine, bool debug);
        void renderSpace();
        void renderParticles(Node *node);
        void renderQuadTree(Node *node);
        void renderBoundaries(Engine &engine);
};

#endif