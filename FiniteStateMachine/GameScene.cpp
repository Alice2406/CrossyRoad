#include "GameScene.h"
#include "Obstacle.h"
#include <iostream>

GameScene::GameScene()
    : m_camera({ 510.f, 2000.f}, {1800.f, 900.f}),
    m_scoreText(m_font)
{
    if (!m_texCar.loadFromFile("../Asset/scie.png")) {
		std::cerr << "Erreur : Impossible de charger la texture de la voiture !" << std::endl;
    }
    m_map.loadFromFile("../Asset/Plaintext.txt");
    m_player.spawn({ 510.f, 2080.f });

    m_player.spawn({ 290.f, 777.f });
    m_cars.push_back(Obstacle(m_texCar, sf::Vector2f(0.f, 0.f), 3.0f));
    m_cars.push_back(Obstacle(m_texCar, sf::Vector2f(0.f, 12.f), 3.0f));
    m_cars.push_back(Obstacle(m_texCar, sf::Vector2f(0.f, 24.f), 3.0f));
    if (!m_font.openFromFile("Assets/Arial.ttf")) {
        m_font.openFromFile("../Asset/Arial.ttf");
    }

    m_scoreText.setCharacterSize(50);
    m_scoreText.setFillColor(sf::Color::Blue);
    m_scoreText.setOutlineColor(sf::Color::Black);
    m_scoreText.setOutlineThickness(2.f);
    m_scoreText.setPosition({ 20.f, 20.f });
    m_scoreText.setString("Score: 0");
}

void GameScene::handleInput(sf::RenderWindow& window) {}

void GameScene::update(float dt, sf::RenderWindow& window)
{
    m_spawnTimer += dt;

    if (m_spawnTimer >= 3.0f) {
        std::cout << "SPAWN !" << std::endl;
        m_cars.push_back(Obstacle(m_texCar, sf::Vector2f(0.f, 0.f), 3.0f));
        m_cars.push_back(Obstacle(m_texCar, sf::Vector2f(0.f, 12.f), 3.0f));
        m_cars.push_back(Obstacle(m_texCar, sf::Vector2f(0.f, 24.f), 3.0f));


        m_spawnTimer = 0.f;
    }

    for (auto it = m_cars.begin(); it != m_cars.end();) {
        it->update(dt);

        if (it->getGridX() > 42.f) {
            it = m_cars.erase(it);
        }
        else {
            ++it;
        }
    }

    m_player.update();
    sf::Vector2f playerScreenPos = m_player.getIsoPosition();
    m_player.update();
    m_camera.update(dt, m_player.getPosition());

    int playerRow = static_cast<int>(m_player.getPosition().y / 32.f);
    int startRow = static_cast<int>(2096.f / 32.f);
    int calculatedScore = startRow - playerRow;

    if (calculatedScore > m_highScore) {
        m_highScore = calculatedScore;
        m_scoreText.setString("Score: " + std::to_string(m_highScore));
    }

    if (m_player.getIsoPosition().y > m_camera.getScreenBottom()) {
        std::cout << "Mort" << std::endl;
    }
}

void GameScene::draw(sf::RenderWindow& window)
{
    m_camera.apply(window);
    m_map.draw(window);
    for (auto& car : m_cars) {
        car.draw(window);
    }
    m_player.draw(window);

    window.setView(window.getDefaultView());
    window.draw(m_scoreText);
}