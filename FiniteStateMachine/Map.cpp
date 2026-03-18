#include "Map.h"
#include <iostream>
#include <fstream>
#include <sstream>

Map::Map() : m_tileSprite(m_texGrass) {

    if (!m_texGrass.loadFromFile("../Asset/grass2.png") ||
        !m_texRoad.loadFromFile("../Asset/rails.png") ||
        !m_texTree.loadFromFile("../Asset/arbre.png") ||
        !m_texTree2.loadFromFile("../Asset/arbre2.png") ||
        !m_texTree3.loadFromFile("../Asset/arbre3.png") ||
        !m_texgrave.loadFromFile("../Asset/tombe22.png") ||
        !m_texWater.loadFromFile("../Asset/water2.png") ||
        !m_texPowerUp.loadFromFile("../Asset/PowerUp.png"))
    {
        std::cerr << "Erreur : Impossible de charger une ou plusieurs textures !" << std::endl;
    }

    m_tileSprite.setOrigin({ 32.f, 32.f });
}

bool Map::isWalkable(float x, float y) {
    int gx = static_cast<int>(x);
    int gy = static_cast<int>(y);

    if (gy < 0 || gy >= (int)m_grid.size() || gx < 0 || gx >= (int)m_grid[0].size()) {
        return false;
    }

    int tileType = m_grid[gy][gx];

    if (tileType == 3 || tileType == 4) {
        return false;
    }

    return true;
}

bool Map::isWater(float x, float y) const {
    int gx = static_cast<int>(x);
    int gy = static_cast<int>(y);

    // Sécurité limites
    if (gy < 0 || gy >= (int)m_grid.size() || gx < 0 || gx >= (int)m_grid[0].size()) {
        return false;
    }

    // Si le type est 5, c'est de l'eau !
    return (m_grid[gy][gx] == 2);
}

void Map::loadFromFile(const std::string& filename)
{
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

    const float HALF_WIDTH = 32.f;
    const float HALF_HEIGHT = 24.f;
    const float OFFSET_X = 900.f;
    const float OFFSET_Y = 200.f;

    for (int y = 0; y < (int)m_grid.size(); ++y) {
        for (int x = 0; x < (int)m_grid[y].size(); ++x) {

            int type = m_grid[y][x];

            // --- 1. CHOIX DU SOL ---
            // On ajoute "type == 5" ici pour dessiner de l'herbe sous le bonus
            if (type == 0 || type == 3 || type == 4 || type == 5)
                m_tileSprite.setTexture(m_texGrass, true);
            else if (type == 1)
                m_tileSprite.setTexture(m_texRoad, true);
            else if (type == 2)
                m_tileSprite.setTexture(m_texWater, true);

            m_tileSprite.setOrigin({ 32.f, 32.f });

            float isoX = (x - y) * HALF_WIDTH;
            float isoY = (x + y) * HALF_HEIGHT;

            m_tileSprite.setPosition({ isoX + OFFSET_X, isoY + OFFSET_Y });

            // On dessine le sol (herbe, route ou eau)
            window.draw(m_tileSprite);

            // --- 2. DESSIN DES OBJETS (Par-dessus le sol) ---

            if (type == 3) { // Arbres
                int fixedRandom = (x + y * 31) % 3;
                if (fixedRandom == 0)      m_tileSprite.setTexture(m_texTree, true);
                else if (fixedRandom == 1) m_tileSprite.setTexture(m_texTree2, true);
                else                       m_tileSprite.setTexture(m_texTree3, true);

                m_tileSprite.setOrigin({ 32.f, 64.f });
                window.draw(m_tileSprite);
            }

            if (type == 4) { // Tombes
                m_tileSprite.setTexture(m_texgrave, true);
                m_tileSprite.setOrigin({ 32.f, 48.f });
                window.draw(m_tileSprite);
            }

            if (type == 5) { // PowerUp
                m_tileSprite.setTexture(m_texPowerUp, true);
                m_tileSprite.setOrigin({ 32.f, 48.f });
                // Pas besoin de changer setPosition car isoX/isoY sont déjà bons
                window.draw(m_tileSprite);
            }
        }
    }
}