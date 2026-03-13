#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

class Map {
public:
    Map();
    void loadFromFile(const std::string& filename);
    void draw(sf::RenderWindow& window);

    std::vector<std::vector<int>>& getGrid() { return m_grid; }

private:
    std::vector<std::vector<int>> m_grid;
    sf::Texture m_texGrass, m_texRoad, m_texWater, m_texTree;
    sf::Sprite m_tileSprite;

};