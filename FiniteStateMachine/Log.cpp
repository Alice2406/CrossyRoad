#include "Log.h"

#include "GameScene.h" 

void Log::draw(sf::RenderWindow& window, GameScene& scene) {
    sf::Vector2f isoPos = scene.gridToIso(m_gridPos);
    m_sprite.setPosition(isoPos);
    window.draw(m_sprite);
}