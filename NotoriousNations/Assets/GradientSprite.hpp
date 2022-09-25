#pragma once
#ifndef GradientSprite_hpp
#define GradientSprite_hpp

#include <SFML/Graphics.hpp>

struct GradientSprite {
	sf::Sprite sprt_sprite;

	sf::Color colr_primary_color;
	sf::Color colr_secondary_color;

	bool b_invert_gradient;
};

#endif