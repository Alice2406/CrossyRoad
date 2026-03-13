#include "SkinScene.h"
#include <iostream>
#include <cmath>

SkinScene::SkinScene()
    : font(),
    chickenTexture(),
    backButtonIcon(chickenTexture),
    skinNameText(font),
    counterText(font)
{
    if (!font.openFromFile("Assets/Arial.ttf")) {
        std::cerr << "Erreur : Police introuvable" << std::endl;
    }

    if (!chickenTexture.loadFromFile("Assets/image.png")) {
        std::cerr << "Erreur : image.png introuvable" << std::endl;
    }

   
    backButtonRect.setSize({ 80.f, 80.f });
    backButtonRect.setFillColor(sf::Color(40, 0, 0, 200));
    backButtonRect.setOutlineThickness(2.f);
    backButtonRect.setOutlineColor(sf::Color(100, 0, 0)); 
    backButtonRect.setPosition({ 20.f, 20.f });

    backButtonIcon.setTexture(chickenTexture);
    backButtonIcon.setScale({ 0.5f, 0.5f });
    backButtonIcon.setPosition({ 30.f, 30.f });
    backButtonIcon.setColor(sf::Color(150, 150, 150)); 

  
    playButton.setSize({ 250.f, 100.f });
    playButton.setFillColor(sf::Color(20, 20, 20)); 
    playButton.setOutlineThickness(3.f);
    playButton.setOutlineColor(sf::Color(138, 3, 3)); 
    playButton.setPosition({ 900.f - 125.f, 750.f });

    skinNameText.setString("PROCHAINE VICTIME ?");
    skinNameText.setCharacterSize(70);
    skinNameText.setFillColor(sf::Color(180, 0, 0)); 
    skinNameText.setOutlineThickness(2.f);
    skinNameText.setOutlineColor(sf::Color::Black);
   
    sf::FloatRect titleBounds = skinNameText.getGlobalBounds();
    skinNameText.setPosition({ 900.f - titleBounds.size.x / 2.f, 80.f });

  
    counterText.setCharacterSize(35);
    counterText.setFillColor(sf::Color(150, 150, 150, 180)); 
    counterText.setPosition({ 20.f, 850.f });

    for (int i = 0; i < 12; ++i) {
        skins.emplace_back(chickenTexture);
        sf::FloatRect bounds = skins.back().getLocalBounds();
        skins.back().setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
        skins.back().setColor(sf::Color(50, 50, 50)); 
    }
}

void SkinScene::handleInput(sf::RenderWindow& window) {
    
    sf::Vector2i mousePosI = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(mousePosI);

    static bool wasPressed = false;
    bool isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

    if (!isPressed && wasPressed) {
        if (backButtonRect.getGlobalBounds().contains(mousePos)) {
            backToMenu = true;
        }
    }
    wasPressed = isPressed;

    static bool keyReleased = true;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && keyReleased) {
        if (currentIndex < (int)skins.size() - 1) currentIndex++;
        keyReleased = false;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && keyReleased) {
        if (currentIndex > 0) currentIndex--;
        keyReleased = false;
    }

    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        keyReleased = true;
    }
}

void SkinScene::update(float dt, sf::RenderWindow& window) {
   
    targetOffset = currentIndex * -300.f;
    currentOffset += (targetOffset - currentOffset) * 10.f * dt;

    static float totalTime = 0.f;
    totalTime += dt;

  
    float titleShake = std::sin(totalTime * 20.f) * 2.f;
    skinNameText.move({ titleShake * dt, 0.f });

    for (int i = 0; i < (int)skins.size(); ++i) {
        float x = 900.f + (i * 300.f) + currentOffset;
        skins[i].setPosition({ x, 450.f });

        if (i == currentIndex) {
            
            skins[i].setScale({ 3.2f, 3.2f });
            int pulse = 200 + std::sin(totalTime * 10.f) * 55;
            skins[i].setColor(sf::Color(255, pulse, pulse)); 
        }
        else {
           
            skins[i].setScale({ 1.5f, 1.5f });
            skins[i].setColor(sf::Color(60, 0, 0, 180)); 
        }
    }
    counterText.setString(std::to_string(currentIndex + 1) + " / " + std::to_string(skins.size()));
}

void SkinScene::draw(sf::RenderWindow& window) {
    window.setView(window.getDefaultView());

   
    window.clear(sf::Color::Black);

   
    sf::RectangleShape bloodFloor({ 1800.f, 200.f });
    bloodFloor.setPosition({ 0.f, 700.f });
    bloodFloor.setFillColor(sf::Color(50, 0, 0, 150)); 
    window.draw(bloodFloor);

    window.draw(backButtonRect);
    window.draw(backButtonIcon);
    window.draw(playButton);
    window.draw(skinNameText);
    window.draw(counterText);

    for (auto& s : skins) {
        window.draw(s);
    }
}