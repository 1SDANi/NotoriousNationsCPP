#pragma once
#ifndef SubMenu_hpp
#define SubMenu_hpp\

#include "MenuVariable.hpp"
#include "MenuSprite.hpp"

struct SubMenu {
	std::string s_name;
	std::map<int, MenuVariable> m_i_mnvb_menu_variables;
	std::map<int, MenuSprite> m_i_mnsp_menu_sprites;
};

#endif