#include "SkinScene.h"
#include <iostream>

SkinScene::SkinScene()
    : font(),
    chickenTexture(), 
    backButtonIcon(chickenTexture), 
    skinNameText(font, "MISTER ?"),
    counterText(font, "1/12")
{
   
    if (!font.openFromFile("Assets/Arial.ttf")) {
        std::cerr << "Erreur : Police introuvable" << std::endl;
    }

    if (!chickenTexture.loadFromFile("Assets/image.png")) {
        std::cerr << "Erreur : image.png introuvable" << std::endl;
    }

   
    backButtonRect.setSize({ 80.f, 80.f });
    backButtonRect.setFillColor(sf::Color(100, 200, 255));
    backButtonRect.setPosition({ 20.f, 20.f });

   
    backButtonIcon.setTexture(chickenTexture);
    
    backButtonIcon.setScale({ 0.5f, 0.5f });
    backButtonIcon.setPosition({ 30.f, 30.f });

   
    playButton.setSize({ 250.f, 100.f });
    playButton.setFillColor(sf::Color(100, 200, 255));
    playButton.setPosition({ 900.f - 125.f, 750.f });

    skinNameText.setCharacterSize(60);
    skinNameText.setFillColor(sf::Color::White);
    skinNameText.setPosition({ 900.f - 100.f, 100.f });

    counterText.setCharacterSize(40);
    counterText.setFillColor(sf::Color::White);
    counterText.setPosition({ 20.f, 840.f });

    for (int i = 0; i < 12; ++i) {
        skins.emplace_back(chickenTexture);
        skins.back().setOrigin(skins.back().getLocalBounds().getCenter());
    }
}

void SkinScene::handleInput(sf::RenderWindow& window) {
    static bool mouseWasReleased = false;
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        mouseWasReleased = true;
    }

    if (mouseWasReleased && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

       
        if (backButtonRect.getGlobalBounds().contains(mousePos)) {
            backToMenu = true;
            mouseWasReleased = false;
        }
    }

  
    static bool keyReleased = true;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && keyReleased) {
        if (currentIndex < (int)skins.size() - 1) currentIndex++;
        keyReleased = false;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && keyReleased) {
        if (currentIndex > 0) currentIndex--;
        keyReleased = false;
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        keyReleased = true;
    }
}

void SkinScene::update(float dt) {
    targetOffset = currentIndex * -300.f;
    currentOffset += (targetOffset - currentOffset) * 10.f * dt;

    for (int i = 0; i < (int)skins.size(); ++i) {
        float x = 900.f + (i * 300.f) + currentOffset;
        skins[i].setPosition({ x, 450.f });
        if (i == currentIndex) {
            skins[i].setScale({ 3.0f, 3.0f });
            skins[i].setColor(sf::Color::White);
        }
        else {
            skins[i].setScale({ 1.5f, 1.5f });
            skins[i].setColor(sf::Color(100, 100, 100, 200));
        }
    }
    counterText.setString(std::to_string(currentIndex + 1) + " / " + std::to_string(skins.size()));
}

void SkinScene::draw(sf::RenderWindow& window) {
    window.clear(sf::Color(135, 206, 235));

   
    window.draw(backButtonRect);
    window.draw(backButtonIcon);

    window.draw(playButton);
    window.draw(skinNameText);
    window.draw(counterText);
    for (auto& s : skins) window.draw(s);
}