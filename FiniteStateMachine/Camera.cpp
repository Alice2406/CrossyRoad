#include "Camera.h"

Camera::Camera(sf::Vector2f startLogicalPos, sf::Vector2f viewSize)
    : m_logicalPos(startLogicalPos)
{
    m_view.setSize(viewSize);
}

void Camera::update(float dt, sf::Vector2f playerLogicalPos) {
    m_logicalPos.y -= m_speed * dt;

    if (playerLogicalPos.y < m_logicalPos.y - 120.0f) {
        m_logicalPos.y = playerLogicalPos.y + 120.0f;
    }

    float isoX = (m_logicalPos.x - m_logicalPos.y) + 900.f;
    float isoY = (m_logicalPos.x + m_logicalPos.y) * 0.5f + 200.f;

    m_view.setCenter({ isoX, isoY });
}

void Camera::apply(sf::RenderWindow& window) {
    window.setView(m_view);
}

float Camera::getScreenBottom() const {
    return m_view.getCenter().y + (m_view.getSize().y / 2.0f);
}