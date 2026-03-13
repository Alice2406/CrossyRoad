#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML/Graphics.hpp>

class Obstacle {
public:
    Obstacle(sf::Texture& tex, sf::Vector2f gridPos, float speed);

    void update(float dt);
    void draw(sf::RenderWindow& window);
    float getGridX() const { return m_gridPos.x; }

private:
    sf::Sprite m_sprite;
    sf::Vector2f m_gridPos; // Position dans la grille (ex: 5.0, 2.0)
    float m_speed;
};

#endif