#pragma once
#ifndef MenuSprite_hpp
#define MenuSprite_hpp\

#include "Asset.hpp"

struct MenuSprite {
	std::string s_name;
	std::string s_x;
	std::string s_y;
	std::string s_r;
	std::string s_w;
	std::string s_h;
	std::string s_texture;

	bool b_invert_gradient;
};

#endif