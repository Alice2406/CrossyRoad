#include "GameScene.h"
#include "Obstacle.h"

GameScene::GameScene()
{
    if (!m_texCar.loadFromFile("../Asset/scie.png")) {
		std::cerr << "Erreur : Impossible de charger la texture de la voiture !" << std::endl;
    }
    m_map.loadFromFile("../Asset/Plaintext.txt");

    m_player.spawn({ 290.f, 777.f });
    m_cars.push_back(Obstacle(m_texCar, sf::Vector2f(0.f, 0.f), 3.0f));
    m_cars.push_back(Obstacle(m_texCar, sf::Vector2f(0.f, 12.f), 3.0f));
    m_cars.push_back(Obstacle(m_texCar, sf::Vector2f(0.f, 24.f), 3.0f));
    m_view.setSize({ 1800.f, 900.f });
}

void GameScene::handleInput(sf::RenderWindow& window)
{
}

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
    m_view.setCenter(playerScreenPos);
}

void GameScene::draw(sf::RenderWindow& window)
{
    window.setView(m_view);
    m_map.draw(window);
    for (auto& car : m_cars) {
        car.draw(window);
    }
    m_player.draw(window);
}