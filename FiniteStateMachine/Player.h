#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public:
    Player();

    void handleEvent(const sf::Event& event);
    void update();
    void draw(sf::RenderWindow& window);
    void spawn(const sf::Vector2f& position);

    sf::Vector2f getPosition() const;

private:
    sf::RectangleShape m_shape;
    float m_step; 
    int m_health;
    bool m_moveLocked = false;
};

