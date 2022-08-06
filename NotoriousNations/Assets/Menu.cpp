#include "Menu.hpp"

#include "../Globals.hpp"

Menu::Menu()
{
	i_cursor_position = -1;
}

Menu::Menu(std::filesystem::path path_roaming_data_path)
{
	i_cursor_position = -1;

	generate_menus(path_roaming_data_path);
}

sf::FloatRect Menu::frct_get_toolbar_bounds(Vector2 vec2_window_size, std::string s_name)
{
	return sf::FloatRect(get_value(vec2_window_size, s_name, m_s_sbmn_submenus[s_name].s_toolbar_x),
						get_value(vec2_window_size, s_name, m_s_sbmn_submenus[s_name].s_toolbar_y),
						get_value(vec2_window_size, s_name, m_s_sbmn_submenus[s_name].s_toolbar_w),
						get_value(vec2_window_size, s_name, m_s_sbmn_submenus[s_name].s_toolbar_h));
}

std::map<int, sf::FloatRect> Menu::m_i_frct_get_icon_bounds(Vector2 vec2_window_size, std::string s_name)
{
	std::map<int, sf::FloatRect> m_i_frct_return = std::map<int, sf::FloatRect>();

	sf::Vector2f vc2f_icon_screen_coordinates;

	for (int i = 0; i < m_i_sprt_toolbar_sprites.size(); i++)
	{
		vc2f_icon_screen_coordinates = vc2f_get_icon_screen_coordinates(vec2_window_size, s_name, i);

		m_i_frct_return.emplace(i, sf::FloatRect(vc2f_icon_screen_coordinates, sf::Vector2f(get_value(vec2_window_size, s_name, m_s_sbmn_submenus[s_name].s_size),
																						get_value(vec2_window_size, s_name, m_s_sbmn_submenus[s_name].s_size))));
	}

	return m_i_frct_return;
}

void Menu::update_submenu(Vector2 vec2_window_size, std::string s_name)
{
	for (int i = 0; i < m_s_sbmn_submenus[s_name].m_i_mnvb_menu_variables.size(); i++)
	{
		update_variable(vec2_window_size, s_name, i);
	}
}

void Menu::clear_toolbar()
{
	m_i_sprt_toolbar_sprites = std::map<int, sf::Sprite>();
	m_i_s_toolbar_sprite_names = std::map<int, std::string>();
}

void Menu::populate_toolbar_soil_covers(std::string s_selected_soil_cover)
{
	clear_toolbar();

	int i_tile_size = Globals::glob_get_globals().p_asmp_get_asset_maps()->i_get_tile_size();

	int i;

	i_cursor_position = -1;

	for (std::pair<std::string, SoilCover> pair_pair : Globals::glob_get_globals().p_asmp_get_asset_maps()->m_sslcv_get_soil_covers())
	{
		Int2 int2_atlas_coords = pair_pair.second.int2_get_atlas_coords();

		i = int2_atlas_coords.x + int2_atlas_coords.y * Globals::glob_get_globals().p_asmp_get_asset_maps()->p_txtr_get_soil_cover_atlas()->getSize().x / i_tile_size;

		sf::Sprite sprt_temp_sprite = sf::Sprite();

		sprt_temp_sprite.setTexture(*Globals::glob_get_globals().p_asmp_get_asset_maps()->p_txtr_get_soil_cover_atlas());
		sprt_temp_sprite.setTextureRect(sf::Rect(int2_atlas_coords.x * i_tile_size,
			((int)Globals::glob_get_globals().p_asmp_get_asset_maps()->p_txtr_get_soil_cover_atlas()->getSize().y) - i_tile_size - int2_atlas_coords.y * i_tile_size,
			i_tile_size,
			i_tile_size));

		if (pair_pair.first == s_selected_soil_cover) { i_cursor_position = i; }

		m_i_sprt_toolbar_sprites.emplace(i, sprt_temp_sprite);
		m_i_s_toolbar_sprite_names.emplace(i, pair_pair.second.s_get_name());
	}
}

int Menu::i_get_cursor_position()
{
	return i_cursor_position;
}

void Menu::update_variable(Vector2 vec2_window_size, std::string s_name, int i_index)
{
	m_s_sbmn_submenus[s_name].m_i_mnvb_menu_variables[i_index].f_output = get_value(vec2_window_size, s_name, m_s_sbmn_submenus[s_name].m_i_mnvb_menu_variables[i_index].s_value);

	m_s_sbmn_submenus[s_name].m_i_mnvb_menu_variables[i_index].f_output = calculate(vec2_window_size, s_name, m_s_sbmn_submenus[s_name].m_i_mnvb_menu_variables[i_index].m_i_mncl_menu_calculations, m_s_sbmn_submenus[s_name].m_i_mnvb_menu_variables[i_index].f_output);
}

float Menu::calculate(Vector2 vec2_window_size, std::string s_name, std::map<int, MenuCalculation> m_i_mncl_menu_calculations, float f_input)
{
	if (m_i_mncl_menu_calculations.size() == 0) return f_input;

	float f_output = f_input;

	for (int i = 0; i < m_i_mncl_menu_calculations.size(); i++)
	{
		std::string s_value = m_i_mncl_menu_calculations[i].s_value;

		switch (m_i_mncl_menu_calculations[i].i_operation)
		{
		case (MENU_OPERATION_ADD):
			f_output += get_value(vec2_window_size, s_name, s_value);
			break;
		case (MENU_OPERATION_SUBTRACT):
			f_output -= get_value(vec2_window_size, s_name, s_value);
			break;
		case (MENU_OPERATION_MULTIPLY):
			f_output *= get_value(vec2_window_size, s_name, s_value);
			break;
		case (MENU_OPERATION_DIVIDE):
			f_output /= get_value(vec2_window_size, s_name, s_value);
			break;
		default:
			break;
		}
	}

	return f_output;
}

float Menu::get_value(Vector2 vec2_window_size, std::string s_name, std::string s_value)
{
	char* end = nullptr;
	float val = strtof(s_value.c_str(), &end);

	if (end != s_value.c_str() && *end == '\0' && val != HUGE_VAL)
	{
		return val;
	}
	else if (s_value == "window_width")
	{
		return (float)vec2_window_size.x;
	}
	else if (s_value == "window_height")
	{
		return (float)vec2_window_size.y;
	}
	for (int i = 0; i < m_s_sbmn_submenus[s_name].m_i_mnvb_menu_variables.size(); i++)
	{
		if (m_s_sbmn_submenus[s_name].m_i_mnvb_menu_variables[i].s_name == s_value)
		{
			return m_s_sbmn_submenus[s_name].m_i_mnvb_menu_variables[i].f_output;
		}
	}
	return 0.0;
}

void Menu::generate_menus(std::filesystem::path path_roaming_data_path)
{
	clear_toolbar();
	m_s_m_i_sprt_submenu_sprites = std::map<std::string, std::map<int, sf::Sprite>>();
	std::vector<std::filesystem::path>  v_path_matching_paths = FolderCrawler::b_crawl_folder(path_roaming_data_path.string() + "\\JSON\\Menu\\menus", {L".json"});
	if (v_path_matching_paths.size() > 0)
	{
		SubMenu sbmn_iteration;

		nlohmann::json json_json;

		for (std::filesystem::path path_path : v_path_matching_paths)
		{
			std::ifstream ifst_ifstream(path_path.c_str());

			json_json = nlohmann::json::parse(ifst_ifstream);

			sbmn_iteration = sbmn_populate_submenu(json_json, path_path);

			m_s_sbmn_submenus[sbmn_iteration.s_name] = sbmn_iteration;

			m_s_m_i_sprt_submenu_sprites.emplace(sbmn_iteration.s_name, std::map<int, sf::Sprite>());

			generate_submenu_sprites(path_roaming_data_path, sbmn_iteration.s_name);
		}
	}
}

std::string Menu::s_get_json(nlohmann::json json_json, std::string key)
{
	if (json_json.at(key).is_string())
	{
		return json_json.at(key);
	}
	else
	{
		return "";
	}
}

SubMenu Menu::sbmn_populate_submenu(nlohmann::json json_json, std::filesystem::path path_path)
{
	SubMenu sbmn_submenu = SubMenu();

	if (json_json.at("s_type") != "Toolbar")
	{
		std::throw_with_nested(path_path.string() + "is not a Toolbar");
	}
	
	sbmn_submenu.s_name = s_get_json(json_json, "s_name");

	sbmn_submenu.s_scale = s_get_json(json_json, "s_scale");
	sbmn_submenu.s_size = s_get_json(json_json, "s_size");
	sbmn_submenu.s_buffer = s_get_json(json_json, "s_buffer");
	sbmn_submenu.s_resolution = s_get_json(json_json, "s_resolution");

	sbmn_submenu.s_toolbar_x = s_get_json(json_json, "s_toolbar_x");
	sbmn_submenu.s_toolbar_y = s_get_json(json_json, "s_toolbar_y");
	sbmn_submenu.s_toolbar_w = s_get_json(json_json, "s_toolbar_w");
	sbmn_submenu.s_toolbar_h = s_get_json(json_json, "s_toolbar_h");
	
	sbmn_submenu.m_i_mnvb_menu_variables = m_i_mnvb_populate_menu_variables(json_json, "dict_i_vrbl_variables", path_path, sbmn_submenu.s_name);

	if (json_json.at("dict_i_sprt_sprites").is_object())
	{
		sbmn_submenu.m_i_mnsp_menu_sprites = m_i_mnsp_populate_menu_sprites(json_json, "dict_i_sprt_sprites", path_path, sbmn_submenu.s_name);
	}

	return sbmn_submenu;
}

std::map<int, MenuVariable> Menu::m_i_mnvb_populate_menu_variables(nlohmann::json json_j, std::string key, std::filesystem::path path_path, std::string s_submenu_name)
{
	std::map<int, MenuVariable> m_i_mnvb_menu_variables = std::map<int, MenuVariable>();

	if (!json_j.contains(key) || !json_j.at(key).is_object())
	{
		return m_i_mnvb_menu_variables;
	}

	nlohmann::json json_json = json_j.at(key);

	for (int i = 0; i < json_json.size(); i++)
	{
		MenuVariable mnvb_menu_variable;

		if (json_json.at(std::to_string(i)).at("s_type") != "Variable")
		{
			std::throw_with_nested("object at index " + std::to_string(i) + " in submenu " + s_submenu_name + " at " + path_path.string() + " is not a Variable");

			continue;
		}
		
		mnvb_menu_variable.s_name = s_get_json(json_json.at(std::to_string(i)), "s_name");
		mnvb_menu_variable.s_value = s_get_json(json_json.at(std::to_string(i)), "s_value");

		mnvb_menu_variable.m_i_mncl_menu_calculations = m_i_mncl_populate_menu_calculations(json_json.at(std::to_string(i)), "dict_i_cltn_calculations", path_path, s_submenu_name, i);
		
		m_i_mnvb_menu_variables.emplace(i, mnvb_menu_variable);
	}

	return m_i_mnvb_menu_variables;
}

std::map<int, MenuCalculation> Menu::m_i_mncl_populate_menu_calculations(nlohmann::json json_j, std::string key, std::filesystem::path path_path, std::string s_submenu_name, int i_variable_index)
{
	std::map<int, MenuCalculation> m_i_mncl_menu_calculations;

	if (!json_j.contains(key) || !json_j.at(key).is_object())
	{
		return m_i_mncl_menu_calculations;
	}

	nlohmann::json json_json = json_j.at(key);

	for (int i = 0; i < json_json.size(); i++)
	{
		MenuCalculation mncl_menu_calculation;

		if (json_json.at(std::to_string(i)).at("s_type") != "Calculation")
		{
			std::throw_with_nested("object at index " + std::to_string(i) + " in variable at index " + std::to_string(i_variable_index) + " in submenu " + s_submenu_name + " at " + path_path.string() + " is not a Variable");
			
			continue;
		}
		
		mncl_menu_calculation.s_value = s_get_json(json_json.at(std::to_string(i)), "s_value");

		switch (Globals::hash(s_get_json(json_json.at(std::to_string(i)), "s_operation")))
		{
		case Globals::hash("Add"):
			mncl_menu_calculation.i_operation = MENU_OPERATION_ADD;
			break;
		case Globals::hash("Subtract"):
			mncl_menu_calculation.i_operation = MENU_OPERATION_SUBTRACT;
			break;
		case Globals::hash("Multiply"):
			mncl_menu_calculation.i_operation = MENU_OPERATION_MULTIPLY;
			break;
		case Globals::hash("Divide"):
			mncl_menu_calculation.i_operation = MENU_OPERATION_DIVIDE;
			break;
		default:
			mncl_menu_calculation.i_operation = MENU_OPERATION_NONE;
			break;
		}
		
		m_i_mncl_menu_calculations.emplace(i, mncl_menu_calculation);
	}

	return m_i_mncl_menu_calculations;
}

std::map<int, MenuSprite> Menu::m_i_mnsp_populate_menu_sprites(nlohmann::json json_j, std::string key, std::filesystem::path path_path, std::string s_submenu_name)
{
	std::map<int, MenuSprite> m_i_mnsp_menu_sprites;

	if (!json_j.contains(key) || !json_j.at(key).is_object())
	{
		return m_i_mnsp_menu_sprites;
	}

	nlohmann::json json_json = json_j.at(key);

	for (int i = 0; i < json_json.size(); i++)
	{
		MenuSprite mncl_menu_sprite;

		if (json_json.at(std::to_string(i)).at("s_type") != "Sprite")
		{
			std::throw_with_nested("object at index " + std::to_string(i) + " in submenu " + s_submenu_name + " at " + path_path.string() + " is not a Sprite");

			continue;
		}

		mncl_menu_sprite.s_name = s_get_json(json_json.at(std::to_string(i)), "s_name");
		mncl_menu_sprite.s_x = s_get_json(json_json.at(std::to_string(i)), "s_x");
		mncl_menu_sprite.s_y = s_get_json(json_json.at(std::to_string(i)), "s_y");
		mncl_menu_sprite.s_r = s_get_json(json_json.at(std::to_string(i)), "s_r");
		mncl_menu_sprite.s_w = s_get_json(json_json.at(std::to_string(i)), "s_w");
		mncl_menu_sprite.s_h = s_get_json(json_json.at(std::to_string(i)), "s_h");
		mncl_menu_sprite.s_texture = s_get_json(json_json.at(std::to_string(i)), "s_texture");

		m_i_mnsp_menu_sprites.emplace(i, mncl_menu_sprite);
	}

	return m_i_mnsp_menu_sprites;
}

void Menu::generate_submenu_sprites(std::filesystem::path path_roaming_data_path, std::string s_name)
{
	m_s_p_txtr_textures = std::map<std::string, std::shared_ptr<sf::Texture>>();

	for (auto const& [i_index, mnsp_menu_sprite] : m_s_sbmn_submenus[s_name].m_i_mnsp_menu_sprites)
	{
		if (!m_s_p_txtr_textures.contains(mnsp_menu_sprite.s_texture))
		{
			sf::Texture txtr_temp_texture;

			txtr_temp_texture.loadFromFile(path_roaming_data_path.string() + mnsp_menu_sprite.s_texture);

			m_s_p_txtr_textures.emplace(mnsp_menu_sprite.s_texture, std::make_shared<sf::Texture>(sf::Texture(txtr_temp_texture)));
		}
		
		m_s_m_i_sprt_submenu_sprites.at(s_name).emplace(i_index, sf::Sprite());

		m_s_m_i_sprt_submenu_sprites.at(s_name).at(i_index).setTexture(*m_s_p_txtr_textures.at(mnsp_menu_sprite.s_texture));
	}
}

std::map<int, sf::Sprite> Menu::m_i_sprt_get_submenu_sprites(Vector2 vec2_window_size, std::string s_name)
{
	for (auto const& [i_index, mnsp_menu_sprite] : m_s_sbmn_submenus[s_name].m_i_mnsp_menu_sprites)
	{
		m_s_m_i_sprt_submenu_sprites.at(s_name).at(i_index).setPosition(get_value(vec2_window_size, s_name, mnsp_menu_sprite.s_x), get_value(vec2_window_size, s_name, mnsp_menu_sprite.s_y));
		m_s_m_i_sprt_submenu_sprites.at(s_name).at(i_index).setRotation(get_value(vec2_window_size, s_name, mnsp_menu_sprite.s_r));
		m_s_m_i_sprt_submenu_sprites.at(s_name).at(i_index).setScale(get_value(vec2_window_size, s_name, mnsp_menu_sprite.s_w), get_value(vec2_window_size, s_name, mnsp_menu_sprite.s_h));
	}

	return m_s_m_i_sprt_submenu_sprites.at(s_name);
}

std::map<int, sf::Sprite> Menu::m_i_sprt_get_toolbar_sprites(Vector2 vec2_window_size, std::string s_name)
{
	for (int i = 0; i < m_i_sprt_toolbar_sprites.size(); i++)
	{
		m_i_sprt_toolbar_sprites.at(i).setPosition(vc2f_get_icon_screen_coordinates(vec2_window_size, s_name, i));
		m_i_sprt_toolbar_sprites.at(i).setRotation(0);
		m_i_sprt_toolbar_sprites.at(i).setScale(f_get_icon_scale(vec2_window_size, s_name), f_get_icon_scale(vec2_window_size, s_name));
	}

	return m_i_sprt_toolbar_sprites;
}

std::map<int, std::string> Menu::m_i_s_get_toolbar_sprite_names(Vector2 vec2_window_size, std::string s_name)
{
	return m_i_s_toolbar_sprite_names;
}

sf::Vector2f Menu::vc2f_get_icon_screen_coordinates(Vector2 vec2_window_size, std::string s_name, int i_index)
{
	sf::Vector2f vc2f_top_left = sf::Vector2(get_value(vec2_window_size, s_name, m_s_sbmn_submenus[s_name].s_toolbar_x), get_value(vec2_window_size, s_name, m_s_sbmn_submenus[s_name].s_toolbar_y));

	float f_buffer = get_value(vec2_window_size, s_name, m_s_sbmn_submenus[s_name].s_buffer);

	float f_scale = get_value(vec2_window_size, s_name, m_s_sbmn_submenus[s_name].s_scale);

	float f_offset = i_index * (f_scale * get_value(vec2_window_size, s_name, m_s_sbmn_submenus[s_name].s_resolution) + f_buffer);

	return sf::Vector2f(vc2f_top_left.x + f_offset, vc2f_top_left.y);
}

float Menu::f_get_icon_scale(Vector2 vec2_window_size, std::string s_name)
{
	return get_value(vec2_window_size, s_name, m_s_sbmn_submenus[s_name].s_scale);
}