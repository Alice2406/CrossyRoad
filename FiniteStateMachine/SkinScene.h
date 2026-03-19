#pragma once
#include "Scene.h"
#include <vector>

class SkinScene : public Scene {
public:
    SkinScene();
    void handleInput(sf::RenderWindow& window) override;
    void update(float dt, sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;

    bool backToMenu = false;

private:
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::RectangleShape backButtonRect;
    sf::Text backText;
};