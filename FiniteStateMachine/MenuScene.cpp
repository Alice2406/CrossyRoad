#include "MenuScene.h"
#include <iostream>

MenuScene::MenuScene()
    : font(),
    title(font, "CROSSY ROAD"),
    skinButtonText(font, "SKINS")
{
    if (!font.openFromFile("Assets/Arial.ttf")) {
        std::cerr << "Erreur : impossible de charger la police !" << std::endl;
    }

    title.setCharacterSize(100);
    title.setFillColor(sf::Color::Black);
    title.setPosition({ 900.f - title.getGlobalBounds().size.x / 2.f, 300.f });


    skinButton.setSize({ 200.f, 60.f });
    skinButton.setFillColor(sf::Color::Blue);
    skinButton.setPosition({ 50.f, 750.f });

    skinButtonText.setCharacterSize(30);
    skinButtonText.setFillColor(sf::Color::White);

    sf::FloatRect textBounds = skinButtonText.getGlobalBounds();
    skinButtonText.setPosition({
        skinButton.getPosition().x + (200.f - textBounds.size.x) / 2.f,
        skinButton.getPosition().y + (60.f - textBounds.size.y) / 2.f
        });
}

void MenuScene::handleInput(sf::RenderWindow& window) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
        if (skinButton.getGlobalBounds().contains(mousePos)) {
            goToSkin = true;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
        gameStarted = true;
    }
}

void MenuScene::update(float dt) {
    if (gameStarted) {
        title.move({ -1500.f * dt, 0.f });
    }
}

void MenuScene::draw(sf::RenderWindow& window) {
    window.draw(title);
    window.draw(skinButton);
    window.draw(skinButtonText);
}