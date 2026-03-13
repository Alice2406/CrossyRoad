#pragma once
#include "Scene.h"

class PauseScene : public Scene {
public:
    PauseScene();
    void handleInput(sf::RenderWindow& window) override;
    void update(float dt, sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;

    bool resumeGame = false; 

private:
    sf::Font font;
    sf::Text timerText;
    float remainingTime = 3.0f; 
};