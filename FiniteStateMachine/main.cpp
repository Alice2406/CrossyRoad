#include <SFML/Graphics.hpp>
#include "GameScene.h"
#include <iostream>


int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1800, 900 }), "Crossy Isometric");
    window.setFramerateLimit(60);

    sf::Clock dtClock;
    GameScene gameScene; 

    while (window.isOpen())
    {
        float dt = dtClock.restart().asSeconds(); 

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        gameScene.update(dt, window);

        window.clear();
        gameScene.draw(window);
        window.display();
    }
    return 0;
}