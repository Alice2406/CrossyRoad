#pragma once
#include "Scene.h"
#include "Player.h"
#include "Obstacle.h"
#include "Map.h"
#include "Camera.h"
#include "Log.h"
#include <vector>
#include <map>

class GameScene : public Scene
{
public:
    GameScene();
    bool requestPause = false;

    void handleInput(sf::RenderWindow& window) override;
    void update(float dt, sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;
    sf::Vector2f gridToIso(sf::Vector2f gridPos);
    bool isGameOver = false;
    int m_highScore = 0;
private:
    sf::VertexArray m_vignette{ sf::PrimitiveType::TriangleFan, 362 };
    Player m_player;
    std::vector<Obstacle> m_obstacles;
    Map m_map;

    sf::Texture m_texCar; 
    sf::Texture m_texFleau;
    std::vector<Obstacle> m_cars; 
    std::map<int, float> m_lineSpeeds;
    float m_spawnTimer = 0.f;
	float m_logTimer = 0.f;
    std::vector<Log> m_logs;
    sf::Texture m_texLog;
    Camera m_camera;
    sf::Clock m_spawnClock;
    float m_spawnInterval;

    sf::Font m_font;
    sf::Text m_scoreText;
    int m_highScore = 0;

    sf::Texture m_texPowerUp;
};