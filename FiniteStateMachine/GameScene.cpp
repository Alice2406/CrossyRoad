#include "GameScene.h"
#include <iostream>
#include <string>

GameScene::GameScene()
    : m_camera({ 510.f, 2000.f }, { 1800.f, 900.f }),
    m_spawnInterval(2.0f),
    m_scoreText(m_font)
{
    m_map.loadFromFile("../Asset/Plaintext.txt");
    m_player.spawn({ 510.f, 2080.f });

    if (!m_font.openFromFile("Assets/Arial.ttf")) {
        std::cerr << "ERREUR : Impossible de charger Arial.ttf" << std::endl;
    }

    m_scoreText.setCharacterSize(50);
    m_scoreText.setFillColor(sf::Color::Blue);
    m_scoreText.setOutlineColor(sf::Color::Black);
    m_scoreText.setOutlineThickness(2.f);
    m_scoreText.setPosition({ 20.f, 20.f });
    m_scoreText.setString("Score: 0");

    isGameOver = false;
    m_highScore = 0;
}

void GameScene::handleInput(sf::RenderWindow& window) {}

void GameScene::update(float dt, sf::RenderWindow& window)
{
    m_player.update();
    m_camera.update(dt, m_player.getPosition());

    int currentScore = static_cast<int>((2080.f - m_player.getPosition().y) / 32.f);

    if (currentScore > m_highScore) {
        m_highScore = currentScore;
        m_scoreText.setString("Score: " + std::to_string(m_highScore));
    }

    if (m_player.getIsoPosition().y > m_camera.getScreenBottom()) {
        isGameOver = true;
    }
}

void GameScene::draw(sf::RenderWindow& window)
{
    m_camera.apply(window);
    m_map.draw(window);
    m_player.draw(window);

    window.setView(window.getDefaultView());
    window.draw(m_scoreText);
}