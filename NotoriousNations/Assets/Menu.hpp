#pragma once
#ifndef Menu_hpp
#define Menu_hpp\

#include "SubMenu.hpp"
#include "Vector2.hpp"

#include "../json.hpp"

#include <cstdlib>
#include <vector>
#include <filesystem>
#include <SFML/Graphics.hpp>

class Globals;
class Menu
{
public:
	Menu();
	Menu(std::filesystem::path path_roaming_data_path);

	sf::FloatRect frct_get_iconbox_bounds(Vector2 vec2_window_size, std::string s_name);

	sf::FloatRect frct_get_namebox_bounds(Vector2 vec2_window_size, std::string s_name);

	std::map<int, sf::FloatRect> m_i_frct_get_icon_bounds(Vector2 vec2_window_size, std::string s_name);

	void update_submenu(Vector2 vec2_window_size, std::string s_name);

	void clear_toolbar();

	void populate_toolbar_soil_covers(std::string s_selected_soil_cover);

	int i_get_cursor_position();

	int i_get_nametext_height(Vector2 vec2_window_size, std::string s_name);

	sf::Vector2f vc2f_get_nametext_position(Vector2 vec2_window_size, std::string s_name);

	sf::Vector2f vc2f_get_icon_screen_coordinates(Vector2 vec2_window_size, std::string s_name, int i_index);

	float f_get_icon_scale(Vector2 vec2_window_size, std::string s_name);

	std::map<int, sf::Sprite> m_i_sprt_get_submenu_sprites(Vector2 vec2_window_size, std::string s_name);

	std::map<int, sf::Sprite> m_i_sprt_get_toolbar_sprites(Vector2 vec2_window_size, std::string s_name);

	std::map<int, std::string> m_i_s_get_toolbar_sprite_names(Vector2 vec2_window_size, std::string s_name);

private:
	int i_cursor_position;

	float get_value(Vector2 vec2_window_size, std::string s_name, std::string s_value);

	float calculate(Vector2 vec2_window_size, std::string s_name, std::map<int, MenuCalculation> m_i_mncl_menu_calculations, float f_input);

	SubMenu sbmn_populate_submenu(nlohmann::json json_json, std::filesystem::path path_path);

	std::string s_get_json(nlohmann::json json_json, std::string key);

	void update_variable(Vector2 vec2_window_size, std::string s_name, int i_index);

	void update_essentials(Vector2 vec2_window_size, std::string s_name);

	void generate_submenu_sprites(std::filesystem::path path_roaming_data_path, std::string s_name);

	void generate_menus(std::filesystem::path path_roaming_data_path);

	std::map<int, MenuVariable> m_i_mnvb_populate_menu_variables(nlohmann::json json_j, std::string key, std::filesystem::path path_path, std::string s_submenu_name);

	std::map<int, MenuCalculation> m_i_mncl_populate_menu_calculations(nlohmann::json json_j, std::string key, std::filesystem::path path_path, std::string s_submenu_name, int i_variable_index);

	std::map<int, MenuSprite> m_i_mnsp_populate_menu_sprites(nlohmann::json json_j, std::string key, std::filesystem::path path_path, std::string s_submenu_name);

	std::map<std::string, SubMenu> m_s_sbmn_submenus;

	std::map<std::string, std::shared_ptr<sf::Texture>> m_s_p_txtr_textures;

	std::map<std::string, std::map<int, sf::Sprite>> m_s_m_i_sprt_submenu_sprites;

	std::map<int, sf::Sprite> m_i_sprt_toolbar_sprites;

	std::map<int, std::string> m_i_s_toolbar_sprite_names;
};

#endif