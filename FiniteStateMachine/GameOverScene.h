#pragma once
#include "Scene.h"
#include <SFML/Graphics.hpp>

class GameOverScene : public Scene {
public:
    GameOverScene();
    void handleInput(sf::RenderWindow& window) override;
    void update(float dt, sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;

    bool shouldLoadGame = false;
    bool shouldQuit = false;

private:
    sf::Font font;
    sf::Text loadText;
    sf::Text quitText;

    sf::Texture texBg, texTitle;
    sf::Sprite sprBg, sprTitle;
	float totalTime = 0.f;
    bool mouseWasPressed = false;
};