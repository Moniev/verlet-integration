#include "engine.hpp"

Particle& Engine::addParticle(sf::Vector2f position, float radius, sf::Color color) {
    Particle new_particle = Particle(position, radius, color);
    return particles.emplace_back(new_particle); 
}

std::vector<Particle>& Engine::getParticles(){
    return particles;
}

void Engine::setSimulationUpdateRate(uint32_t rate)
{
    m_frame_dt = 1.0f / static_cast<float>(rate);
}

void Engine::mousePull(sf::Vector2f position) {
    for(auto &particle : particles) {
        sf::Vector2f dir = position - particle.position;
        float dist = sqrt(dir.x * dir.x + dir.y * dir.y);
        particle.accelerate(dir*std::max(0.0f, 10 * (120-dist)));
    }
}

void Engine::mousePush(sf::Vector2f position) {
    for(auto &particle : particles) {
        sf::Vector2f dir = position - particle.position;
        float dist = sqrt(dir.x * dir.x + dir.y * dir.y);
        particle.accelerate(dir*std::max(0.0f, -10 * (120-dist)));
    }
}

void Engine::update() {
    float sub_step_dt = step_dt / sub_steps;
    m_time += m_frame_dt; 
    std::cout << m_time << std::endl;
    for(int i = 0; i < sub_steps; i++){
        applyGravity();
        applyBoundary(sub_step_dt);
        checkCollisions();
        updateParticles(sub_step_dt);
    }
}

void Engine::updateTree(Node *node) {
    if(node->isLeaf()) {
        float sub_step_dt = step_dt / sub_steps;
        m_time += m_frame_dt; 
        std::vector<Particle*> particles = node->box.particles;
        for(int i = 0; i < sub_steps; i++) {
            resolveGravity(particles);
            resolveCollisions(particles);
            resolveBoundaries(particles, sub_step_dt);
            resolveParticlesUpdates(particles, sub_step_dt);
        }
        return;
    }
    for(auto &__children : node->children) {
        updateTree(__children);
    }
}

void Engine::checkCollisions() {
    const float response_coef = 0.75f;
    for(int i = 0; i < particles.size(); i++){
        Particle &particle_1 = particles[i];
        for(int j = i + 1; j < particles.size(); j++){
            Particle &particle_2 = particles[j];
            const sf::Vector2f v = particle_1.position - particle_2.position;
            const float pre_dist = v.x * v.x + v.y * v.y;
            const float min_dist = particle_1.radius + particle_2.radius;
            if(pre_dist < min_dist * min_dist){
                const float dist = sqrt(pre_dist);
                const sf::Vector2f n = v / dist;
                const float mass_ratio_1 = 2 * particle_1.radius / (particle_1.radius + particle_2.radius);
                const float mass_ratio_2 = 2 * particle_2.radius / (particle_1.radius + particle_2.radius); 
                const float delta = 0.5f * response_coef * (dist - min_dist);
                particle_1.position -= n * (mass_ratio_2 * delta); 
                particle_2.position += n * (mass_ratio_1 * delta); 
            }
        }
    }
}

void Engine::resolveCollisions(std::vector<Particle*> particles) {
    const float response_coef = 0.75f;
    for(auto &particle__i : particles) {
        for(auto &particle__j : particles) {
            if(particle__i != particle__j) {
                const sf::Vector2f v = particle__i->position - particle__j->position;
                const float pre_dist = v.x * v.x + v.y * v.y;
                const float min_dist = particle__i->radius + particle__j->radius;
                if(pre_dist < min_dist * min_dist) {
                    const float dist = sqrt(pre_dist);
                    const sf::Vector2f n = v / dist;
                    const float mass_ratio_1 = 2 * particle__i->radius / (particle__i->radius + particle__j->radius);
                    const float mass_ratio_2 = 2 * particle__j->radius / (particle__i->radius + particle__j->radius); 
                    const float delta = 0.5f * response_coef * (dist - min_dist);
                    particle__i->position -= n * (mass_ratio_2 * delta); 
                    particle__j->position += n * (mass_ratio_1 * delta); 
                }
            }
        }
    }
}

//new recursive formula for collisions inside quad trees 
void Engine::applyCollisions(Node *node) {
    std::vector<Node*> children = node->getChildren();
    Box box = node->box;
    std::vector<Particle*> particles = box.particles;
    if(node->isLeaf()) {
        resolveCollisions(particles);
    }
    for(auto &__children : children) {
        applyCollisions(__children);
    }
}

void Engine::applyBoundary(float sub_step_dt) {
    for(auto &particle: particles) {
        const sf::Vector2f r = boundary_center - particle.position;
        const float dist = sqrt(r.x * r.x + r.y * r.y);
        if(dist > boundary_radius - particle.radius) {
            const sf::Vector2f n = r / dist;
            const sf::Vector2f perp = {-n.y, n.x};
            const sf::Vector2f vel = particle.getVelocity(sub_step_dt);
            particle.position = boundary_center - n * (boundary_radius - particle.radius);
            particle.setVelocity(2.0f * (vel.x * perp.x + vel.y * perp.y) * perp - vel, 1.0f);
        }
    }
}

bool Engine::particleBelong(Particle *particle, Node *node) {
    float x = particle->position.x;
    float y = particle->position.y;
    Box box = node->box;

    return x >= box.left
        && x <= box.getRight()
        && y <= box.getTop()
        && y >= box.bottom;
}

void Engine::findNewNode(Particle *particle, Node *node) {
    if(particleBelong(particle, node)) {
        if(node->isLeaf()) {
            node->box.addParticle(particle);
            return;
        }

        for(auto &__children : node->children) {
            findNewNode(particle, __children);
        }
    }
    return;
}

void Engine::updateSpatialLookup(Node *node) {
    std::vector<Particle*> particles = node->box.particles;
    for(auto &particle: particles) {
        if(!particleBelong(particle, node)) {
            findNewNode(particle, root);
            node->box.removeParticle(particle);
        }
    }

    for(auto &__children : node->children) {
        updateSpatialLookup(__children);
    }
}

float Engine::getTime() const {
    return m_time;
}

void Engine::setParticleVelocity(Particle &particle, sf::Vector2f v) {
    particle.setVelocity(v, step_dt);
}

void Engine::setBoundary(sf::Vector2f position, float radius) {
    boundary_center = position;
    boundary_radius = radius;
}

void Engine::setSubStepCount(uint32_t steps) {
    sub_steps = steps;
}

sf::Vector3f Engine::getBoundary() const {
    return {boundary_center.x, boundary_center.y, boundary_radius};
}

Node* Engine::getQuadTree() {
    return root;
}

void Engine::applyGravity() {
    for(auto &particle: particles) {
        particle.accelerate(gravity);
    }
}

void Engine::updateParticles(float dt) {
    for(auto &particle: particles) {
        particle.update(dt);
    }
}

void Engine::resolveBoundaries(std::vector<Particle*> particles, float sub_step_dt) {
    for(auto &particle : particles) {
        const sf::Vector2f r = boundary_center - particle->position;
        const float dist = sqrt(r.x * r.x + r.y * r.y);
        if(dist > boundary_radius - particle->radius) {
            const sf::Vector2f n = r / dist;
            const sf::Vector2f perp = {-n.y, n.x};
            const sf::Vector2f vel = particle->getVelocity(sub_step_dt);
            particle->position = boundary_center - n * (boundary_radius - particle->radius);
            particle->setVelocity(2.0f * (vel.x * perp.x + vel.y * perp.y) * perp - vel, 1.0f);
        }
    }
}

void Engine::resolveGravity(std::vector<Particle*> particles) {
    for(auto &particle : particles) {
        particle->accelerate(gravity);
    }
}

void Engine::resolveParticlesUpdates(std::vector<Particle*> particles, float dt) {
    for(auto &particle : particles) {
        particle->update(dt);
    }
}
