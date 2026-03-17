#pragma once
#include <SFML/Graphics.hpp>
class GameScene;


class Log {
public:
    Log(sf::Texture& tex, sf::Vector2f gridPos, float speed)
		: m_gridPos(gridPos), m_speed(speed), m_sprite(tex)
    {
        m_sprite.setTexture(tex);
    }

    sf::Vector2f getGridPos() const { return m_gridPos; }
    void update(float dt) {
        m_gridPos.x += m_speed * dt;
    }
    void draw(sf::RenderWindow& window, GameScene& scene);
    sf::FloatRect getGridBounds() const {
        return sf::FloatRect(m_gridPos, { 2.0f, 0.8f }); // Une bûche de 2 cases de large
    }

    float getSpeed() const { return m_speed; }

private:
    sf::Sprite m_sprite;
    sf::Vector2f m_gridPos;
    float m_speed;
};