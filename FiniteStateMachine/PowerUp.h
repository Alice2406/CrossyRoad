#pragma once

#include <SFML/Graphics.hpp>
#include"Player.h"

class PowerUp {
protected:
    sf::Sprite m_sprite;
    sf::Vector2f m_gridPos;
    bool m_isCollected;

public:
    PowerUp(sf::Texture& tex, sf::Vector2f gridPos);
    virtual ~PowerUp();

    virtual void applyEffect(Player& player) = 0; // Purement virtuelle

    void draw(sf::RenderWindow& window);
    bool isCollected() const;
    void collect();
    sf::FloatRect getBounds() const;
};

// --- Les classes dérivées ---

class Invincibility : public PowerUp {
public:
    Invincibility(sf::Texture& tex, sf::Vector2f gridPos);
    void applyEffect(Player& player) override;
};

