#include "Player.h"
#include <iostream>

Player::Player() : m_step(32.f), m_sprite(m_texDown)
{
    if (!m_texUp.loadFromFile("../Asset/Up.png")) { std::cout << "ERREUR : Up.png" << std::endl; }
    if (!m_texDown.loadFromFile("../Asset/Down.png")) { std::cout << "ERREUR : Down.png" << std::endl; }
    if (!m_texLeft.loadFromFile("../Asset/Left.png")) { std::cout << "ERREUR : Left.png" << std::endl; }
    if (!m_texRight.loadFromFile("../Asset/Right.png")) { std::cout << "ERREUR : Right.png" << std::endl; }

    m_sprite.setTexture(m_texDown, true);
    auto texSize = m_texDown.getSize();
    m_sprite.setTextureRect(sf::IntRect({ 0, 0 }, { (int)texSize.x, (int)texSize.y }));

    auto bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
}

sf::Vector2f Player::getIsoPosition() const {
    float isoX = (m_basePos.x - m_basePos.y) + 900.f;
    float isoY = (m_basePos.x + m_basePos.y) * 0.5f + 200.f;
    return { isoX, isoY };
}

void Player::update()
{
    bool anyKey = false;
    sf::Vector2f moveVec(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        moveVec = { 0.f, -m_step };
        m_sprite.setTexture(m_texUp, true);
        anyKey = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        moveVec = { 0.f, m_step };
        m_sprite.setTexture(m_texDown, true);
        anyKey = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        moveVec = { -m_step, 0.f };
        m_sprite.setTexture(m_texLeft, true);
        anyKey = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        moveVec = { m_step, 0.f };
        m_sprite.setTexture(m_texRight, true);
        anyKey = true;
    }

    if (anyKey && !m_moveLocked) {
        m_basePos += moveVec;
        m_moveLocked = true;
    }
    if (!anyKey) m_moveLocked = false;
}

void Player::draw(sf::RenderWindow& window) {
    m_sprite.setPosition(getIsoPosition());
    window.draw(m_sprite);
}

void Player::spawn(const sf::Vector2f& position)
{
    m_basePos = position;
}

sf::Vector2f Player::getPosition() const
{
    return m_basePos;
}