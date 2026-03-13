#pragma once
#include "Scene.h"
#include <memory>

class GameOverScene : public Scene {
public:
    GameOverScene(int finalScore);
    void handleInput(sf::RenderWindow& window) override;
    void update(float dt, sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;

    bool retryGame = false;
    bool backToMenu = false;

private:
    sf::Font font;
    std::unique_ptr<sf::Text> titleText;
    std::unique_ptr<sf::Text> scoreText;
    std::unique_ptr<sf::Text> instructionText;
};