#include "PauseScene.h"
#include <cmath>

PauseScene::PauseScene(std::unique_ptr<Scene> backScene)
    : m_backgroundScene(std::move(backScene)), 
    timeRemaining(3.9f),
    pauseText(font),
    timerText(font)
{
    font.openFromFile("Assets/Arial.ttf");

    pauseText.setString("TU Y ES PRESQUE...");
    pauseText.setCharacterSize(80);
    pauseText.setFillColor(sf::Color(180, 0, 0, 220));

    timerText.setCharacterSize(40);
    timerText.setFillColor(sf::Color::White);
}

void PauseScene::handleInput(sf::RenderWindow& window) {}

void PauseScene::update(float dt, sf::RenderWindow& window) {
    timeRemaining -= dt;
    totalTime += dt;

    pauseText.setPosition({ 900.f - pauseText.getGlobalBounds().size.x / 2.f, 400.f });

    int secs = static_cast<int>(std::floor(timeRemaining));
    timerText.setString("REPRISE DANS " + std::to_string(secs < 0 ? 0 : secs));
    timerText.setPosition({ 900.f - timerText.getGlobalBounds().size.x / 2.f, 520.f });

    if (timeRemaining <= 0.f) resumeGame = true;
}

void PauseScene::draw(sf::RenderWindow& window) {
  
    if (m_backgroundScene) {
        m_backgroundScene->draw(window);
    }

  
    window.setView(window.getDefaultView());
    sf::RectangleShape overlay({ 1800.f, 900.f });
    overlay.setFillColor(sf::Color(0, 0, 0, 100)); 
    window.draw(overlay);

    window.draw(pauseText);
    window.draw(timerText);
}