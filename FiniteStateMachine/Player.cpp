#include "Player.h"

Player::Player()
    : m_step(50.f)
    , m_health(100)
{
    m_shape.setSize({ 50.f, 50.f });
    m_shape.setFillColor(sf::Color::White);
    m_shape.setOrigin(m_shape.getSize() / 2.f);
}

void Player::update()
{
    bool anyKey = false;
    sf::Vector2f moveVec(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        moveVec = { -17.f, -m_step }; 
        anyKey = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        moveVec = { 17.f, m_step }; 
        anyKey = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        moveVec = { -m_step, -17.f }; 
        anyKey = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        moveVec = { m_step, 17.f }; 
        anyKey = true;
    }

    if (anyKey && !m_moveLocked) {
        m_shape.move(moveVec);
        m_moveLocked = true;
    }
    if (!anyKey) m_moveLocked = false;
}

void Player::draw(sf::RenderWindow& window)
{
    sf::Vector2f pos = m_shape.getPosition();

    float isoX = (pos.x - pos.y);
    float isoY = (pos.x + pos.y) * 0.5f;

    sf::Vector2f originalPos = m_shape.getPosition();
    float originalRotation = m_shape.getRotation().asDegrees();

    m_shape.setPosition({ isoX + 900.f, isoY + 200.f });
    m_shape.setRotation(sf::degrees(45.f));
    m_shape.setScale({ 1.f, 1.f });    

    window.draw(m_shape);

    m_shape.setPosition(originalPos);
    m_shape.setRotation(sf::degrees(originalRotation));
}

void Player::spawn(const sf::Vector2f& position)
{
    m_shape.setPosition(position);
}

sf::Vector2f Player::getPosition() const
{
    return m_shape.getPosition();
}