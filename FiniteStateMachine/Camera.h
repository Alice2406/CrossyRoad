#pragma once
#include <SFML/Graphics.hpp>

class Camera {
public:
    Camera(sf::Vector2f startLogicalPos, sf::Vector2f viewSize);

    void update(float dt, sf::Vector2f playerLogicalPos);

    void apply(sf::RenderWindow& window);

    sf::View& getView() { return m_view; }
    float getScreenBottom() const;

private:
    float m_startY = 0.f;
    bool m_initialized = false;
    float m_highestYReached = 30.0f;
	float m_autoScroll;
    float m_zoomFactor = 0.6f;
    float m_maxSpeed = 15.0f; 
    float m_acceleration = 0.1f;
    sf::View m_view;
    sf::Vector2f m_logicalPos;
    float m_speed = 0.5f;
};