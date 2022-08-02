#include "Window.hpp"

Window::Window(const std::string& windowName) : wndw_window(sf::VideoMode(800, 600), windowName, sf::Style::Close | sf::Style::Resize | sf::Style::Titlebar)
{
	wndw_window.setVerticalSyncEnabled(true);
	wndw_window.setFramerateLimit(60);
	
	view_view = sf::View(wndw_window.getDefaultView());
	view_view = sf::View(sf::FloatRect(0, 0, 800, 600));

	on_resize();
}

void Window::update()
{
	sf::Event event;
	if (wndw_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			wndw_window.close();
			break;
		case sf::Event::Resized:
			on_resize();
			break;
		case sf::Event::GainedFocus:
			Globals::glob_get_globals().gained_focus();
			break;
		case sf::Event::LostFocus:
			Globals::glob_get_globals().lost_focus();
			break;
		case sf::Event::MouseWheelScrolled:
			switch (event.mouseWheelScroll.wheel)
			{
			case sf::Mouse::VerticalWheel:
			case sf::Mouse::HorizontalWheel:
				Globals::glob_get_globals().update_mouse_wheel_input(event.mouseWheelScroll.wheel, event.mouseWheelScroll.delta);
				break;
			}
			break;
		}
	}
}

void Window::on_resize()
{
	sf::Vector2f size = static_cast<sf::Vector2f>(wndw_window.getSize());

	if (size.x < 160) size.x = 160;
	if (size.y < 144) size.y = 144;

	wndw_window.setSize(static_cast<sf::Vector2u>(size));

	view_view = sf::View(sf::FloatRect(0.f, 0.f, size.x, size.y));

	wndw_window.setView(view_view);
}

Vector2 Window::vec2_get_size()
{
	return Vector2(wndw_window.getSize().x, wndw_window.getSize().y);
}

void Window::begin_draw()
{
	wndw_window.clear(sf::Color::Black);
}

void Window::draw(const sf::Drawable& drawable)
{
	wndw_window.draw(drawable);
}

void Window::end_draw()
{
	wndw_window.display();
}

bool Window::b_is_open() const
{
	return wndw_window.isOpen();
}

sf::Vector2i Window::vc2i_get_mouse_position()
{
	return sf::Mouse::getPosition(wndw_window);
}
