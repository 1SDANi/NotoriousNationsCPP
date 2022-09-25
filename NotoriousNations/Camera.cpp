#include "Camera.hpp"

#include "Globals.hpp"

const std::map<Camera::CameraOutput, std::string> Camera::m_cotp_s_output_type_strings
{
	{ CameraOutput::CAMERA_OUTPUT_VERTICAL, "Vertical" },
	{ CameraOutput::CAMERA_OUTPUT_HORIZONTAL, "Horizontal" },
	{ CameraOutput::CAMERA_OUTPUT_ZOOM, "Zoom" },
	{ CameraOutput::CAMERA_OUTPUT_SELECT, "Select" },
	{ CameraOutput::CAMERA_OUTPUT_CANCEL, "Cancel" }
};

const std::map<std::string, Camera::CameraOutput> Camera::m_s_cotp_output_type_strings
{
	{ "Vertical", CameraOutput::CAMERA_OUTPUT_VERTICAL},
	{ "Horizontal", CameraOutput::CAMERA_OUTPUT_HORIZONTAL },
	{ "Zoom", CameraOutput::CAMERA_OUTPUT_ZOOM },
	{ "Select", CameraOutput::CAMERA_OUTPUT_SELECT },
	{ "Cancel", CameraOutput::CAMERA_OUTPUT_CANCEL }
};

Camera::Camera()
{

	int2_cursor_position = Int2(-1, -1);

	p_asst_selected_asset = nullptr;

	b_cursor_updated = true;

	vec3_position = Vector3(0, 0, 1);

	m_i_m_s_i_outputs = std::map<int, std::map<std::string, int>>();

	m_i_m_s_f_sensitivities = std::map<int, std::map<std::string, float>>();
}

Camera::Camera(std::filesystem::path path_roaming_data_path)
{
	int2_cursor_position = Int2(-1, -1);

	p_asst_selected_asset = nullptr;

	b_cursor_updated = true;

	this->path_roaming_data_path = path_roaming_data_path;

	vec3_position = Vector3(0, 0, 1);

	m_i_m_s_i_outputs = std::map<int, std::map<std::string, int>>();

	m_i_m_s_f_sensitivities = std::map<int, std::map<std::string, float>>();

	nlohmann::json json_json;

	std::ifstream ifst_ifstream((path_roaming_data_path.string() + "\\JSON\\Controller\\camera.json").c_str());

	json_json = nlohmann::json::parse(ifst_ifstream);

	for (int i = 0; i < Controller::INPUT_TYPE_NUM_INPUT_TYPES; i++)
	{
		if (!json_json.contains(Controller::m_i_s_input_type_strings.at(i)))
		{
			continue;
		}

		for (auto& [name, key] : json_json.at(Controller::m_i_s_input_type_strings.at(i)).items())
		{
			m_i_m_s_i_outputs[i][name] = (int)m_s_cotp_output_type_strings.at(key.at("output"));
			m_i_m_s_f_sensitivities[i][name] = key.at("sensitivity");
		}
	}

	b_cursor_updated = true;
}

Vector3 Camera::vec3_get_position()
{
	return vec3_position;
}

Int2 Camera::int2_get_cursor_position()
{
	return int2_cursor_position;
}

bool Camera::b_is_cursor_updated()
{
	if (b_cursor_updated)
	{
		b_cursor_updated = false;

		return true;
	}

	return false;
}

void Camera::update(Controller cntr_controller, sf::Vector2i vc2i_mouse_position, Vector2 vec2_window_size, float f_delta_time, int i_tile_size)
{
	float f_vertical = 0.0f;
	float f_horizontal = 0.0f;
	float f_zoom = 0.0f;

	for (int i = 0; i < Controller::INPUT_TYPE_NUM_INPUT_TYPES; i++)
	{
		if (!m_i_m_s_i_outputs.contains(i))
		{
			continue;
		}

		for (auto& [name, key] : m_i_m_s_i_outputs[i])
		{
			switch (key)
			{
			case (int)CameraOutput::CAMERA_OUTPUT_VERTICAL:
				f_vertical += cntr_controller.f_get_input(i, name) * m_i_m_s_f_sensitivities[i][name];
				break;
			case (int)CameraOutput::CAMERA_OUTPUT_HORIZONTAL:
				f_horizontal += cntr_controller.f_get_input(i, name) * m_i_m_s_f_sensitivities[i][name];
				break;
			case (int)CameraOutput::CAMERA_OUTPUT_ZOOM:
				f_zoom += cntr_controller.f_get_input(i, name) * m_i_m_s_f_sensitivities[i][name];
				break;
			case (int)CameraOutput::CAMERA_OUTPUT_SELECT:
				if (cntr_controller.b_is_input_changed(i, name) && cntr_controller.b_is_input_neutral(i, name))
				{
					select(vc2i_mouse_position, vec2_window_size, i_tile_size);
				}
				break;
			case (int)CameraOutput::CAMERA_OUTPUT_CANCEL:
				if (cntr_controller.b_is_input_changed(i, name) && cntr_controller.b_is_input_neutral(i, name))
				{
					cancel();
				}
				break;
			default:
				break;
			}
		}
	}

	vec3_position = Vector3(vec3_position.x + f_horizontal, vec3_position.y + f_vertical, vec3_position.z + f_zoom);

	if (vec3_position.z < -0.9f)
	{
		vec3_position = Vector3(vec3_position.x, vec3_position.y, -0.9f);
	}
}

void Camera::select(sf::Vector2i vc2i_mouse_position, Vector2 vec2_window_size, int i_tile_size)
{
	// don't handle clicks outside of the window
	if (vc2i_mouse_position.x < 0 || vc2i_mouse_position.x > vec2_window_size.x || vc2i_mouse_position.y < 0 || vc2i_mouse_position.y > vec2_window_size.x)
	{
		return;
	}

	std::shared_ptr p_menu_menu = Globals::glob_get_globals().p_menu_get_menu();

	sf::FloatRect frct_iconbox_bounds = p_menu_menu->frct_get_iconbox_bounds(vec2_window_size, "Toolbar");
	sf::FloatRect frct_namebox_bounds = p_menu_menu->frct_get_namebox_bounds(vec2_window_size, "Toolbar");
	std::map<int, sf::FloatRect> m_i_frct_icon_bounds = p_menu_menu->m_i_frct_get_icon_bounds(vec2_window_size, "Toolbar");

	if (frct_namebox_bounds.contains((sf::Vector2f)vc2i_mouse_position)) return;

	if (frct_iconbox_bounds.contains((sf::Vector2f)vc2i_mouse_position))
	{
		for (int i = 0; i < m_i_frct_icon_bounds.size(); i++)
		{
			if (m_i_frct_icon_bounds[i].contains((sf::Vector2f)vc2i_mouse_position))
			{
				if (std::shared_ptr<Tile> p_tile_tile = std::dynamic_pointer_cast<Tile>(get_selected_asset()))
				{
					std::map<int, std::string> m_i_s_garrison_indices = std::map<int, std::string>();

					int i_index = 1;

					if (p_tile_tile->p_grsn_get_garrison(Globals::glob_get_globals().plyr_get_turn_player()->s_get_name())->m_s_p_unit_get_units().size() > 0)
					{
						m_i_s_garrison_indices[i_index++] = Globals::glob_get_globals().plyr_get_turn_player()->s_get_name();
					}

					for (int j = 0; j < Globals::glob_get_globals().p_map_get_current_map()->m_i_s_get_turn_order().size(); j++)
					{
						std::string s_player = Globals::glob_get_globals().p_map_get_current_map()->m_i_s_get_turn_order()[j];
						if (Globals::glob_get_globals().plyr_get_turn_player()->s_get_name() == s_player) { continue; }
						if (p_tile_tile->p_grsn_get_garrison(s_player)->m_s_p_unit_get_units().size() > 0)
						{
							m_i_s_garrison_indices[i_index++] = s_player;
						}
					}

					if (i == 0)
					{
						p_asst_selected_asset = std::make_shared<SoilCover>(p_tile_tile->scvr_get_soil_cover());

						b_cursor_updated = true;
					}
					else if (m_i_s_garrison_indices.contains(i))
					{
						p_asst_selected_asset = p_tile_tile->p_grsn_get_garrison(m_i_s_garrison_indices[i]);

						b_cursor_updated = true;
					}
				}
				else if (std::shared_ptr<SoilCover> p_tile_tile = std::dynamic_pointer_cast<SoilCover>(get_selected_asset()))
				{
					Globals::glob_get_globals().edit_soil_cover("Toolbar", i);

					b_cursor_updated = true;
				}
				else if (std::shared_ptr<Garrison> p_grsn_garrison = std::dynamic_pointer_cast<Garrison>(get_selected_asset()))
				{
					std::shared_ptr<Unit> p_unit_unit = p_grsn_garrison->p_unit_get_unit(std::stoi(Globals::glob_get_globals().p_menu_get_menu()->m_i_s_get_toolbar_sprite_names(vec2_window_size, "Toolbar").at(i)));
					
					p_asst_selected_asset = p_unit_unit;

					b_cursor_updated = true;
				}
				else if (std::shared_ptr<Unit> p_unit_unit = std::dynamic_pointer_cast<Unit>(get_selected_asset()))
				{
					int i_mobilize_index = p_unit_unit->i_get_mobility() > 0 ? 1 : -1;

					if (i == 0)
					{
						std::shared_ptr<Garrison> p_grsn_garrison = Globals::glob_get_globals().p_map_get_current_map()->p_tile_get_tile(int2_cursor_position)->p_grsn_get_garrison(p_unit_unit->s_get_player());

						p_grsn_garrison->remove_unit(p_unit_unit);

						p_asst_selected_asset = p_grsn_garrison;

						b_cursor_updated = true;
					}
					else if (i == i_mobilize_index)
					{
						p_asst_selected_asset = std::make_shared<MenuMode>("mobilize", MenuMode::MenuModes::MENU_MODE_MOBILIZE, p_unit_unit);

						b_cursor_updated = true;
					}
				}
				else if (std::shared_ptr<MenuMode> p_mnmd_menu_mode = std::dynamic_pointer_cast<MenuMode>(get_selected_asset()))
				{
					if (std::shared_ptr<Unit> p_unit_unit = std::dynamic_pointer_cast<Unit>(p_mnmd_menu_mode->p_asst_get_operator()))
					{
						if (p_mnmd_menu_mode->mnmd_get_mode() == MenuMode::MenuModes::MENU_MODE_MOBILIZE)
						{
							if (i == 0)
							{
								std::shared_ptr<Garrison> p_grsn_garrison = Globals::glob_get_globals().p_map_get_current_map()->p_tile_get_tile(int2_cursor_position)->p_grsn_get_garrison(p_unit_unit->s_get_player());

								p_grsn_garrison->remove_unit(p_unit_unit);

								p_asst_selected_asset = p_grsn_garrison;

								b_cursor_updated = true;
							}
						}
					}
				}
			}
		}
	}
	else
	{
		if (sprt_soilcovers.getGlobalBounds().contains((sf::Vector2f)vc2i_mouse_position))
		{
			Vector2 relative_mouse_position = Vector2((vc2i_mouse_position.x - sprt_soilcovers.getGlobalBounds().left) / sprt_soilcovers.getScale().x,
													((vc2i_mouse_position.y - sprt_soilcovers.getGlobalBounds().top) / sprt_soilcovers.getScale().y));

			Vector2 vec2_soilcover_dimensions = Vector2(sprt_soilcovers.getTexture()->getSize().x / (float)i_tile_size, sprt_soilcovers.getTexture()->getSize().y / (float)i_tile_size);

			Int2 int2_clicked_position = Int2((int)(relative_mouse_position.x /  (float)i_tile_size), (int)(relative_mouse_position.y / (float)i_tile_size));

			if (std::shared_ptr<MenuMode> p_mnmd_menu_mode = std::dynamic_pointer_cast<MenuMode>(get_selected_asset()))
			{
				if (std::shared_ptr<Unit> p_unit_unit = std::dynamic_pointer_cast<Unit>(p_mnmd_menu_mode->p_asst_get_operator()))
				{
					if (p_mnmd_menu_mode->mnmd_get_mode() == MenuMode::MenuModes::MENU_MODE_MOBILIZE)
					{
						std::shared_ptr<Tile> p_tile_selected = Globals::glob_get_globals().p_map_get_current_map()->p_tile_get_tile(int2_cursor_position);
						std::shared_ptr<Tile> p_tile_destination = Globals::glob_get_globals().p_map_get_current_map()->p_tile_get_tile(int2_clicked_position);

						if (p_tile_selected->b_move_unit(p_unit_unit, p_tile_destination))
						{
							if (p_unit_unit->i_get_mobility() > 0)
							{
								p_asst_selected_asset = std::make_shared<MenuMode>("mobilize", MenuMode::MenuModes::MENU_MODE_MOBILIZE, p_unit_unit);
							}
							else
							{
								p_asst_selected_asset = p_unit_unit;
							}

							int2_cursor_position = int2_clicked_position;

							b_cursor_updated = true;

							return;
						}
					}
				}
			}

			int2_cursor_position = int2_clicked_position;

			p_asst_selected_asset = Globals::glob_get_globals().p_map_get_current_map()->p_tile_get_tile(int2_cursor_position);

			b_cursor_updated = true;
		}
	}
}

void Camera::cancel()
{
	if (int2_cursor_position.x >= 0 && int2_cursor_position.y >= 0)
	{
		if (std::shared_ptr<Unit> p_unit_unit = std::dynamic_pointer_cast<Unit>(Globals::glob_get_globals().p_cmra_get_camera()->get_selected_asset()))
		{
			p_asst_selected_asset = Globals::glob_get_globals().p_map_get_current_map()->p_tile_get_tile(int2_cursor_position)->p_grsn_get_garrison(p_unit_unit->s_get_player());

			b_cursor_updated = true;
		}
		else if (std::dynamic_pointer_cast<Tile>(Globals::glob_get_globals().p_cmra_get_camera()->get_selected_asset()) == nullptr)
		{
			p_asst_selected_asset = Globals::glob_get_globals().p_map_get_current_map()->p_tile_get_tile(int2_cursor_position);

			b_cursor_updated = true;
		}
		else if (std::shared_ptr<MenuMode> p_mnmd_menu_mode = std::dynamic_pointer_cast<MenuMode>(get_selected_asset()))
		{
			if (std::shared_ptr<Unit> p_unit_unit = std::dynamic_pointer_cast<Unit>(p_mnmd_menu_mode->p_asst_get_operator()))
			{
				if (p_mnmd_menu_mode->mnmd_get_mode() == MenuMode::MenuModes::MENU_MODE_MOBILIZE)
				{
					p_asst_selected_asset = Globals::glob_get_globals().p_map_get_current_map()->p_tile_get_tile(int2_cursor_position)->p_grsn_get_garrison(p_unit_unit->s_get_player());

					b_cursor_updated = true;
				}
			}
		}
		else
		{
			int2_cursor_position = Int2(-1, -1);

			p_asst_selected_asset = nullptr;

			b_cursor_updated = true;
		}

	}
	else
	{
		int2_cursor_position = Int2(-1, -1);

		p_asst_selected_asset = nullptr;

		b_cursor_updated = true;
	}
}

void Camera::late_update(int i_tile_size)
{
	sprt_soilcovers.setPosition(-vec3_position.x, vec3_position.y);
	sprt_units.setPosition(-vec3_position.x, vec3_position.y);

	sprt_soilcovers.setScale(1 + vec3_position.z, 1 + vec3_position.z);
	sprt_units.setScale((1 + vec3_position.z) / 8, (1 + vec3_position.z) / 8);
}

void Camera::set_soilcovers(std::shared_ptr<sf::Texture> p_txtr_texture)
{
	sprt_soilcovers.setTexture(*p_txtr_texture);
}

void Camera::set_units(std::shared_ptr<sf::Texture> p_txtr_texture)
{
	sprt_units.setTexture(*p_txtr_texture);
}

sf::Sprite Camera::sprt_get_soilcovers_sprite()
{
	return sprt_soilcovers;
}

sf::Sprite Camera::sprt_get_units_sprite()
{
	return sprt_units;
}

std::shared_ptr<Asset> Camera::get_selected_asset()
{
	return p_asst_selected_asset;
}