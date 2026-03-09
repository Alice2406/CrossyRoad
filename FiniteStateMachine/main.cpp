#include <SFML/Graphics.hpp>
#include "Player.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1800, 900 }), " ");
    window.setFramerateLimit(60);

    Player player;
    player.spawn({ 900.f, 700.f });

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        player.update();
        window.clear(sf::Color(0, 0, 0));
        player.draw(window);
        window.display();
    }
    return 0;
}