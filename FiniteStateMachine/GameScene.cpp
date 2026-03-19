#include "GameScene.h"
#include "Obstacle.h"
#include "Invisibility.h"
#include "Invincibility.h"
#include <memory> 
#include <iostream>

GameScene::GameScene()
    : m_camera({ 510.f, 2000.f }, { 1800.f, 900.f }),
    m_scoreText(m_font),
    m_spawnInterval(3.0f) 
{
    if (!m_texCar.loadFromFile("../Asset/scie.png")) {
		std::cerr << "Erreur : scie.png introuvable !" << std::endl;
    }
    if (!m_texLog.loadFromFile("../Asset/cercueil.png")) {
        std::cerr << "Erreur : cercueil.png introuvable !" << std::endl;
    }
    if (!m_texFleau.loadFromFile("../Asset/fleau.png")) {
        std::cerr << "Erreur : fleau.png introuvable !" << std::endl;
    }
    m_map.loadFromFile("../Asset/Plaintext.txt");

    m_player.spawn({ 10.f, 30.f });
    m_cars.push_back(Obstacle(m_texCar, sf::Vector2f(-2.f, 1.7f), 3.0f));
    m_cars.push_back(Obstacle(m_texCar, sf::Vector2f(-2.f, 12.7f), 3.0f));
    m_cars.push_back(Obstacle(m_texCar, sf::Vector2f(-2.f, 18.7f), 3.0f));
    m_cars.push_back(Obstacle(m_texCar, sf::Vector2f(-2.f, 22.7f), 3.0f));

    m_cars.push_back(Obstacle(m_texFleau, sf::Vector2f(-2.f, 26.7f), 4.0f));
    m_cars.push_back(Obstacle(m_texFleau, sf::Vector2f(-2.f, 3.7f), 3.0f));
    m_cars.push_back(Obstacle(m_texFleau, sf::Vector2f(-2.f, 15.7f), 3.0f));

    m_logs.push_back(Log(m_texLog, sf::Vector2f(-3.f, 24.5f), 3.0f));
    m_logs.push_back(Log(m_texLog, sf::Vector2f(-3.f, 23.5f), 2.0f));
    if (!m_font.openFromFile("../Asset/Thunder.ttf")) {
		std::cerr << "Erreur : impossible de charger la police !" << std::endl;
    }

    m_scoreText.setCharacterSize(50);
    m_scoreText.setFillColor(sf::Color::Red);
    m_scoreText.setOutlineColor(sf::Color::White);
    m_scoreText.setOutlineThickness(2.f);
    m_scoreText.setPosition({ 20.f, 20.f });
    m_scoreText.setString("0");
}

void GameScene::handleInput(sf::RenderWindow& window) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        requestPause = true;
    }
}


void GameScene::update(float dt, sf::RenderWindow& window)
{
    m_logTimer += dt;
    if (m_logTimer >= 2.f) {
        m_logs.push_back(Log(m_texLog, sf::Vector2f(-3.f, 24.5f), 3.0f));
        m_logs.push_back(Log(m_texLog, sf::Vector2f(-3.f, 23.5f), 2.0f));
        m_logTimer = 0.f;
    }

    for (auto it = m_logs.begin(); it != m_logs.end(); ) {
        if (it->getGridPos().x > 50.f) {
            it = m_logs.erase(it);
        }
        else {
            ++it;
        }
    }
    m_spawnTimer += dt;
    if (m_spawnTimer >= 3.0f) {
        m_cars.push_back(Obstacle(m_texCar, sf::Vector2f(-2.f, 1.7f), 4.0f));
        m_cars.push_back(Obstacle(m_texCar, sf::Vector2f(-2.f, 12.7f), 4.0f));
        m_cars.push_back(Obstacle(m_texCar, sf::Vector2f(-2.f, 18.7f), 3.0f));
        m_cars.push_back(Obstacle(m_texCar, sf::Vector2f(-2.f, 22.7f), 4.0f));
        m_cars.push_back(Obstacle(m_texFleau, sf::Vector2f(-2.f, 26.7f), 4.0f));
        m_cars.push_back(Obstacle(m_texFleau, sf::Vector2f(-2.f, 3.7f), 3.0f));
        m_cars.push_back(Obstacle(m_texFleau, sf::Vector2f(-2.f, 15.7f), 3.0f));
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

    for (auto& l : m_logs) {
        l.update(dt);
        if (m_player.getGridBounds().findIntersection(l.getGridBounds())) {
            onLog = true;
            currentLogSpeed = l.getSpeed();
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
            if (m_map.isWalkable(targetX, pPos.y)) {
                m_player.setGridPos({ targetX, pPos.y });
            }
            else {
                float alternativeX = (targetX > pPos.x) ? std::floor(pPos.x) : std::ceil(pPos.x);
                if (m_map.isWalkable(alternativeX, pPos.y)) {
                    m_player.setGridPos({ alternativeX, pPos.y });
                }
            }
        }
    }

    for (auto it = m_cars.begin(); it != m_cars.end();) {
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
        if (it->getGridX() > 42.f) it = m_cars.erase(it);
        else ++it;
    }
    m_camera.update(dt, m_player.getPosition());
}

void GameScene::draw(sf::RenderWindow& window)
{
    m_camera.apply(window);
    m_map.draw(window);

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



