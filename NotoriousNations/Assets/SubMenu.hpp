#pragma once
#ifndef SubMenu_hpp
#define SubMenu_hpp\

#include "MenuVariable.hpp"
#include "MenuSprite.hpp"

struct SubMenu {
	std::string s_name;

	std::string s_scale;
	std::string s_size;
	std::string s_buffer;
	std::string s_resolution;

	std::string s_iconbox_x;
	std::string s_iconbox_y;
	std::string s_iconbox_w;
	std::string s_iconbox_h;

	std::string s_namebox_x;
	std::string s_namebox_y;
	std::string s_namebox_w;
	std::string s_namebox_h;

	std::map<int, MenuVariable> m_i_mnvb_menu_variables;
	std::map<int, MenuSprite> m_i_mnsp_menu_sprites;
};

#endif