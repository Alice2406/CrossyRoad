#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML/Graphics.hpp>

class Obstacle {
public:
    Obstacle(sf::Texture& tex, sf::Vector2f gridPos, float speed);

    void update(float dt);
    void draw(sf::RenderWindow& window);
    float getGridX() const { return m_gridPos.x; }
    sf::FloatRect getGridBounds() const;
private:
    sf::Sprite m_sprite;
    sf::Vector2f m_gridPos;
    float m_speed;
};

#endif