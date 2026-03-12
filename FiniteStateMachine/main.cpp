#include <SFML/Graphics.hpp>
#include "MenuScene.h"
#include "SkinScene.h"
#include <memory>

int main() {
    sf::RenderWindow window(sf::VideoMode({ 1800, 900 }), "Crossy Road ");
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


        if (MenuScene* menu = dynamic_cast<MenuScene*>(currentScene.get())) {
            if (menu->goToSkin) {
                currentScene = std::make_unique<SkinScene>();
            }
        }
        else if (SkinScene* skin = dynamic_cast<SkinScene*>(currentScene.get())) {
            if (skin->backToMenu) {
                currentScene = std::make_unique<MenuScene>();
            }
        }

        currentScene->update(dt);

        window.clear(sf::Color::White);
        currentScene->draw(window);
        window.display();
    }

    return 0;
}