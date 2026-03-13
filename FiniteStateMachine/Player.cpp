#include "Player.h"
#include <iostream>

Player::Player() : m_step(40.f), m_sprite(m_texDown)
{
    if (!m_texUp.loadFromFile("../Asset/Up.png")) { std::cout << "ERREUR : Impossible de trouver player_down.png" << std::endl; }
    if (!m_texDown.loadFromFile("../Asset/Down.png")) { std::cout << "ERREUR : Impossible de trouver player_down.png" << std::endl; }
    if (!m_texLeft.loadFromFile("../Asset/Left.png")) { std::cout << "ERREUR : Impossible de trouver player_down.png" << std::endl; }
    if (!m_texRight.loadFromFile("../Asset/Right.png")) { std::cout << "ERREUR : Impossible de trouver player_down.png" << std::endl; }

    m_sprite.setTexture(m_texDown, true);

    auto texSize = m_texDown.getSize();
    m_sprite.setTextureRect(sf::IntRect({ 0, 0 }, { (int)texSize.x, (int)texSize.y }));

    auto bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
    m_sprite.setScale({ 1.f, 1.f });
    m_sprite.setColor(sf::Color::White);
}

sf::Vector2f Player::getIsoPosition() const {
    sf::Vector2f pos = m_sprite.getPosition();
    float isoX = (pos.x - pos.y);
    float isoY = (pos.x + pos.y) * 0.5f;
    return { isoX + 900.f, isoY + 200.f };
}

void Player::update()
{
    bool anyKey = false;
    sf::Vector2f moveVec(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        moveVec = { -8.f, -m_step };
        m_sprite.setTexture(m_texUp, true);
        auto size = m_texUp.getSize();
        m_sprite.setTextureRect(sf::IntRect({ 0, 0 }, { (int)size.x, (int)size.y }));
        anyKey = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        moveVec = {8.f, m_step };
        m_sprite.setTexture(m_texDown);
        anyKey = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        moveVec = { -m_step, -8.f };
        m_sprite.setTexture(m_texLeft);
        anyKey = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        moveVec = { m_step, 8.f };
        m_sprite.setTexture(m_texRight);
        anyKey = true;
    }

    if (anyKey && !m_moveLocked) {
        m_sprite.move(moveVec);
        m_moveLocked = true;
    }
    if (!anyKey) m_moveLocked = false;
}

void Player::draw(sf::RenderWindow& window) {
    sf::Vector2f logicalPos = m_sprite.getPosition();

    m_sprite.setPosition(getIsoPosition());

    window.draw(m_sprite);
    m_sprite.setPosition(logicalPos);
}

void Player::spawn(const sf::Vector2f& position)
{
    m_shape.setPosition(position);
}

sf::Vector2f Player::getPosition() const
{
    return m_shape.getPosition();
}

