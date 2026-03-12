#include "Map.h"
#include <iostream>
#include <fstream>
#include <sstream>

Map::Map() : m_tileSprite(m_texGrass) {

    if (!m_texGrass.loadFromFile("../Asset/grass.png") ||
        !m_texRoad.loadFromFile("../Asset/road.png") ||
        !m_texWater.loadFromFile("../Asset/water.png"))
    {
        std::cerr << "Erreur : Impossible de charger une ou plusieurs textures !" << std::endl;
    }

    m_tileSprite.setOrigin({ 32.f, 32.f });
}

void Map::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir " << filename << std::endl;
        return;
    }

    m_grid.clear();
    std::string line;
    while (std::getline(file, line)) {
        std::vector<int> row;
        std::stringstream ss(line);
        int type;

        while (ss >> type) {
            row.push_back(type);
        }

        if (!row.empty()) {
            m_grid.push_back(row);
        }
    }
    file.close();
    std::cout << "Map chargee avec succes (" << m_grid.size() << " lignes)." << std::endl;
}

void Map::draw(sf::RenderWindow& window) {
    if (m_grid.empty()) return;

    const float OFFSET_X = 900.f;
    const float OFFSET_Y = 200.f;
    const float HALF_WIDTH = 32.f;
    const float HALF_HEIGHT = 16.f;

    for (int y = 0; y < m_grid.size(); ++y) {
        for (int x = 0; x < m_grid[y].size(); ++x) {

            int type = m_grid[y][x];
            if (type == 0) m_tileSprite.setTexture(m_texGrass, true);
            else if (type == 1) m_tileSprite.setTexture(m_texRoad, true);
            else if (type == 2) m_tileSprite.setTexture(m_texWater, true);

            float isoX = (x - y) * HALF_WIDTH;
            float isoY = (x + y) * HALF_HEIGHT;

            m_tileSprite.setOrigin({ 32.f, 32.f });

            m_tileSprite.setPosition({ isoX + OFFSET_X, isoY + OFFSET_Y });
            m_tileSprite.setScale({ 2.f, 2.f });
            window.draw(m_tileSprite);
        }
    }
}