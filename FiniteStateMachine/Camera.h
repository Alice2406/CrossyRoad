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
    sf::View m_view;
    sf::Vector2f m_logicalPos;
    float m_speed = 40.0f;
};