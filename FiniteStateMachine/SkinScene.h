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
    sf::Texture chickenTexture;

    sf::RectangleShape backButtonRect; 
    sf::Sprite backButtonIcon;        

    sf::RectangleShape playButton;
    sf::Text skinNameText;
    sf::Text counterText;

    std::vector<sf::Sprite> skins;
    int currentIndex = 0;
    float targetOffset = 0.f;
    float currentOffset = 0.f;
};