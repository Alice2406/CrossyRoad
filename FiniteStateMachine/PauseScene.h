#pragma once
#include "Scene.h"
#include <memory>

class PauseScene : public Scene
{
public:
  
    PauseScene(std::unique_ptr<Scene> backScene);

    void handleInput(sf::RenderWindow& window) override;
    void update(float dt, sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;

    bool resumeGame = false;
  
    std::unique_ptr<Scene> m_backgroundScene;

private:
    sf::Font font;
    sf::Text pauseText;
    sf::Text timerText;
    float timeRemaining;
    float totalTime = 0.0f;
};