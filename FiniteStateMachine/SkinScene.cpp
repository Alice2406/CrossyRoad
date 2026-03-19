#include "SkinScene.h"
#include <iostream>

SkinScene::SkinScene(): backgroundSprite(backgroundTexture), backText(font)
{
    if (!font.openFromFile("../Asset/Thunder.ttf")) {
        std::cerr << "Erreur : Police introuvable" << std::endl;
    }

    if (!backgroundTexture.loadFromFile("../Asset/image.png")) {
        std::cerr << "Erreur : image.png introuvable" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture, true);
    sf::Vector2u texSize = backgroundTexture.getSize();
    backgroundSprite.setOrigin({ texSize.x / 2.f, texSize.y / 2.f });

    backgroundSprite.setPosition({ 900.f, 450.f });
    backgroundSprite.setScale({ 1.2f, 1.2f });
    backButtonRect.setSize({ 80.f, 80.f });
    backButtonRect.setFillColor(sf::Color(20, 20, 20, 0));
    backButtonRect.setPosition({ 20.f, 20.f });

    backText.setFont(font);
    backText.setString("<");
    backText.setCharacterSize(50);
    backText.setFillColor(sf::Color::White);
    backText.setPosition({ 40.f, 25.f });
}

void SkinScene::handleInput(sf::RenderWindow& window) {
    sf::Vector2i mousePosI = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(mousePosI);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        if (backButtonRect.getGlobalBounds().contains(mousePos)) {
            backToMenu = true;
        }
    }
}

void SkinScene::update(float dt, sf::RenderWindow& window) {
}

void SkinScene::draw(sf::RenderWindow& window) {
    window.setView(window.getDefaultView());

    window.draw(backgroundSprite);

    window.draw(backButtonRect);
    window.draw(backText);
}