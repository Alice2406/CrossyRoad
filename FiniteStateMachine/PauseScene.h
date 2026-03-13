//#pragma once
//#include "Scene.h"
//
//class PauseScene : public Scene
//{
//public:
//    PauseScene();
//    void handleInput(sf::RenderWindow& window) override;
//    void update(float dt, sf::RenderWindow& window) override;
//    void draw(sf::RenderWindow& window) override;
//
//    bool resumeGame = false;
//
//private:
//    sf::Font font;
//    sf::Text pauseText;
//    sf::Text timerText;
//    float timeRemaining;
//    float totalTime = 0.0f; // Pour l'animation d'horreur
//};

#pragma once
#include "Scene.h"
#include <memory>

class PauseScene : public Scene
{
public:
    // On reçoit la scène actuelle pour la stocker
    PauseScene(std::unique_ptr<Scene> backScene);

    void handleInput(sf::RenderWindow& window) override;
    void update(float dt, sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;

    bool resumeGame = false;
    // On la met en public pour que le main puisse la récupérer après
    std::unique_ptr<Scene> m_backgroundScene;

private:
    sf::Font font;
    sf::Text pauseText;
    sf::Text timerText;
    float timeRemaining;
    float totalTime = 0.0f;
};