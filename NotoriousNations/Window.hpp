#pragma once
#ifndef Window_hpp
#define Window_hpp

#include "Globals.hpp"

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

private:
	sf::RenderWindow window;
};

#endif