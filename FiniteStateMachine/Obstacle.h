#pragma once
#include <SFML/Graphics.hpp>

class Obstacle {
public:
    Obstacle(sf::Vector2f startPos, float speed)
        : m_pos(startPos), m_speed(speed) {
        m_shape.setSize({ 50.f, 50.f });
        m_shape.setFillColor(sf::Color::Red);
        m_shape.setOrigin({ 32.f, 32.f });
    }

    void update(float dt) {
        m_pos.x += m_speed * dt;
        m_pos.y += (m_speed * (27.f / 80.f)) * dt; 
    }

    void draw(sf::RenderWindow& window) {
        float isoX = (m_pos.x - m_pos.y);
        float isoY = (m_pos.x + m_pos.y) * 0.5f;

        m_shape.setPosition({ isoX + 900.f, isoY + 200.f });
        m_shape.setRotation(sf::degrees(45.f));
        window.draw(m_shape);
    }

    sf::Vector2f getPosition() const { return m_pos; }

private:
    sf::RectangleShape m_shape;
    sf::Vector2f m_pos;
    float m_speed;
};

