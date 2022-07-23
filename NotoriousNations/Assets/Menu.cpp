#include "Menu.hpp"

Menu::Menu()
{
	generate_menus();
}

void Menu::update_submenu(Vector2 vec2_window_size, std::string s_name)
{
	for (int i = 0; i < m_s_sbmn_submenus[s_name].m_i_mnvb_menu_variables.size(); i++)
	{
		update_variable(vec2_window_size, s_name, i);
	}
}

void Menu::update_variable(Vector2 vec2_window_size, std::string s_name, int i_index)
{
	m_s_sbmn_submenus[s_name].m_i_mnvb_menu_variables[i_index].f_output = get_value(vec2_window_size, s_name, m_s_sbmn_submenus[s_name].m_i_mnvb_menu_variables[i_index].s_value);

	if (m_s_sbmn_submenus[s_name].m_i_mnvb_menu_variables[i_index].m_i_mncl_menu_calculations.size() == 0)
	{
		return;
	}

	for (int i = 0; i < m_s_sbmn_submenus[s_name].m_i_mnvb_menu_variables[i_index].m_i_mncl_menu_calculations.size(); i++)
	{
		std::string s_value = m_s_sbmn_submenus[s_name].m_i_mnvb_menu_variables[i_index].m_i_mncl_menu_calculations[i].s_value;

		switch (m_s_sbmn_submenus[s_name].m_i_mnvb_menu_variables[i_index].m_i_mncl_menu_calculations[i].i_operation)
		{
		case (MENU_OPERATION_ADD):
			m_s_sbmn_submenus[s_name].m_i_mnvb_menu_variables[i_index].f_output += get_value(vec2_window_size, s_name, s_value);
			break;
		case (MENU_OPERATION_SUBTRACT):
			m_s_sbmn_submenus[s_name].m_i_mnvb_menu_variables[i_index].f_output -= get_value(vec2_window_size, s_name, s_value);
			break;
		case (MENU_OPERATION_MULTIPLY):
			m_s_sbmn_submenus[s_name].m_i_mnvb_menu_variables[i_index].f_output *= get_value(vec2_window_size, s_name, s_value);
			break;
		case (MENU_OPERATION_DIVIDE):
			m_s_sbmn_submenus[s_name].m_i_mnvb_menu_variables[i_index].f_output /= get_value(vec2_window_size, s_name, s_value);
			break;
		default:
			break;
		}
	}
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

void Menu::generate_menus()
{
	m_s_m_i_sprt_sprites = std::map<std::string, std::map<int, sf::Sprite>>();
	std::vector<std::filesystem::path>  v_path_matching_paths = FolderCrawler::b_crawl_folder(Globals::glob_get_globals().path_get_roaming_data_path().string() + "\\JSON\\Menu\\menus", {L".json"});
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

			m_s_m_i_sprt_sprites.emplace(sbmn_iteration.s_name, std::map<int, sf::Sprite>());

			generate_submenu_sprites(sbmn_iteration.s_name);
		}
	}
}

SubMenu Menu::sbmn_populate_submenu(nlohmann::json json_json, std::filesystem::path path_path)
{
	SubMenu sbmn_submenu = SubMenu();

	if (json_json.at("s_type") != "Menu")
	{
		std::throw_with_nested(path_path.string() + "is not a Menu");
	}

	if (json_json.at("s_name").is_string())
	{
		sbmn_submenu.s_name = json_json.at("s_name");
	}

	if (json_json.at("dict_i_vrbl_variables").is_object())
	{
		sbmn_submenu.m_i_mnvb_menu_variables = m_i_mnvb_populate_menu_variables(json_json.at("dict_i_vrbl_variables"), path_path, sbmn_submenu.s_name);
	}

	if (json_json.at("dict_i_sprt_sprites").is_object())
	{
		sbmn_submenu.m_i_mnsp_menu_sprites = m_i_mnsp_populate_menu_sprites(json_json.at("dict_i_sprt_sprites"), path_path, sbmn_submenu.s_name);
	}

	return sbmn_submenu;
}

std::map<int, MenuVariable> Menu::m_i_mnvb_populate_menu_variables(nlohmann::json json_json, std::filesystem::path path_path, std::string s_submenu_name)
{
	std::map<int, MenuVariable> m_i_mnvb_menu_variables;

	for (int i = 0; i < json_json.size(); i++)
	{
		MenuVariable mnvb_menu_variable;

		if (json_json.at(std::to_string(i)).at("s_type") != "Variable")
		{
			std::throw_with_nested("object at index " + std::to_string(i) + " in submenu " + s_submenu_name + " at " + path_path.string() + " is not a Variable");
		}

		if (json_json.at(std::to_string(i)).at("s_name").is_string())
		{
			mnvb_menu_variable.s_name = json_json.at(std::to_string(i)).at("s_name");
		}

		if (json_json.at(std::to_string(i)).at("s_value").is_string())
		{
			mnvb_menu_variable.s_value = json_json.at(std::to_string(i)).at("s_value");
		}

		if (json_json.at(std::to_string(i)).contains("dict_i_cltn_calculations") && json_json.at(std::to_string(i)).at("dict_i_cltn_calculations").is_object())
		{
			mnvb_menu_variable.m_i_mncl_menu_calculations = m_i_mncl_populate_menu_calculations(json_json.at(std::to_string(i)).at("dict_i_cltn_calculations"), path_path, s_submenu_name, i);
		}

		m_i_mnvb_menu_variables.emplace(i, mnvb_menu_variable);
	}

	return m_i_mnvb_menu_variables;
}

std::map<int, MenuCalculation> Menu::m_i_mncl_populate_menu_calculations(nlohmann::json json_json, std::filesystem::path path_path, std::string s_submenu_name, int i_variable_index)
{
	std::map<int, MenuCalculation> m_i_mncl_menu_calculations;

	for (int i = 0; i < json_json.size(); i++)
	{
		MenuCalculation mncl_menu_calculation;

		if (json_json.at(std::to_string(i)).at("s_type") != "Calculation")
		{
			std::throw_with_nested("object at index " + std::to_string(i) + " in variable at index " + std::to_string(i_variable_index) + " in submenu " + s_submenu_name + " at " + path_path.string() + " is not a Variable");
		}

		if (json_json.at(std::to_string(i)).at("s_value").is_string())
		{
			mncl_menu_calculation.s_value = json_json.at(std::to_string(i)).at("s_value");
		}

		if (json_json.at(std::to_string(i)).at("s_operation").is_string())
		{
			if (json_json.at(std::to_string(i)).at("s_operation") == "Add")
			{
				mncl_menu_calculation.i_operation = MENU_OPERATION_ADD;
			}
			else if (json_json.at(std::to_string(i)).at("s_operation") == "Subtract")
			{
				mncl_menu_calculation.i_operation = MENU_OPERATION_SUBTRACT;
			}
			else if (json_json.at(std::to_string(i)).at("s_operation") == "Multiply")
			{
				mncl_menu_calculation.i_operation = MENU_OPERATION_MULTIPLY;
			}
			else if (json_json.at(std::to_string(i)).at("s_operation") == "Divide")
			{
				mncl_menu_calculation.i_operation = MENU_OPERATION_DIVIDE;
			}
		}

		m_i_mncl_menu_calculations.emplace(i, mncl_menu_calculation);
	}

	return m_i_mncl_menu_calculations;
}

std::map<int, MenuSprite> Menu::m_i_mnsp_populate_menu_sprites(nlohmann::json json_json, std::filesystem::path path_path, std::string s_submenu_name)
{
	std::map<int, MenuSprite> m_i_mnsp_menu_sprites;

	for (int i = 0; i < json_json.size(); i++)
	{
		MenuSprite mncl_menu_sprite;

		if (json_json.at(std::to_string(i)).at("s_type") != "Sprite")
		{
			std::throw_with_nested("object at index " + std::to_string(i) + " in submenu " + s_submenu_name + " at " + path_path.string() + " is not a Sprite");
		}

		if (json_json.at(std::to_string(i)).at("s_name").is_string())
		{
			mncl_menu_sprite.s_name = json_json.at(std::to_string(i)).at("s_name");
		}

		if (json_json.at(std::to_string(i)).at("s_x").is_string())
		{
			mncl_menu_sprite.s_x = json_json.at(std::to_string(i)).at("s_x");
		}

		if (json_json.at(std::to_string(i)).at("s_y").is_string())
		{
			mncl_menu_sprite.s_y = json_json.at(std::to_string(i)).at("s_y");
		}

		if (json_json.at(std::to_string(i)).at("s_r").is_string())
		{
			mncl_menu_sprite.s_r = json_json.at(std::to_string(i)).at("s_r");
		}

		if (json_json.at(std::to_string(i)).at("s_w").is_string())
		{
			mncl_menu_sprite.s_w = json_json.at(std::to_string(i)).at("s_w");
		}

		if (json_json.at(std::to_string(i)).at("s_h").is_string())
		{
			mncl_menu_sprite.s_h = json_json.at(std::to_string(i)).at("s_h");
		}

		if (json_json.at(std::to_string(i)).at("s_texture").is_string())
		{
			mncl_menu_sprite.s_texture = json_json.at(std::to_string(i)).at("s_texture");
		}

		m_i_mnsp_menu_sprites.emplace(i, mncl_menu_sprite);
	}

	return m_i_mnsp_menu_sprites;
}

void Menu::generate_submenu_sprites(std::string s_name)
{
	m_s_p_txtr_menu_edge = std::map<std::string, std::shared_ptr<sf::Texture>>();

	for (auto const& [i_index, mnsp_menu_sprite] : m_s_sbmn_submenus[s_name].m_i_mnsp_menu_sprites)
	{
		if (!m_s_p_txtr_menu_edge.contains(mnsp_menu_sprite.s_texture))
		{
			sf::Texture txtr_temp_texture;

			txtr_temp_texture.loadFromFile(Globals::glob_get_globals().path_get_roaming_data_path().string() + mnsp_menu_sprite.s_texture);

			m_s_p_txtr_menu_edge.emplace(mnsp_menu_sprite.s_texture, std::make_shared<sf::Texture>(sf::Texture(txtr_temp_texture)));
		}
		
		m_s_m_i_sprt_sprites.at(s_name).emplace(i_index, sf::Sprite());

		m_s_m_i_sprt_sprites.at(s_name).at(i_index).setTexture(*m_s_p_txtr_menu_edge.at(mnsp_menu_sprite.s_texture));
	}
}

std::map<int, sf::Sprite> Menu::get_submenu_sprites(Vector2 vec2_window_size, std::string s_name)
{
	for (auto const& [i_index, mnsp_menu_sprite] : m_s_sbmn_submenus[s_name].m_i_mnsp_menu_sprites)
	{
		m_s_m_i_sprt_sprites.at(s_name).at(i_index).setPosition(get_value(vec2_window_size, s_name, mnsp_menu_sprite.s_x), get_value(vec2_window_size, s_name, mnsp_menu_sprite.s_y));
		m_s_m_i_sprt_sprites.at(s_name).at(i_index).setRotation(get_value(vec2_window_size, s_name, mnsp_menu_sprite.s_r));
		m_s_m_i_sprt_sprites.at(s_name).at(i_index).setScale(get_value(vec2_window_size, s_name, mnsp_menu_sprite.s_w), get_value(vec2_window_size, s_name, mnsp_menu_sprite.s_h));
	}

	return m_s_m_i_sprt_sprites.at(s_name);
}