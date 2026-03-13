#include "GameOverScene.h"
#include <iostream>
#include <string>

GameOverScene::GameOverScene(int finalScore) {
    if (!font.openFromFile("Assets/Arial.ttf")) {
        std::cerr << "ERREUR : Impossible de charger Arial.ttf" << std::endl;
    }

    titleText = std::make_unique<sf::Text>(font, "GAME OVER", 80);
    titleText->setFillColor(sf::Color::Red);
    titleText->setPosition({ 900.f - titleText->getGlobalBounds().size.x / 2.f, 200.f });

    scoreText = std::make_unique<sf::Text>(font, "Score Final: " + std::to_string(finalScore), 50);
    scoreText->setFillColor(sf::Color::White);
    scoreText->setPosition({ 900.f - scoreText->getGlobalBounds().size.x / 2.f, 350.f });

    instructionText = std::make_unique<sf::Text>(font, "Appuyez sur ENTREE pour rejouer\nou ECHAP pour revenir au menu", 30);
    instructionText->setFillColor(sf::Color::Yellow);
    instructionText->setPosition({ 900.f - instructionText->getGlobalBounds().size.x / 2.f, 500.f });
}

void GameOverScene::handleInput(sf::RenderWindow& window) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
        retryGame = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        backToMenu = true;
    }
}

void GameOverScene::update(float dt, sf::RenderWindow& window) {}

void GameOverScene::draw(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);
    window.draw(*titleText);
    window.draw(*scoreText);
    window.draw(*instructionText);
}