#include "GameScene.h"
#include "Obstacle.h"
#include <iostream>
#include <cmath>

GameScene::GameScene()
    : m_camera({ 510.f, 2000.f }, { 1800.f, 900.f }),
    m_scoreText(m_font)
{
    if (!m_texCar.loadFromFile("../Asset/scie.png")) std::cerr << "Erreur : scie.png" << std::endl;
    if (!m_texLog.loadFromFile("../Asset/cercueil.png")) std::cerr << "Erreur : cercueil.png" << std::endl;
    if (!m_texFleau.loadFromFile("../Asset/fleau.png")) std::cerr << "Erreur : fleau.png" << std::endl;

    m_map.loadFromFile("../Asset/Plaintext.txt");

    if (!m_font.openFromFile("../Asset/Thunder.ttf")) {
        std::cerr << "Erreur : font introuvable !" << std::endl;
    }

    m_scoreText.setCharacterSize(50);
    m_scoreText.setFillColor(sf::Color::Red);
    m_scoreText.setOutlineColor(sf::Color::White);
    m_scoreText.setOutlineThickness(2.f);
    m_scoreText.setPosition({ 20.f, 20.f });
    m_scoreText.setString("0");

    for (int y = 0; y < 100; ++y) {
        float dir = (y % 2 == 0) ? 1.f : -1.f; 
        float randomSpeed = (2.5f + static_cast<float>(rand() % 20) / 10.f);
        m_lineSpeeds[y] = randomSpeed * dir;
    }

    m_player.spawn({ 10.f, 36.f });
}

void GameScene::handleInput(sf::RenderWindow& window) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        requestPause = true;
    }
}

void GameScene::update(float dt, sf::RenderWindow& window)
{
    m_spawnTimer += dt;

    if (m_spawnTimer >= 0.4f) {
        for (int y = 0; y < 50; ++y) {
            char type = m_map.getTileType(0, y);
            if (type == 1 || type == 2 || type == 6) {

                float speed = m_lineSpeeds[y];

                if (type == 1) speed *= 1.8f;
                if (type == 2) speed *= 0.8f;
                float startX = (speed > 0) ? -5.f : 45.f;
                float targetY = (type == 2) ? (float)y - 0.5f : (float)y - 0.3f;

                bool spaceIsFree = true;
                float minDistance = (type == 2) ? 3.5f : 8.f;

                for (auto& c : m_cars) {
                    if (std::abs(c.getGridBounds().position.x - startX) < minDistance &&
                        std::abs(c.getGridBounds().position.y - targetY) < 0.1f) {
                        spaceIsFree = false; break;
                    }
                }
                for (auto& l : m_logs) {
                    if (std::abs(l.getGridBounds().position.x - startX) < minDistance &&
                        std::abs(l.getGridBounds().position.y - targetY) < 0.1f) {
                        spaceIsFree = false; break;
                    }
                }

                if (spaceIsFree) {
                    int chance = rand() % 100;

                    if (type == 2 && chance > 40) {
                        m_logs.push_back(Log(m_texLog, { startX, targetY }, speed));
                    }
                    else if (type == 6 && chance > 80) {
                        m_cars.push_back(Obstacle(m_texFleau, { startX, targetY }, speed));
                    }
                    else if (type == 1 && chance > 85) {
                        m_cars.push_back(Obstacle(m_texCar, { startX, targetY }, speed));
                    }
                }
            }
        }
        m_spawnTimer = 0.f;
    }

    m_player.update(dt, m_map);
    sf::Vector2f pPos = m_player.getGridPos();

    bool onLog = false;
    float currentLogSpeed = 0.f;

    for (auto it = m_logs.begin(); it != m_logs.end(); ) {
        it->update(dt);

        if (m_player.getGridBounds().findIntersection(it->getGridBounds())) {
            onLog = true;
            currentLogSpeed = it->getSpeed();
        }

        if (it->getGridPos().x > 60.f || it->getGridPos().x < -20.f) {
            it = m_logs.erase(it);
        }
        else {
            ++it;
        }
    }

    if (m_map.isWater(pPos.x, pPos.y)) {
        if (onLog) {
            m_player.setGridPos({ pPos.x + currentLogSpeed * dt, pPos.y });
        }
        else {
            isGameOver = true;
            return;
        }
    }
    else {
        float targetX = std::round(pPos.x);
        if (std::abs(pPos.x - targetX) > 0.01f) {
            if (m_map.isWalkable(targetX, pPos.y)) m_player.setGridPos({ targetX, pPos.y });
        }
    }

    for (auto it = m_cars.begin(); it != m_cars.end(); ) {
        it->update(dt);

        if (m_player.getGridBounds().findIntersection(it->getGridBounds())) {
            isGameOver = true;
            return;
        }

        if (it->getGridX() > 60.f || it->getGridX() < -20.f) {
            it = m_cars.erase(it);
        }
        else {
            ++it;
        }
    }

    m_camera.update(dt, m_player.getPosition());
    float limitY = m_camera.getScreenBottom();
    sf::Vector2f playerIsoPos = m_player.getPosition();

    if (playerIsoPos.y > limitY + 50.f)
    {
        std::cout << "GAME OVER : Le joueur est reste a la traine !" << std::endl;
        isGameOver = true;
        return;
    }
    int calculatedScore = 30 - static_cast<int>(m_player.getGridBounds().position.y);
    if (calculatedScore > m_highScore) {
        m_highScore = calculatedScore;
        m_scoreText.setString(std::to_string(m_highScore));
    }
}

void GameScene::draw(sf::RenderWindow& window) {
    m_camera.apply(window); 

    m_map.draw(window); 

    for (auto& log : m_logs) {
        log.draw(window, *this);
    }

    for (auto& car : m_cars) {
        car.draw(window);
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