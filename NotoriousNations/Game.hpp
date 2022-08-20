#pragma once
#ifndef Game_hpp
#define Game_hpp

#include "Window.hpp"
#include "Globals.hpp"
#include "Controller.hpp"

#include "Assets/Menu.hpp"

#include <iostream>
#include <memory>

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
	sf::Clock clck_clock;

	sf::Text text_text;

	sf::Font font_font;

	float f_delta_time;

	float f_buffer_size = 8.0f;

	std::shared_ptr<sf::Texture> p_txtr_cursor;

	//for some reason, the cursor doesn't want to draw if its code is in Camera.hpp/cpp
	sf::Sprite sprt_camera_cursor;

	sf::Sprite sprt_menu_cursor;
};

#endif