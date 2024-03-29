#include "Globals.hpp"

bool Globals::b_is_open() const
{
	return wndw_window.b_is_open();
}

std::shared_ptr<AssetMaps> Globals::p_asmp_get_asset_maps()
{
	return p_asmp_asset_maps;
}

std::shared_ptr<Camera> Globals::p_cmra_get_camera()
{
	return p_cmra_camera;
}

std::shared_ptr<Menu> Globals::p_menu_get_menu()
{
	return p_menu_menu;
}

std::filesystem::path Globals::path_get_roaming_data_path()
{
	return path_roaming_data_path;
}

void Globals::update_controllers()
{
	for (auto& [slot, controller] : m_i_cntr_controllers)
	{
		controller.update();
	}
}

Vector2 Globals::vec2_get_window_size()
{
	return wndw_window.vec2_get_size();
}

sf::Vector2i Globals::vc2i_get_mouse_position()
{
	return wndw_window.vc2i_get_mouse_position();
}

void Globals::update_mouse_wheel_input(int i_wheel, float f_delta)
{
	for (auto& [slot, controller] : m_i_cntr_controllers)
	{
		controller.update_mouse_wheel_input(i_wheel, f_delta);
	}
}

void Globals::update_window()
{
	wndw_window.update();
}

void Globals::begin_draw()
{
	wndw_window.begin_draw();
}

void Globals::draw(const sf::Drawable& drawable)
{
	wndw_window.draw(drawable);
}

void Globals::draw(const GradientSprite gtsp_gradient_sprite, std::shared_ptr<sf::Shader> shdr_shader)
{
	wndw_window.draw(gtsp_gradient_sprite.sprt_sprite, shdr_shader);
}

void Globals::end_draw()
{
	wndw_window.end_draw();
}

Controller Globals::cntr_get_controller(int i_controller)
{
	if (m_i_cntr_controllers.contains(i_controller))
	{
		return m_i_cntr_controllers[i_controller];
	}

	return Controller();
}

void Globals::gained_focus()
{
	b_has_focus = true;
}

void Globals::lost_focus()
{
	b_has_focus = false;
}

bool Globals::b_is_has_focus()
{
	return b_has_focus;
}

std::string Globals::s_get_namebox_text()
{
	if (s_namebox_text_dom != "")
	{
		return s_get_namebox_text_dom();
	}
	return s_get_namebox_text_sub();
}

std::string Globals::s_get_namebox_text_dom()
{
	return s_namebox_text_dom;
}

std::string Globals::s_get_namebox_text_sub()
{
	return s_namebox_text_sub;
}

void Globals::set_namebox_text_dom(std::string s_text)
{
	s_namebox_text_dom = s_text;
}

void Globals::set_namebox_text_sub(std::string s_text)
{
	s_namebox_text_sub = s_text;
}

// static function
// sets "path" to a pointer to a unicode string containing the path to the current user's Appdata/Roaming/NotoriousNations folder
// returns true if "path" is successfully set
std::filesystem::path Globals::generate_roaming_data_path()
{
	std::filesystem::path path_path;
	PWSTR pwst_path;

	if (SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &pwst_path) != S_OK)
	{
		std::throw_with_nested(std::runtime_error("cannot find ...Appdata\\Roaming, got " + (*((wchar_t*)pwst_path))));
	}

	path_path = std::filesystem::path(pwst_path);

	path_path += "\\NotoriousNations";

	if (path_path.empty())
	{
		if (std::filesystem::create_directories(path_path))
		{
			std::wcout << L"folder " << path_path.generic_wstring() << L" created" << "\n";
		}
		else
		{
			std::throw_with_nested(std::runtime_error("failed to create ...Appdata\\Roaming\\NotoriousNations"));
		}
	}
	else
	{
		std::wcout << L"folder " << path_path.generic_wstring() << L" found" << "\n";
	}

	return path_path;
}

void Globals::edit_soil_cover(std::string s_name, int i)
{
	p_asmp_asset_maps->set_soil_cover(s_get_current_map(), p_cmra_camera->int2_get_cursor_position(), p_asmp_asset_maps->m_s_slcv_get_soil_covers()[p_menu_menu->m_i_s_get_toolbar_sprite_names(vec2_get_window_size(), "Toolbar")[i]]);
}

std::string Globals::s_get_current_map()
{
	return s_current_map;
}

std::shared_ptr<Map> Globals::p_map_get_current_map()
{
	return p_asmp_get_asset_maps()->p_map_get_map(s_get_current_map());
}

std::shared_ptr<Player> Globals::plyr_get_turn_player()
{
	return p_map_get_current_map()->p_plyr_get_player(p_map_get_current_map()->m_i_s_get_turn_order()[p_map_get_current_map()->i_get_turn_player()]);
}

std::shared_ptr<sf::Shader> Globals::p_shdr_get_player_color_shader()
{
	return p_shdr_player_color_shader;
}