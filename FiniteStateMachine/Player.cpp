#include "Player.h"

Player::Player()
    : m_step(80.f)
    , m_health(100)
{
    m_shape.setSize({ 64.f, 64.f });
    m_shape.setFillColor(sf::Color::White);
    m_shape.setOrigin(m_shape.getSize() / 2.f);
}

void Player::update()
{
    bool anyKey = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        anyKey = true;
        if (!m_moveLocked)
        {
            m_shape.move({ 0.f, -m_step });
            m_moveLocked = true;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        anyKey = true;
        if (!m_moveLocked)
        {
            m_shape.move({ 0.f, m_step });
            m_moveLocked = true;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        anyKey = true;
        if (!m_moveLocked)
        {
            m_shape.move({ -m_step, 0.f });
            m_moveLocked = true;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        anyKey = true;
        if (!m_moveLocked)
        {
            m_shape.move({ m_step, 0.f });
            m_moveLocked = true;
        }
    }

    if (!anyKey)
        m_moveLocked = false;
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(m_shape);
}

void Player::spawn(const sf::Vector2f& position)
{
    m_shape.setPosition(position);
}

sf::Vector2f Player::getPosition() const
{
    return m_shape.getPosition();
}