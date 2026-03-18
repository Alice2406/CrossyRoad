//#include "PowerUp.h"
//
//PowerUp::PowerUp(sf::Texture& tex, sf::Vector2f gridPos)
//    : m_sprite(tex), m_gridPos(gridPos)
//{
//  
//    m_sprite.setOrigin({ 32.f, 32.f });
//}
//
//void PowerUp::draw(sf::RenderWindow& window) {
//   
//    const float HALF_WIDTH = 32.f;
//    const float HALF_HEIGHT = 24.f;
//    const float OFFSET_X = 900.f;
//    const float OFFSET_Y = 200.f;
//
//   
//    float isoX = (m_gridPos.x - m_gridPos.y) * HALF_WIDTH + OFFSET_X;
//    float isoY = (m_gridPos.x + m_gridPos.y) * HALF_HEIGHT + OFFSET_Y;
//
//    m_sprite.setPosition({ isoX, isoY });
//    window.draw(m_sprite);
//}
//
//sf::FloatRect PowerUp::getGridBounds() const {
//   
//    return sf::FloatRect({ m_gridPos.x - 0.3f, m_gridPos.y - 0.3f }, { 0.6f, 0.6f });
//}