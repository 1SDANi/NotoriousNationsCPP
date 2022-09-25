#pragma once
#ifndef Menu_hpp
#define Menu_hpp\

#include "SubMenu.hpp"
#include "Vector2.hpp"
#include "Tile.hpp"
#include "GradientSprite.hpp"

#include "../json.hpp"

#include <cstdlib>
#include <vector>
#include <filesystem>
#include <iostream>
#include <memory>

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

	void populate_toolbar_soil_covers(std::string s_selected_soil_cover, std::map<std::string, SoilCover> m_s_t_map, std::shared_ptr<sf::Texture> p_txtr_atlas_texture);

	void populate_toolbar_units(std::map<std::string, std::shared_ptr<Unit>> m_s_t_map, std::shared_ptr<sf::Texture> p_txtr_atlas_texture);

	void populate_toolbar_unit_actions(std::shared_ptr<Unit> s_p_unit_unit, int i_selected_option);

	void populate_toolbar_tile(Tile tile_selected_tile);

	void populate_orphan_icon(int i_index, std::string s_name, sf::Color colr_primary, sf::Color colr_secondary, bool b_invert_gradient);

	int i_get_cursor_position();

	int i_get_nametext_height(Vector2 vec2_window_size, std::string s_name);

	sf::Vector2f vc2f_get_nametext_position(Vector2 vec2_window_size, std::string s_name);

	sf::Vector2f vc2f_get_icon_screen_coordinates(Vector2 vec2_window_size, std::string s_name, int i_index);

	float f_get_icon_scale(Vector2 vec2_window_size, std::string s_name);

	std::map<int, GradientSprite> m_i_gtsp_get_submenu_sprites(Vector2 vec2_window_size, std::string s_name);

	std::map<int, GradientSprite> m_i_gtsp_get_toolbar_sprites(Vector2 vec2_window_size, std::string s_name);

	std::map<int, std::string> m_i_s_get_toolbar_sprite_names(Vector2 vec2_window_size, std::string s_name);

private:
	int i_cursor_position;

	float get_value(Vector2 vec2_window_size, std::string s_name, std::string s_value);

	float calculate(Vector2 vec2_window_size, std::string s_name, std::map<int, MenuCalculation> m_i_mncl_menu_calculations, float f_input);

	SubMenu sbmn_populate_submenu(nlohmann::json json_json, std::filesystem::path path_path);

	std::string s_get_json(nlohmann::json json_json, std::string key);

	bool b_get_json(nlohmann::json json_json, std::string key);

	void update_variable(Vector2 vec2_window_size, std::string s_name, int i_index);

	void update_essentials(Vector2 vec2_window_size, std::string s_name);

	void generate_submenu_sprites(std::filesystem::path path_roaming_data_path, std::string s_name);

	void generate_menus(std::filesystem::path path_roaming_data_path);

	std::map<int, MenuVariable> m_i_mnvb_populate_menu_variables(nlohmann::json json_j, std::string key, std::filesystem::path path_path, std::string s_submenu_name);

	std::map<int, MenuCalculation> m_i_mncl_populate_menu_calculations(nlohmann::json json_j, std::string key, std::filesystem::path path_path, std::string s_submenu_name, int i_variable_index);

	std::map<int, MenuSprite> m_i_mnsp_populate_menu_sprites(nlohmann::json json_j, std::string key, std::filesystem::path path_path, std::string s_submenu_name);

	std::map<std::string, SubMenu> m_s_sbmn_submenus;

	std::map<std::string, std::shared_ptr<sf::Texture>> m_s_p_txtr_textures;

	std::map<std::string, std::map<int, GradientSprite>> m_s_m_i_gtsp_submenu_sprites;

	std::map<int, GradientSprite> m_i_gtsp_toolbar_sprites;

	std::map<int, std::string> m_i_s_toolbar_sprite_names;
};

#endif