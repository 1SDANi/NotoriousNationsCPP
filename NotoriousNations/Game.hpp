#pragma once
#ifndef Game_hpp
#define Game_hpp

#include "Window.hpp"
#include "Globals.hpp"
#include "Controller.hpp"

#include <iostream>

class Game
{

public:
	Game();

	void update();

	void late_update();

	void draw();

	void update_delta_time();

	bool b_is_running() const;

private:
	Window window;

	sf::Texture testTexture;
	sf::Sprite testSprite;
	sf::Clock clock;

	float f_delta_time;
};

#endif