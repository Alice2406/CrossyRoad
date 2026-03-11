#include <SFML/Graphics.hpp>
#include "MenuScene.h"
#include <memory>
#include <optional>

int main() {
  
    sf::RenderWindow window(sf::VideoMode({ 1800, 900 }), "Crossy Road");
    window.setFramerateLimit(60);

    std::unique_ptr<Scene> currentScene = std::make_unique<MenuScene>();
    sf::Clock clock;

    while (window.isOpen()) {
    
        float dt = clock.restart().asSeconds();
       
        currentScene->handleInput(window);
       
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
//        gameScene.update(dt, window);
        currentScene->update(dt, window);

        window.clear(sf::Color::White); 

        currentScene->draw(window);

        window.display();
    }
    return 0;
}