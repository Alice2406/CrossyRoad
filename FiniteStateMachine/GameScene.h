#pragma once
#include "Scene.h"
#include "Player.h"
#include "Obstacle.h"
#include "Map.h"
#include "Camera.h"
#include <vector>

class GameScene : public Scene
{
public:
    GameScene();

    void handleInput(sf::RenderWindow& window) override;
    void update(float dt, sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;

    bool isGameOver = false;
    int getScore() const { return m_highScore; }

private:
    Player m_player;
    std::vector<Obstacle> m_obstacles;
    Map m_map;
    Camera m_camera;
    sf::Clock m_spawnClock;
    float m_spawnInterval = 2.0f;

    sf::Font m_font;
    sf::Text m_scoreText;
    int m_highScore = 0;
};