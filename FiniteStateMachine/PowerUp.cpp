#include "PowerUp.h"


PowerUp::PowerUp(sf::Texture& tex, sf::Vector2f gridPos)
    : m_gridPos(gridPos), m_isCollected(false)
{
    m_sprite.setTexture(tex);
    m_sprite.setOrigin({ 32.f, 48.f }); 
}

PowerUp::~PowerUp() {}

void PowerUp::draw(sf::RenderWindow& window) {
    if (!m_isCollected) {
        const float HALF_WIDTH = 32.f;
        const float HALF_HEIGHT = 24.f;
        const float OFFSET_X = 900.f;
        const float OFFSET_Y = 200.f;

        float isoX = (m_gridPos.x - m_gridPos.y) * HALF_WIDTH + OFFSET_X;
        float isoY = (m_gridPos.x + m_gridPos.y) * HALF_HEIGHT + OFFSET_Y;

        m_sprite.setPosition({ isoX, isoY });
        window.draw(m_sprite);
    }
}

bool PowerUp::isCollected() const { return m_isCollected; }

void PowerUp::collect() { m_isCollected = true; }

sf::FloatRect PowerUp::getBounds() const { return m_sprite.getGlobalBounds(); }


// --- Classe Fille Invincibility ---

Invincibility::Invincibility(sf::Texture& tex, sf::Vector2f gridPos)
    : PowerUp(tex, gridPos) {
}

void Invincibility::applyEffect(Player& player) {
    player.isInvincible = true;
    // Optionnel : un petit effet visuel immédiat
}