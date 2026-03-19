#pragma once
#include "Scene.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class GameOverScene : public Scene {
public:
    GameOverScene(int finalScore);
    void handleInput(sf::RenderWindow& window) override;
    void update(float dt, sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;
    void setFinalScore(int score);
    bool shouldLoadGame = false;
    bool shouldQuit = false;

private:
    sf::Font font;
    sf::Text loadText;
    sf::Text quitText;

    sf::Text scoreText; 
    int finalScore = 0;
    sf::Texture texBg, texTitle;
    sf::Sprite sprBg, sprTitle;

    sf::SoundBuffer clickBuffer;
    sf::Sound clickSound;
    sf::SoundBuffer m_hoverBuffer;
    sf::Sound m_hoverSound;

	float totalTime = 0.f;
    bool mouseWasPressed = false;

    bool m_wasHoveringLoad = false;
    bool m_wasHoveringQuit = false;
};