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

    m_player.spawn({ 10.f, 30.f });
    m_cars.push_back(Obstacle(m_texCar, sf::Vector2f(0.f, 1.5f), 3.0f));
    m_cars.push_back(Obstacle(m_texCar, sf::Vector2f(0.f, 12.5f), 3.0f));
    m_cars.push_back(Obstacle(m_texCar, sf::Vector2f(0.f, 26.5f), 3.0f));
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

void GameScene::handleInput(sf::RenderWindow& window) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        requestPause = true;
    }
}

void GameScene::update(float dt, sf::RenderWindow& window)
{
    m_spawnTimer += dt;
    if (m_spawnTimer >= 3.0f) {
        m_cars.push_back(Obstacle(m_texCar, sf::Vector2f(-5.f, 1.5f), 4.0f));
        m_cars.push_back(Obstacle(m_texCar, sf::Vector2f(-5.f, 12.5f), 4.0f));
        m_cars.push_back(Obstacle(m_texCar, sf::Vector2f(-5.f, 26.5f), 4.0f));
        m_spawnTimer = 0.f;
    }

    m_player.update(dt, m_map);

    for (auto it = m_cars.begin(); it != m_cars.end();) {
        it->update(dt);

        if (m_player.getGridBounds().findIntersection(it->getGridBounds())) {
            std::cout << "MORT !" << std::endl;
            m_player.spawn({ 0.f, 30.f });
        }

        if (it->getGridX() > 42.f) {
            it = m_cars.erase(it);
        }
        else {
            ++it;
        }
    }

    m_camera.update(dt, m_player.getPosition());

    int calculatedScore = 30 - static_cast<int>(m_player.getGridBounds().position.y);
    if (calculatedScore > m_highScore) {
        m_highScore = calculatedScore;
        m_scoreText.setString("Score: " + std::to_string(m_highScore));
    }
}

void GameScene::draw(sf::RenderWindow& window)
{
    m_camera.apply(window);
    m_map.draw(window);
    for (auto& car : m_cars) {
        car.draw(window);

        sf::FloatRect box = car.getGridBounds();
        sf::ConvexShape debugShape(4);

        debugShape.setPoint(0, gridToIso({ box.position.x, box.position.y }));
        debugShape.setPoint(1, gridToIso({ box.position.x + box.size.x, box.position.y }));
        debugShape.setPoint(2, gridToIso({ box.position.x + box.size.x, box.position.y + box.size.y }));
        debugShape.setPoint(3, gridToIso({ box.position.x, box.position.y + box.size.y }));

        debugShape.setFillColor(sf::Color(255, 0, 0, 100));
        window.draw(debugShape);
    }
    m_player.draw(window);

    window.setView(window.getDefaultView());
    window.draw(m_scoreText);
}

sf::Vector2f GameScene::gridToIso(sf::Vector2f gridPos) {
    const float HALF_WIDTH = 32.f;
    const float HALF_HEIGHT = 24.f;
    const float OFFSET_X = 900.f;
    const float OFFSET_Y = 200.f;

    float isoX = (gridPos.x - gridPos.y) * HALF_WIDTH + OFFSET_X;
    float isoY = (gridPos.x + gridPos.y) * HALF_HEIGHT + OFFSET_Y;
    return sf::Vector2f({ isoX, isoY });
}