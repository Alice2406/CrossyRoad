#include "GameOverScene.h"
#include <iostream>

GameOverScene::GameOverScene()
    : sprBg(texBg), sprTitle(texTitle),
    loadText(font, "LOAD GAME", 60),
    quitText(font, "QUIT", 60)
{
    if (!texBg.loadFromFile("../Asset/brume.png")) std::cerr << "Erreur : brume.png" << std::endl;
    if (!texTitle.loadFromFile("../Asset/youaredead.png")) std::cerr << "Erreur : title.png" << std::endl;
    if (!font.openFromFile("../Asset/Thunder.ttf")) std::cerr << "Erreur : font" << std::endl;

    sprBg.setTexture(texBg, true);
    sprBg.setScale({ 1800.f / texBg.getSize().x, 900.f / texBg.getSize().y });

    sprTitle.setTexture(texTitle, true);
    sprTitle.setScale({ 1.5f, 1.5f });

    sprTitle.setPosition({ 900.f - sprTitle.getGlobalBounds().size.x / 2.f, 100.f });

    auto setupText = [&](sf::Text& t, const std::string& str, float yPos) {
        t.setFont(font);
        t.setString(str);
        t.setCharacterSize(60);
        t.setFillColor(sf::Color::White);
        sf::FloatRect bounds = t.getGlobalBounds();
        t.setPosition({ 900.f - bounds.size.x / 2.f, yPos });
        };

    setupText(loadText, "LOAD GAME", 500.f);
    setupText(quitText, "QUIT", 650.f);
}

void GameOverScene::update(float dt, sf::RenderWindow& window) {
    totalTime += dt;
    float shake = std::sin(totalTime * 20.f) * 1.5f;

    // Effet clignotement titre
    if (std::rand() % 100 > 95)
        sprTitle.setColor(sf::Color(40, 0, 0));
    else
        sprTitle.setColor(sf::Color::White);

    sprTitle.setPosition({ 900.f - sprTitle.getGlobalBounds().size.x / 2.f + shake, 100.f });

    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    // Définition des couleurs
    sf::Color bordeaux(80, 0, 0);
    sf::Color lightGray(180, 180, 180); // On définit le gris ici

    auto handleHover = [&](sf::Text& t, bool& trigger) {
        if (t.getGlobalBounds().contains(mousePos)) {
            t.setFillColor(bordeaux);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !mouseWasPressed) {
                trigger = true;
            }
        }
        else {
            t.setFillColor(lightGray); // C'est ici qu'on met le gris par défaut !
        }
        };

    // Maintenant les appels fonctionnent car handleHover gère les deux états
    handleHover(loadText, shouldLoadGame);
    handleHover(quitText, shouldQuit);

    // SUPPRIME LES LIGNES ICI qui forçaient loadText et quitText en gris !

    mouseWasPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

void GameOverScene::draw(sf::RenderWindow& window) {
    window.draw(sprBg);
    window.draw(sprTitle);
    window.draw(loadText);
    window.draw(quitText);
}

void GameOverScene::handleInput(sf::RenderWindow& window) {}