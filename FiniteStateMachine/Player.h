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

    void addLife() { if (m_lives < 2) m_lives++; } 
    void loseLife() { m_lives--; }
    int getLives() const { return m_lives; }

    void setInvisibility(float duration) { m_isInvisible = true; m_invisTimer = duration; }



    void setGhostMode(float duration) {
        m_isGhost = true;
        m_ghostTimer = duration;
    }

    bool isGhost() const { return m_isGhost; }
    bool isInvincible() const { return m_isInvincible; }
    bool isInvisible() const { return m_ghostTimer > 0.f; }

    float m_flashTimer = 0.f; 
    void setInvincibleTimer(float duration) { m_invincibleTimer = duration; }


private:
    sf::Vector2f m_gridPos;
    sf::Vector2f m_basePos;
    sf::RectangleShape m_shape;
    float m_step; 
    bool m_moveLocked = false;
    sf::Texture m_texUp, m_texDown, m_texLeft, m_texRight;
    sf::Sprite m_sprite;

    int m_lives = 1;             
    bool m_isInvisible = false;
    float m_invisTimer = 0.0f;  


    bool m_isGhost = false;      
    float m_ghostTimer = 0.0f;  
    bool m_isInvincible = false;

    float m_invincibleTimer = 0.f;
    float m_invisibleTimer = 0.f;

};

