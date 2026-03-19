#include "GameScene.h"
#include "Obstacle.h"
#include "Invisibility.h"
#include "Invincibility.h"
#include <memory> 
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

    m_player.spawn({ 25.f, 36.f });
    int playerY = 30;

    for (int y = playerY - 40; y <= playerY + 20; ++y) {
        char type = m_map.getTileType(0, y);

        if (type == 1 || type == 2 || type == 6) {
            float speed = m_lineSpeeds[(y % 100 + 100) % 100];
            if (type == 1) speed *= 2.5f;
            if (type == 2) speed *= 0.8f;

            int initialCount = 3 + (rand() % 3);

            for (int i = 0; i < initialCount; ++i) {
                float randomX = static_cast<float>(rand() % 35);
                float targetY = (type == 2) ? (float)y - 0.5f : (float)y - 0.3f;

                if (type == 2)
                    m_logs.push_back(Log(m_texLog, { randomX, targetY }, speed));
                else if (type == 6)
                    m_cars.push_back(Obstacle(m_texFleau, { randomX, targetY }, speed));
                else if (type == 1)
                    m_cars.push_back(Obstacle(m_texCar, { randomX, targetY }, speed));
            }
        }
    }

    float width = 1800.f;
    float height = 900.f;

    m_vignette.setPrimitiveType(sf::PrimitiveType::TriangleFan);
    m_vignette.resize(362);

    m_vignette[0].position = { width / 2.f, height / 2.f };
    m_vignette[0].color = sf::Color(0, 0, 0, 0);

    for (int i = 1; i <= 361; ++i) {
        float angle = i * 3.14159f / 180.f;
        m_vignette[i].position = {
            width / 2.f + cos(angle) * width * 0.9f,
            height / 2.f + sin(angle) * height * 0.9f
        };
        m_vignette[i].color = sf::Color(0, 0, 0, 255);
    }
}

void GameScene::handleInput(sf::RenderWindow& window) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        requestPause = true;
    }
}


void GameScene::update(float dt, sf::RenderWindow& window)
{

    m_spawnTimer += dt;

    if (m_spawnTimer >= 0.2f) {
        int playerLine = (int)m_player.getGridPos().y;

        for (int y = playerLine - 40; y < playerLine + 10; ++y) {

            char type = m_map.getTileType(0, y);

            if (type == 1 || type == 2 || type == 6) {

                int speedIdx = (y % 100 + 100) % 100;
                float speed = m_lineSpeeds[speedIdx];

                if (type == 1) speed *= 1.8f;
                if (type == 2) speed *= 1.f;

                float startX = (speed > 0) ? -5.f : 45.f;
                float targetY = (type == 2) ? (float)y - 0.5f : (float)y - 0.3f;

                bool spaceIsFree = true;
                float minDistance = (type == 2) ? 2.2f : 8.f;

                for (auto& c : m_cars) {
                    if (std::abs(c.getGridBounds().position.y - targetY) < 0.1f && std::abs(c.getGridBounds().position.x - startX) < minDistance) {
                        spaceIsFree = false; break;
                    }
                }
                for (auto& l : m_logs) {
                    if (std::abs(l.getGridPos().y - targetY) < 0.1f && std::abs(l.getGridPos().x - startX) < minDistance) {
                        spaceIsFree = false; break;
                    }
                }

                if (spaceIsFree) {
                    int chance = rand() % 100;
                    if (type == 2 && chance > 25) m_logs.push_back(Log(m_texLog, { startX, targetY }, speed));
                    else if (type == 6 && chance > 60) m_cars.push_back(Obstacle(m_texFleau, { startX, targetY }, speed));
                    else if (type == 1 && chance > 80) m_cars.push_back(Obstacle(m_texCar, { startX, targetY }, speed));
                }
            }
        }
        m_spawnTimer = 0.f;
    }

    m_player.update(dt, m_map);
    sf::Vector2f pPos = m_player.getGridPos();

    int ix = static_cast<int>(std::round(pPos.x));
    int iy = static_cast<int>(std::round(pPos.y));

    auto& grid = m_map.getGrid();

    if (iy >= 0 && iy < (int)grid.size() && ix >= 0 && ix < (int)grid[iy].size()) {
        if (grid[iy][ix] == 5) {
            grid[iy][ix] = 0;

            std::unique_ptr<PowerUp> bonus;

        
            if ((ix + iy) % 2 == 0) {
                bonus = std::make_unique<Invincibility>(); 
            }
            else {
                bonus = std::make_unique<Invisibility>(); 
            }

            bonus->applyEffect(m_player);
            std::cout << "Power-Up recolte !" << std::endl;
        }
    }

   
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
            if (m_player.isInvisible()) {
                ++it;
                continue;
            }
            m_player.loseLife();
            if (m_player.getLives() > 0) {
                std::cout << "OUF ! Vie perdue !" << std::endl;
                it = m_cars.erase(it);
                continue;
            }
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
    m_camera.update(dt, m_player.getGridPos());
    sf::Vector2f playerIso = gridToIso(m_player.getGridPos());
    float limitY = m_camera.getScreenBottom();

    if (playerIso.y > limitY)
    {
        isGameOver = true;
        return;
    }
    int calculatedScore = 30 - static_cast<int>(m_player.getGridBounds().position.y);
    if (calculatedScore > m_highScore) {
        m_highScore = calculatedScore;
        m_scoreText.setString(std::to_string(m_highScore));
    }
}

void GameScene::draw(sf::RenderWindow& window)
{
    m_camera.apply(window);
    m_map.draw(window, m_player.getGridPos());

    auto& grid = m_map.getGrid();
    sf::Sprite pUpSprite(m_texPowerUp);

    pUpSprite.setColor(sf::Color::White);

    for (int y = 0; y < (int)grid.size(); ++y) {
        for (int x = 0; x < (int)grid[y].size(); ++x) {
            if (grid[y][x] == 5) {
             
                pUpSprite.setPosition(gridToIso({ (float)x, (float)y }));
                window.draw(pUpSprite);
            }
        }
    }

    for (auto& car : m_cars) { car.draw(window); }
    for (auto& log : m_logs) { log.draw(window, *this); }

    m_player.draw(window);

    window.setView(window.getDefaultView());
    window.draw(m_vignette);
    window.draw(m_scoreText);
}

    sf::Vector2f GameScene::gridToIso(sf::Vector2f gridPos) 
    {
        const float HALF_WIDTH = 32.f;
        const float HALF_HEIGHT = 24.f;
        const float OFFSET_X = 900.f; 
        const float OFFSET_Y = 200.f;

        float isoX = (gridPos.x - gridPos.y) * HALF_WIDTH + OFFSET_X;
        float isoY = (gridPos.x + gridPos.y) * HALF_HEIGHT + OFFSET_Y;
        return sf::Vector2f(isoX, isoY);
    }



