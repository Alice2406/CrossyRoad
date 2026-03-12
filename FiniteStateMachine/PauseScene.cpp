#include "PauseScene.h"

void PauseScene::update(float dt) {
    remainingTime -= dt;

    if (remainingTime <= 0.f) {
        resumeGame = true; 
    }
    else {
      
        timerText.setString(std::to_string((int)std::ceil(remainingTime)));
    }
}