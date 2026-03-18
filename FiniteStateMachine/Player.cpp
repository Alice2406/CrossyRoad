#include "Player.h"
#include <iostream>

Player::Player()
    : m_step(40.f),
    m_sprite(m_texture),
    m_frameCount(8),     
    m_frameTime(0.005f),  
    m_elapsedTime(0.f),
    m_currentFrame(0),
    m_frameSize(66, 66)
{
    if (!m_texture.loadFromFile("../Asset/spritesheet.png")) {
        std::cout << "ERREUR : PlayerAnim.png introuvable !" << std::endl;
    }

    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(sf::IntRect({ 0, 0 }, m_frameSize));

    auto bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin({ bounds.size.x / 2.f, bounds.size.y });
}

sf::FloatRect Player::getGridBounds() const {
    return sf::FloatRect({ m_gridPos.x - 0.2f, m_gridPos.y - 0.2f }, { 0.4f, 0.4f });
}

sf::Vector2f Player::getIsoPosition() const {
    const float HALF_WIDTH = 32.f;
    const float HALF_HEIGHT = 24.f;
    const float OFFSET_X = 900.f;
    const float OFFSET_Y = 200.f;

    float isoX = (m_gridPos.x - m_gridPos.y) * HALF_WIDTH + OFFSET_X;
    float isoY = (m_gridPos.x + m_gridPos.y) * HALF_HEIGHT + OFFSET_Y;
    return { isoX, isoY };
}

void Player::update(float dt, Map& map)
{

    if (m_ghostTimer > 0.f) {
        m_ghostTimer -= dt;
    }
    bool anyKey = false;
    sf::Vector2f moveVec(0.f, 0.f);
    sf::Vector2f gridDir(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        moveVec = { -8.f, -m_step };
        gridDir = { 0.f, -1.f };
        anyKey = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        moveVec = { 8.f, m_step };
        gridDir = { 0.f, 1.f };
        anyKey = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        moveVec = { -m_step, -8.f };
        gridDir = { -1.f, 0.f };
        anyKey = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        moveVec = { m_step, 8.f };
        gridDir = { 1.f, 0.f };
        anyKey = true;
    }
    if (m_moveLocked) {
        m_elapsedTime += dt;
        if (m_elapsedTime >= m_frameTime) {
            m_elapsedTime = 0.f;
            m_currentFrame = (m_currentFrame + 1) % m_frameCount;
        }
    }
    else {
        m_currentFrame = 0; 
    }

    m_sprite.setTextureRect(sf::IntRect(
        { m_currentFrame * m_frameSize.x, 0 },
        m_frameSize
    ));

    if (anyKey && !m_moveLocked) {
        sf::Vector2f nextGridPos = m_gridPos + gridDir;
        if (map.isWalkable(nextGridPos.x, nextGridPos.y)) {
            m_basePos += moveVec;
            m_gridPos = nextGridPos;
        }
        m_moveLocked = true;
    }

    if (!anyKey) m_moveLocked = false;
}
void Player::draw(sf::RenderWindow& window) {
    m_sprite.setPosition(getIsoPosition());

    if (this->isInvisible()) {
       
        m_sprite.setColor(sf::Color(100, 150, 255, 150));

       
    }
    else if (this->isInvincible()) {
     
        m_sprite.setColor(sf::Color(255, 200, 200, 100));
    }
    else {
        // --- ÉTAT NORMAL ---
        m_sprite.setColor(sf::Color::White); // Couleur d'origine
    }

    window.draw(m_sprite);
}

void Player::spawn(const sf::Vector2f& gridPosition) {

    m_gridPos = gridPosition;
    m_basePos = getIsoPosition();
}

sf::Vector2f Player::getPosition() const {
    return m_basePos;
}