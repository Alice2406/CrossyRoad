#include "Obstacle.h"
#include <iostream>

Obstacle::Obstacle(sf::Texture& tex, sf::Vector2f gridPos, float speed)
    : m_sprite(tex),       
    m_gridPos(gridPos),
    m_speed(speed)
{
    m_sprite.setOrigin({ 32.f, 48.f });
}

void Obstacle::update(float dt) {
    m_gridPos.x += m_speed * dt;
}

void Obstacle::draw(sf::RenderWindow& window) {
    const float HALF_WIDTH = 32.f;
    const float HALF_HEIGHT = 24.f;
    const float OFFSET_X = 900.f;
    const float OFFSET_Y = 200.f;

    float isoX = (m_gridPos.x - m_gridPos.y) * HALF_WIDTH + OFFSET_X;
    float isoY = (m_gridPos.x + m_gridPos.y) * HALF_HEIGHT + OFFSET_Y;

    m_sprite.setPosition({ isoX, isoY });
    window.draw(m_sprite);
}

sf::FloatRect Obstacle::getGridBounds() const {
    float width = 0.7f;
    float height = 0.8f; // La zone de contact au sol est assez fine

    // On peut ajouter un offset si m_gridPos représente le centre du sprite
    // Mais si m_gridPos représente la base, on ajuste simplement ainsi :
    float offsetY = 0.1f; // Ajuste cette valeur pour monter/descendre la box

    return sf::FloatRect(
        { m_gridPos.x - width / 2.f, m_gridPos.y - height / 2.f + offsetY },
        { width, height }
    );
}