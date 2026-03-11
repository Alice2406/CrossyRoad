#include "MenuScene.h"
#include "Scene.h"
#include <iostream>

MenuScene::MenuScene()
    : font(),
    title(font, "CROSSY ROAD"),
    gameStarted(false)  
{
    if (!font.openFromFile("Assets\\Arial.ttf"))
    {
        std::cerr << "Erreur : impossible de charger la police !" << std::endl;
    }
    title.setFont(font);
    title.setString("CROSSY ROAD");


    title.setCharacterSize(100);
    title.setFillColor(sf::Color::Black);
    title.setPosition({ 900.f - title.getGlobalBounds().size.x / 2.f, 350.f });

}
void MenuScene::handleInput(sf::RenderWindow& window) {
   
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
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
   
}