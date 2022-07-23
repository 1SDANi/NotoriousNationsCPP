#pragma once
#ifndef Game_hpp
#define Game_hpp

#include "Window.hpp"
#include "Globals.hpp"
#include "Controller.hpp"

#include "Assets/Menu.hpp"

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

	sf::Clock clck_clock;

	Menu menu;

	float f_delta_time;

	float f_buffer_size = 8.0f;

	sf::Sprite sprt_soilcovers;
};

#endif