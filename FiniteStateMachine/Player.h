#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
class Player
{
public:
    Player();

    void update(float dt, Map& map);
    void draw(sf::RenderWindow& window);
    void spawn(const sf::Vector2f& position);
    sf::Vector2f getGridPos() const { return m_gridPos; }
    sf::Vector2f getPosition() const;
    sf::Vector2f getIsoPosition() const;
    sf::FloatRect getGridBounds() const;
    void setGridPos(sf::Vector2f newPos) { m_gridPos = newPos; }
private:
    int m_currentFrame = 0;
    int m_frameCount = 9;
    float m_frameTime = 0.15f;
    float m_elapsedTime = 0.f;
    sf::Vector2i m_frameSize;
    sf::Vector2f m_gridPos;
    sf::Vector2f m_basePos;
    sf::RectangleShape m_shape;
    float m_step; 
    bool m_moveLocked = false;
    sf::Texture m_texture;
    sf::Sprite m_sprite;

};

