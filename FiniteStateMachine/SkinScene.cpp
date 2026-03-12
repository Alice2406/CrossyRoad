#include "SkinScene.h"
#include <iostream>

SkinScene::SkinScene()
    : font(),
    skinNameText(font, "FESTIVE CHICKEN"),
    counterText(font, "1/3")
{
    font.openFromFile("Assets/Arial.ttf");


    if (!chickenTexture.loadFromFile("Assets/chicken.png")) {
        std::cerr << "Note: chicken.png manquant, utilise des placeholders" << std::endl;
    }


    backButton.setSize({ 80.f, 80.f });
    backButton.setFillColor(sf::Color(100, 200, 255));
    backButton.setPosition({ 20.f, 20.f });

    playButton.setSize({ 250.f, 100.f });
    playButton.setFillColor(sf::Color(100, 200, 255));
    playButton.setPosition({ 900.f - 125.f, 750.f });


    skinNameText.setCharacterSize(60);
    skinNameText.setFillColor(sf::Color::White);
    skinNameText.setPosition({ 900.f - skinNameText.getGlobalBounds().size.x / 2.f, 100.f });


    for (int i = 0; i < 3; ++i) {
        sf::Sprite s(chickenTexture);
        s.setOrigin(s.getLocalBounds().getCenter());
        skins.push_back(s);
    }
}

void SkinScene::handleInput(sf::RenderWindow& window) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

        if (backButton.getGlobalBounds().contains(mousePos)) {
            backToMenu = true;
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
    window.draw(backButton);
    window.draw(playButton);
    window.draw(skinNameText);
    window.draw(counterText);
    for (auto& s : skins) window.draw(s);
}