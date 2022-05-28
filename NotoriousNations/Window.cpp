#include "Window.hpp"

Window::Window(const std::string& windowName) : window(sf::VideoMode(800, 600), windowName, sf::Style::Resize)
{
	window.setVerticalSyncEnabled(true);
}

void Window::update()
{
	sf::Event event;
	if (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
	}
}

void Window::begin_draw()
{
	window.clear(sf::Color::Black);
}

void Window::draw(const sf::Drawable& drawable)
{
	window.draw(drawable);
}

void Window::end_draw()
{
	window.display();
}

bool Window::b_is_open() const
{
	return window.isOpen();
}