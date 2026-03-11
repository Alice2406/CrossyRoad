#pragma once
#include <SFML/Graphics.hpp>

class Scene
{
public:
	virtual ~Scene() = default;

	virtual void handleInput(sf::RenderWindow& Window) = 0;
	virtual void update(float dt, sf::RenderWindow& window) = 0;
	virtual void draw(sf::RenderWindow& Window) = 0;

};
	
