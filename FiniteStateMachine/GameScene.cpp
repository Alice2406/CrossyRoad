#include "GameScene.h"

GameScene::GameScene()
    : m_spawnInterval(2.0f)
{
    m_map.loadFromFile("../Asset/Plaintext.txt");

    m_player.spawn({ 290.f, 777.f });

    m_view.setSize({ 1800.f, 900.f });
}

void GameScene::handleInput(sf::RenderWindow& window) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        requestPause = true;
    }
}
void GameScene::update(float dt, sf::RenderWindow& window)
{
    m_player.update();

    sf::Vector2f playerScreenPos = m_player.getIsoPosition();
    m_view.setCenter(playerScreenPos);
}

void GameScene::draw(sf::RenderWindow& window)
{
    window.setView(m_view);
    m_map.draw(window);

    m_player.draw(window);
}