#include "GameScene.h"
#include "Obstacle.h"

GameScene::GameScene()
{
    if (!m_texCar.loadFromFile("../Asset/scie.png")) {
		std::cerr << "Erreur : Impossible de charger la texture de la voiture !" << std::endl;
    }
    m_map.loadFromFile("../Asset/Plaintext.txt");

    m_player.spawn({ 290.f, 777.f });

    m_view.setSize({ 1800.f, 900.f });
}

void GameScene::handleInput(sf::RenderWindow& window)
{
}

void GameScene::update(float dt, sf::RenderWindow& window)
{
    m_spawnTimer += dt;


    // Toutes les 3 secondes, on crée une nouvelle voiture
    if (m_spawnTimer >= 3.0f) {
        m_cars.push_back(Obstacle(m_texCar, sf::Vector2f(0.f, 0.f), 3.0f));
        m_spawnTimer = 0.f;
    }

    // On met à jour et on nettoie les voitures sorties de la map
    for (auto it = m_obstacles.begin(); it != m_obstacles.end();) {
        it->update(dt);

        if (it->getGridX() > 20.f) { // Si dépasse la case 20
            it = m_obstacles.erase(it); // Supprime
        }
        else {
            ++it;
        }
    }
    m_player.update();

    sf::Vector2f playerScreenPos = m_player.getIsoPosition();
	std::cout << "Player screen position: (" << playerScreenPos.x << ", " << playerScreenPos.y << ")\n";
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