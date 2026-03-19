#include "MenuScene.h"
#include <iostream>
#include <cmath>

MenuScene::MenuScene()
    : font(),
    backgroundTex(),
    backgroundSprite(backgroundTex),
    title(font, "THE ONLY ROAD"),
    playText(font, "START"),
    skinText(font, "SKINS"),
    quitText(font, "QUIT"),
    m_clickSound(m_clickBuffer),
    m_hoverSound(m_hoverBuffer)
{
    if (!backgroundTex.loadFromFile("../Asset/brume.png")) std::cerr << "Erreur : brume.png" << std::endl;
    backgroundSprite.setTexture(backgroundTex, true);
    backgroundSprite.setScale({ 1800.f / backgroundTex.getSize().x, 900.f / backgroundTex.getSize().y });

    if (!font.openFromFile("../Asset/Thunder.ttf")) std::cerr << "Erreur : font" << std::endl;

    if (!m_clickBuffer.loadFromFile("../Asset/click.mp3")) {
		std::cerr << "Erreur : click.mp3" << std::endl;
    }
    else {
        m_clickSound.setVolume(50.f);
    }

    if (!m_hoverBuffer.loadFromFile("../Asset/hover.mp3")) {
        std::cerr << "Erreur : hover.mp3" << std::endl;
    }
    else {
        m_hoverSound.setVolume(30.f);
    }

    title.setCharacterSize(120);
    title.setFillColor(sf::Color(150, 0, 0));
    title.setPosition({ 900.f - title.getGlobalBounds().size.x / 2.f, 150.f });

    auto setupBtn = [&](sf::RectangleShape& shape, sf::Text& text, float yPos) {
        shape.setSize({ 300.f, 60.f });
        shape.setFillColor(sf::Color(20, 20, 20, 50));
        shape.setOutlineThickness(2.f);
        shape.setOutlineColor(sf::Color(80, 0, 0));
        shape.setPosition({ 900.f - 150.f, yPos });
        text.setCharacterSize(30);
        text.setFillColor(sf::Color(180, 0, 0));
        sf::FloatRect bounds = text.getGlobalBounds();
        text.setPosition({ shape.getPosition().x + (300.f - bounds.size.x) / 2.f, shape.getPosition().y + (60.f - bounds.size.y) / 2.f - 5.f });
    };

    setupBtn(playBtn, playText, 400.f);
    setupBtn(skinBtn, skinText, 500.f);
    setupBtn(quitBtn, quitText, 600.f);
}

void MenuScene::handleInput(sf::RenderWindow& window) {}

void MenuScene::update(float dt, sf::RenderWindow& window) {
    totalTime += dt;
    float shake = std::sin(totalTime * 25.f) * 2.f;
    title.setPosition({ 900.f - title.getGlobalBounds().size.x / 2.f + shake, 150.f });

    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    static bool mouseWasPressed = false;

    auto handleBtn = [&](sf::RectangleShape& b, bool& trigger, bool& isHoveringState) {
        if (b.getGlobalBounds().contains(mousePos)) {
            b.setOutlineColor(sf::Color::Red);
            if (!isHoveringState) {
                m_hoverSound.play();
                isHoveringState = true;
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !mouseWasPressed) {
                m_clickSound.play();
                trigger = true;
            }
        }
        else {
            b.setOutlineColor(sf::Color(80, 0, 0));
            isHoveringState = false;
        }
    };

    handleBtn(playBtn, gameStarted, m_wasHoveringPlay);
    handleBtn(skinBtn, goToSkin, m_wasHoveringSkin);
    handleBtn(quitBtn, quitGame, m_wasHoveringQuit);
    mouseWasPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

void MenuScene::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    window.draw(title);
    window.draw(playBtn); window.draw(playText);
    window.draw(skinBtn); window.draw(skinText);
    window.draw(quitBtn); window.draw(quitText);
}