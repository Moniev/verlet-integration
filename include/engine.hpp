#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "particle.hpp"
#include "node.hpp"

class Engine {
    public:
        const int32_t max_width;
        const int32_t max_height;
        float m_time = 0;
        float m_frame_dt = 0;
        Box *box;
        Node *root;

        Engine() = default;
        Engine(int32_t max_height, int32_t max_width) : 
            max_height(max_height),
            max_width(max_width) {
                this->box = new Box(0, 0, max_width, max_height);
                this->root = new Node(box); 
            }
            
        Particle* addParticle(sf::Vector2f position, float radius, sf::Color color);
        std::vector<Particle*>& getParticles();
        std::vector<Particle*> particles;
        void update();
        void resolveGravity();
        void setSubStepCount(uint32_t steps);
        float getTime() const;
        void setBoundary(sf::Vector2f position, float radius);
        sf::Vector3f getBoundary() const;
        void applyBoundary(float substep_dt);
        void updateObjects(const float dt);
        void mousePull(sf::Vector2f position, Node *node);
        void mousePush(sf::Vector2f position, Node *node);
        void setParticleVelocity(Particle *particle, sf::Vector2f v);
        void setSimulationUpdateRate(uint32_t rate);
        void checkCollisions();
        void resolveCollisions(Box *box);
        void applyCollisions(Node *node);
        void updateSpatialLookup(Node *node);
        int positionToBox(sf::Vector2f position);
        bool particleBelong(Particle *particle, Node *node);
        void findNewNode(Particle *particle, Node *node);
        Node* getQuadTree();
        void resolveGravity(std::vector<Particle*> particles);
        void resolveBoundaries(std::vector<Particle*> particles, float sub_step_dt);
        void resolveParticlesUpdates(std::vector<Particle*> particles, float dt);
        void __resolveCollisions(std::vector<Particle*> particles);
        void updateTree(Node *node);
        void setTreeDepth(int n);
        void splitTree(Node *node);
        void mergeTrees(Node *node);
        void resolveBorderCollisions(Node *node);
        bool windowFriction(Node *node);
        
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