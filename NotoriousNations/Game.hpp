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
	Window wndw_window;

	sf::Sprite sprt_corners[4];
	sf::Sprite sprt_edges[2];
	sf::Sprite sprt_cursors;
	sf::Sprite sprt_soilcovers;

	sf::Clock clck_clock;

	float f_delta_time;

	float f_buffer_size = 8.0f;
};

#endif