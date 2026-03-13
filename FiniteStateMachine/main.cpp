#include <SFML/Graphics.hpp>
#include "MenuScene.h"
#include "SkinScene.h"
#include "GameScene.h"
#include "PauseScene.h"

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

        currentScene->handleInput(window);
        if (MenuScene* menu = dynamic_cast<MenuScene*>(currentScene.get())) {
            if (menu->quitGame) {
                window.close();
            }
            else if (menu->goToSkin) {
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

        // ... après les autres checks de dynamic_cast ...
      // ... (tes autres dynamic_cast pour Menu et Skin) ...

        else if (GameScene* game = dynamic_cast<GameScene*>(currentScene.get())) {
            if (game->requestPause) {
                // On donne la GameScene à la PauseScene
                currentScene = std::make_unique<PauseScene>(std::move(currentScene));
            }
        }
        else if (PauseScene* pause = dynamic_cast<PauseScene*>(currentScene.get())) {
            if (pause->resumeGame) {
                // On récupère la GameScene
                std::unique_ptr<Scene> gameBack = std::move(pause->m_backgroundScene);

                // IMPORTANT : On reset le bouton pause pour ne pas reboucler !
                if (GameScene* g = dynamic_cast<GameScene*>(gameBack.get())) {
                    g->requestPause = false;
                }

                currentScene = std::move(gameBack);
            }
        }

        currentScene->update(dt, window);

        window.clear(sf::Color::Black);
        currentScene->draw(window);
        window.display();
    }

    return 0;
}





