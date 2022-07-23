#pragma once
#ifndef Menu_hpp
#define Menu_hpp\

#include "SubMenu.hpp"

#include "../Window.hpp"
#include "../Globals.hpp"

#include <cstdlib>
#include <vector>
#include <filesystem>
#include <SFML/Graphics.hpp>

class Menu
{
public:
	Menu();

	void update_submenu(Vector2 vec2_window_size, std::string s_name);

	std::map<int, sf::Sprite> get_submenu_sprites(Vector2 vec2_window_size, std::string s_name);

private:
	void update_variable(Vector2 vec2_window_size, std::string s_name, int i_index);

	float get_value(Vector2 vec2_window_size, std::string s_name, std::string s_value);

	void generate_menus();

	void generate_submenu_sprites(std::string s_name);

	SubMenu sbmn_populate_submenu(nlohmann::json json_json, std::filesystem::path path_path);

	std::map<int, MenuVariable> m_i_mnvb_populate_menu_variables(nlohmann::json json_json, std::filesystem::path path_path, std::string s_submenu_name);

	std::map<int, MenuCalculation> m_i_mncl_populate_menu_calculations(nlohmann::json json_json, std::filesystem::path path_path, std::string s_submenu_name, int i_variable_index);

	std::map<int, MenuSprite> m_i_mnsp_populate_menu_sprites(nlohmann::json json_json, std::filesystem::path path_path, std::string s_submenu_name);

	std::map<std::string, std::map<int, sf::Sprite>> m_s_m_i_sprt_sprites;

	std::map<std::string, std::shared_ptr<sf::Texture>> m_s_p_txtr_menu_edge;

	std::map<std::string, SubMenu> m_s_sbmn_submenus;
};

#endif