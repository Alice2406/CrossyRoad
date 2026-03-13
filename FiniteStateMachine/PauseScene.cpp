//#include "PauseScene.h"
//#include <iostream>
//#include <cmath>
//
//PauseScene::PauseScene()
//    : timeRemaining(3.9f),
//    pauseText(font),
//    timerText(font)
//{
//    if (!font.openFromFile("Assets/Arial.ttf")) {
//        std::cerr << "Erreur : police introuvable !" << std::endl;
//    }
//
//    // Titre plus raisonnable mais inquiétant
//    pauseText.setString("TU Y ES PRESQUE...");
//    pauseText.setCharacterSize(80); // Réduit de 130 à 80
//    pauseText.setFillColor(sf::Color(180, 0, 0, 220));
//    pauseText.setOutlineThickness(2.f);
//    pauseText.setOutlineColor(sf::Color::Black);
//
//    // Timer discret en bas
//    timerText.setCharacterSize(40);
//    timerText.setFillColor(sf::Color(255, 255, 255, 180));
//}
//
//void PauseScene::handleInput(sf::RenderWindow& window) {}
//
//void PauseScene::update(float dt, sf::RenderWindow& window) {
//    timeRemaining -= dt;
//    totalTime += dt;
//
//    // Tremblement très léger (effet de tension)
//    float shakeX = std::sin(totalTime * 12.f) * 2.f;
//    pauseText.setPosition({ 900.f - pauseText.getGlobalBounds().size.x / 2.f + shakeX, 400.f });
//
//    int displaySeconds = static_cast<int>(std::floor(timeRemaining));
//    if (displaySeconds < 0) displaySeconds = 0;
//
//    timerText.setString("REPRISE DANS " + std::to_string(displaySeconds));
//    timerText.setPosition({ 900.f - timerText.getGlobalBounds().size.x / 2.f, 520.f });
//
//    if (timeRemaining <= 0.f) {
//        resumeGame = true;
//    }
//}
//
//void PauseScene::draw(sf::RenderWindow& window) {
//    // IMPORTANT : On ne touche pas à la vue tout de suite pour laisser le jeu tel quel
//    // Mais on dessine l'overlay par rapport à la fenêtre
//    window.setView(window.getDefaultView());
//
//    // FOND TRANSPARENT (Le secret est ici : le 4ème chiffre est l'Alpha/Opacité)
//    // 0 = invisible, 255 = plein. On met 100 pour voir le jeu derrière.
//    sf::RectangleShape overlay({ 1800.f, 900.f });
//    overlay.setFillColor(sf::Color(20, 0, 0, 100)); // Un voile rouge très léger
//    window.draw(overlay);
//
//    window.draw(pauseText);
//    window.draw(timerText);
//}

#include "PauseScene.h"
#include <cmath>

PauseScene::PauseScene(std::unique_ptr<Scene> backScene)
    : m_backgroundScene(std::move(backScene)), // On "capture" le jeu
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
    // 1. DESSINER LE JEU EN FOND
    if (m_backgroundScene) {
        m_backgroundScene->draw(window);
    }

    // 2. DESSINER L'INTERFACE DE PAUSE
    window.setView(window.getDefaultView());
    sf::RectangleShape overlay({ 1800.f, 900.f });
    overlay.setFillColor(sf::Color(0, 0, 0, 100)); // 100 = Transparence
    window.draw(overlay);

    window.draw(pauseText);
    window.draw(timerText);
}