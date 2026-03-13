#include <SFML/Graphics.hpp>
#include "MenuScene.h"
#include "SkinScene.h"
#include "GameScene.h"
#include "GameOverScene.h"
#include <memory>

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

        if (MenuScene* menu = dynamic_cast<MenuScene*>(currentScene.get())) {
            if (menu->goToSkin) {
                currentScene = std::make_unique<SkinScene>();
            }
            else if (menu->gameStarted) {
                currentScene = std::make_unique<GameScene>();
            }
        }
        else if (SkinScene* skin = dynamic_cast<SkinScene*>(currentScene.get())) {
            if (skin->backToMenu) {
                currentScene = std::make_unique<MenuScene>();
            }
        }
        else if (GameScene* game = dynamic_cast<GameScene*>(currentScene.get())) {
            if (game->isGameOver) {
                int finalScore = game->getScore();
                currentScene = std::make_unique<GameOverScene>(finalScore);
            }
        }
        else if (GameOverScene* gameOver = dynamic_cast<GameOverScene*>(currentScene.get())) {
            if (gameOver->retryGame) {
                currentScene = std::make_unique<GameScene>();
            }
            else if (gameOver->backToMenu) {
                currentScene = std::make_unique<MenuScene>();
            }
        }
        currentScene->update(dt, window);
        window.clear(sf::Color::White);
        currentScene->draw(window);
        window.display();
    }
    return 0;
}