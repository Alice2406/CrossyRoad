#include "Camera.h"

Camera::Camera(sf::Vector2f startLogicalPos, sf::Vector2f viewSize)
    : m_logicalPos(startLogicalPos)
{
    m_autoScroll = 0.f;
    m_view.setSize(viewSize);
}

void Camera::update(float dt, sf::Vector2f playerGridPos) {
    if (!m_initialized) {
        m_startY = playerGridPos.y;
        m_autoScroll = 0.f;
        m_initialized = true;
    }

    if (m_speed < m_maxSpeed) {
        m_speed += m_acceleration * dt;
    }
    m_autoScroll += m_speed * dt;

    float autoLimitY = m_startY - m_autoScroll;

    if (playerGridPos.y < autoLimitY) {
        autoLimitY = playerGridPos.y;
        m_autoScroll = m_startY - playerGridPos.y;
    }

    float fixedGridX = 20.0f;

    float targetIsoX = (fixedGridX - autoLimitY) * 32.f + 900.f;
    float targetIsoY = (fixedGridX + autoLimitY) * 24.f + 200.f;

    m_view.setSize({ 1800.f * m_zoomFactor, 900.f * m_zoomFactor });

    float offsetX = 500.f * m_zoomFactor;
    float offsetY = 100.f * m_zoomFactor;

    m_view.setCenter({ targetIsoX + offsetX, targetIsoY + offsetY });
}

void Camera::apply(sf::RenderWindow& window) {
    window.setView(m_view);
}

float Camera::getScreenBottom() const {
    return m_view.getCenter().y + (m_view.getSize().y / 2.0f);
}