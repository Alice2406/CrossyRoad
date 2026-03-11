#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Obstacle.h"
#include <iostream>


int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1800, 900 }), " ");
    window.setFramerateLimit(60);
    sf::View view(sf::FloatRect({ 0.f, 0.f }, { 1800.f, 900.f }));

    std::vector<Obstacle> obstacles;

    sf::Clock clock;
    sf::Clock spawnClock;
    float spawnInterval = 2.0f;

    Player player;
    player.spawn({ 290.f, 777.f });
    obstacles.push_back(Obstacle({ -84.f, -323.f }, 200.f));
    obstacles.push_back(Obstacle({ -20.f, -223.f }, 150.f));
    while (window.isOpen())
    {
		float dt = clock.restart().asSeconds();
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        player.update();
        sf::Vector2f playerPos = player.getPosition();

        float isoX = (player.getPosition().x - player.getPosition().y);
        float isoY = (player.getPosition().x + player.getPosition().y) * 0.5f;

        float verticalOffset = 200.f;
		float horizontalOffset = 400.f;

        view.setCenter({ isoX + 900.f + horizontalOffset, isoY + 200.f - verticalOffset });

        window.setView(view);
        if (spawnClock.getElapsedTime().asSeconds() >= spawnInterval)
        {
            obstacles.push_back(Obstacle({ -84.f, -323.f }, 200.f));
            obstacles.push_back(Obstacle({ -20.f, -223.f }, 150.f));
            spawnClock.restart();
        }
        for (auto& obs : obstacles) {
            sf::Vector2f diff = player.getPosition() - obs.getPosition();
            float distanceSquared = diff.x * diff.x + diff.y * diff.y;

            if (distanceSquared < 2500.f) {
                std::cout << "MORT ! Collision detectee." << std::endl;
                player.spawn({ 290.f, 777.f });
            }
        }
        for (auto it = obstacles.begin(); it != obstacles.end(); )
        {
            it->update(dt);
            if (it->getPosition().x > 2500.f) {
                it = obstacles.erase(it);
            }
            else {
                ++it;
            }
        }
        window.clear(sf::Color(0, 0, 0));
        for (auto& obs : obstacles) obs.draw(window);
//		std::cout << "Player position: " << player.getPosition().x << ", " << player.getPosition().y << std::endl;
        player.draw(window);
        window.display();
    }
    return 0;
}