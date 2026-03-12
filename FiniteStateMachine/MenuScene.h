#pragma once
#include "Scene.h"

class MenuScene : public Scene
{
public:
    MenuScene();
    virtual ~MenuScene() = default;

    void handleInput(sf::RenderWindow& window) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

    bool goToSkin = false;
    bool isGameStarted() const { return gameStarted; }

private:
    sf::Font font;
    sf::Text title;
    sf::RectangleShape skinButton;
    sf::Text skinButtonText;

    bool gameStarted = false;
};