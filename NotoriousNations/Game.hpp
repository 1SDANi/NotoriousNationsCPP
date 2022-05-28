#pragma once
#ifndef Game_hpp
#define Game_hpp

#include "Window.hpp"
#include "Globals.hpp"

class Game
{

public:
	Game();

	void update();
	void late_update();
	void draw();

	bool b_is_running() const;

private:
	Window window;

	sf::Texture testTexture;
	sf::Sprite testSprite;
};

#endif