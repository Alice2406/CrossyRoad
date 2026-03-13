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
    bool gameStarted = false;
    bool quitGame = false;

private:
    sf::Font font;
    sf::Text title;

    // Boutons
    sf::RectangleShape playBtn;
    sf::Text playText;

    sf::RectangleShape skinBtn;
    sf::Text skinText;

    sf::RectangleShape quitBtn;
    sf::Text quitText;

    float totalTime = 0.0f;
};


