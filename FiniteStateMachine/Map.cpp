#include "Map.h"
#include <iostream>
#include <fstream>
#include <sstream>

Map::Map() : m_tileSprite(m_texGrass) {

    if (!m_texGrass.loadFromFile("../Asset/grass2.png") ||
        !m_texRail.loadFromFile("../Asset/rails.png") ||
        !m_texTree.loadFromFile("../Asset/arbre.png") ||
        !m_texTree2.loadFromFile("../Asset/arbre2.png") ||
        !m_texTree3.loadFromFile("../Asset/arbre3.png") ||
        !m_texgrave.loadFromFile("../Asset/tombe22.png") ||
        !m_texRoad.loadFromFile("../Asset/pierre.png") ||
        !m_texWater.loadFromFile("../Asset/water2.png"))
    {
        std::cerr << "Erreur : Impossible de charger une ou plusieurs textures !" << std::endl;
    }

    m_tileSprite.setOrigin({ 32.f, 32.f });
}

bool Map::isWater(float x, float y) const {
    if (m_grid.empty()) return false;

    int gy = (static_cast<int>(std::floor(y)) % (int)m_grid.size() + (int)m_grid.size()) % (int)m_grid.size();
    int gx = static_cast<int>(std::floor(x));

    if (gx < 0 || gx >= (int)m_grid[gy].size()) {
        return false;
    }

    return (m_grid[gy][gx] == 2);
}

char Map::getTileType(int x, int y) const {
    if (m_grid.empty()) return ' ';
    int gridY = (y % (int)m_grid.size() + (int)m_grid.size()) % (int)m_grid.size();

    if (x >= 0 && (size_t)x < m_grid[gridY].size()) {
        return m_grid[gridY][x];
    }
    return ' ';
}

bool Map::isWalkable(float x, float y) {
    if (m_grid.empty()) return false;

    int gy = (static_cast<int>(std::floor(y)) % (int)m_grid.size() + (int)m_grid.size()) % (int)m_grid.size();
    int gx = static_cast<int>(std::floor(x));

    if (gx < 0 || gx >= (int)m_grid[gy].size()) {
        return false;
    }

    int tileType = m_grid[gy][gx];

    if (tileType == 3 || tileType == 4) {
        return false;
    }

    return true;
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

void Map::draw(sf::RenderWindow& window, sf::Vector2f playerGridPos) {
    if (m_grid.empty()) return;

    const float HALF_WIDTH = 32.f;
    const float HALF_HEIGHT = 24.f;
    const float OFFSET_X = 900.f;
    const float OFFSET_Y = 200.f;

    int startY = (int)playerGridPos.y - 40;
    int endY = (int)playerGridPos.y + 20;

    for (int y = startY; y <= endY; ++y) {
        int gridY = (y % (int)m_grid.size() + (int)m_grid.size()) % (int)m_grid.size();

        for (int x = 0; x < (int)m_grid[gridY].size(); ++x) {

            int type = m_grid[gridY][x];
            if (type > 48) type -= 48; 

            if (type == 0 || type == 3 || type == 4) m_tileSprite.setTexture(m_texGrass, true);
            else if (type == 1) m_tileSprite.setTexture(m_texRail, true);
            else if (type == 2) m_tileSprite.setTexture(m_texWater, true);
            else if (type == 6) m_tileSprite.setTexture(m_texRoad, true);

            m_tileSprite.setOrigin({ 32.f, 32.f });

            float isoX = (x - (float)y) * HALF_WIDTH + OFFSET_X;
            float isoY = (x + (float)y) * HALF_HEIGHT + OFFSET_Y;

            m_tileSprite.setPosition({ isoX, isoY });
            window.draw(m_tileSprite);

            if (type == 3) {
                int fixedRandom = std::abs(x + y * 31) % 3;
                if (fixedRandom == 0) m_tileSprite.setTexture(m_texTree, true);
                else if (fixedRandom == 1) m_tileSprite.setTexture(m_texTree2, true);
                else m_tileSprite.setTexture(m_texTree3, true);
                m_tileSprite.setOrigin({ 32.f, 64.f });
                window.draw(m_tileSprite);
            }
            if (type == 4) {
                m_tileSprite.setTexture(m_texgrave, true);
                m_tileSprite.setOrigin({ 32.f, 48.f });
                window.draw(m_tileSprite);
            }
        }
    }
}