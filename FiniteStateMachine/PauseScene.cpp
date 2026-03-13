#include "PauseScene.h"

void PauseScene::update(float dt, sf::RenderWindow& window) {
    remainingTime -= dt;

    if (remainingTime <= 0.f) {
        resumeGame = true; 
    }
    else {
      
        timerText.setString(std::to_string((int)std::ceil(remainingTime)));
    }
}