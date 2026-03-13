#include "Obstacle.h"

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
    sf::CircleShape debugCircle(20.f);
    debugCircle.setFillColor(sf::Color::Red);
    debugCircle.setPosition({ isoX, isoY });
    window.draw(debugCircle);
    window.draw(m_sprite);
}