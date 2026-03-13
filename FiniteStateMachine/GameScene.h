#pragma once
#include "Scene.h"
#include "Player.h"
#include "Obstacle.h"
#include <vector>
#include "Map.h"
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
    sf::View m_view;
    sf::Texture m_texCar; 
    std::vector<Obstacle> m_cars; 
    float m_spawnTimer = 0.f;

};