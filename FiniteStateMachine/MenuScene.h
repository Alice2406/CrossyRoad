#pragma once
#include "Scene.h"

class MenuScene :public Scene
{
public:
	MenuScene();

	virtual ~MenuScene() = default;

	void handleInput(sf::RenderWindow& Window) override;
	void update(float dt) override;
	void draw(sf::RenderWindow& Window) override;
	//virtual void Destroy();

	bool goToSkin = false; 

private:
	sf::Font font;
	sf::Text title;
	sf::RectangleShape skinButton;
	sf::Text skinButtonText;

	bool gameStarted = false;
};



