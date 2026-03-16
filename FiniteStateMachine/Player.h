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
    sf::Vector2f getPosition() const;
    sf::Vector2f getIsoPosition() const;
    sf::FloatRect getGridBounds() const;
private:
    sf::Vector2f m_gridPos;
    sf::Vector2f m_basePos;
    sf::RectangleShape m_shape;
    float m_step; 
    bool m_moveLocked = false;
    sf::Texture m_texUp, m_texDown, m_texLeft, m_texRight;
    sf::Sprite m_sprite;

};

