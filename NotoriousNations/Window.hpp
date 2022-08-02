#pragma once
#ifndef Window_hpp
#define Window_hpp

#include "Globals.hpp"
#include "Assets/Vector2.hpp"

#include <SFML/Graphics.hpp>

class Window
{
public:
	Window(const std::string& windowName);

	void update();
	void begin_draw();
	void draw(const sf::Drawable& drawable);
	void end_draw();

	bool b_is_open() const;

	Vector2 vec2_get_size();

	sf::Vector2i vc2i_get_mouse_position();

private:
	sf::RenderWindow wndw_window;

	sf::View view_view;

	void on_resize();
};

#endif