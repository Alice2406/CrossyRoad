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

    void addLife() { if (m_lives < 2) m_lives++; } // Max 2 vies
    void loseLife() { m_lives--; }
    int getLives() const { return m_lives; }

    void setInvisibility(float duration) { m_isInvisible = true; m_invisTimer = duration; }
    bool isInvisible() const { return m_isInvisible; }


    void setGhostMode(float duration) {
        m_isGhost = true;
        m_ghostTimer = duration;
    }

    // Cette fonction permettra de vérifier si on peut traverser les voitures
    bool isGhost() const { return m_isGhost; }

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

    int m_lives = 1;             // Le joueur commence avec 1 vie
    bool m_isInvisible = false;  // État du bonus d'invisibilité
    float m_invisTimer = 0.0f;   // Chrono pour l'invisibilité


    bool m_isGhost = false;      // Est-ce que le joueur est un fantôme ?
    float m_ghostTimer = 0.0f;   // Combien de temps il reste ?
};

