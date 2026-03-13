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

private:
    Player m_player;
    std::vector<Obstacle> m_obstacles;
    Map m_map;

    sf::Texture m_texCar; 
    std::vector<Obstacle> m_cars; 
    float m_spawnTimer = 0.f;

    Camera m_camera;
    sf::Clock m_spawnClock;
    float m_spawnInterval;

    sf::Font m_font;
    sf::Text m_scoreText;
    int m_highScore = 0;
};