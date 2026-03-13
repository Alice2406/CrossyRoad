#pragma once
#include "Scene.h"

class MenuScene : public Scene
{
public:
    MenuScene();
    virtual ~MenuScene() = default;

    void handleInput(sf::RenderWindow& window) override;
    void update(float dt, sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;

    bool goToSkin = false;
    bool isGameStarted() const { return gameStarted; }
    bool gameStarted = false;

private:
    sf::Font font;
    sf::Text title;
    sf::RectangleShape skinButton;
    sf::Text skinButtonText;

};