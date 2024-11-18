#include "engine.hpp"
#include "renderer.hpp"


int main()
{
    constexpr int32_t window_width = 1000;
    constexpr int32_t window_height = 1000;
    
    sf::ContextSettings settings;
    settings.antialiasingLevel = 1;
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Verlet integration", sf::Style::Default, settings);
    
    constexpr int32_t frame_rate = 60; 
    constexpr int32_t max_particles = 1000;
    float spawn_delay = 0.05f;
    const float max_angle = 1.0f;
    static constexpr float PI = 3.1415936f;
    sf::Vector2f spawn_position{420.0f, 100.0f};
    sf::Clock clock;

    window.setFramerateLimit(frame_rate);
    Renderer renderer{window};
    
    
    Engine engine;
    engine.setBoundary({window_width / 2, window_height / 2}, (window_width - 20.0f) / 2);
    engine.setSubStepCount(8);
    engine.setSimulationUpdateRate(frame_rate);
    


    while(window.isOpen()) {
        sf::Event event{};
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            float ratio = 840.0f / window.getSize().x;
            sf::Vector2f position = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)) * ratio;
            engine.mousePull(position);
        }   


        if(sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            float ratio = 840.0f / window.getSize().x;
            sf::Vector2f position = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)) * ratio;
            engine.mousePush(position);
        }

        if(engine.getParticles().size() < max_particles && clock.getElapsedTime().asSeconds() >= spawn_delay) {
            clock.restart();
            const float time = engine.getTime();
            const float angle = max_angle * sin(time) + PI * 0.5f;
            auto &particle = engine.addParticle(spawn_position, 10.f, sf::Color::Magenta);
            engine.setParticleVelocity(particle, 12.0f * sf::Vector2f{cos(angle), sin(angle)});
        }

        engine.update();
        window.clear(sf::Color::White);
        renderer.render(engine, false);
        window.display();
    }  
    return 0;
}