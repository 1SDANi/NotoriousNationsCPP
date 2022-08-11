#include "Camera.hpp"

#include "Globals.hpp"

const std::map<int, std::string> Camera::m_i_s_output_type_strings
{
	{ (int)CameraOutput::CAMERA_OUTPUT_VERTICAL, "Vertical" },
	{ (int)CameraOutput::CAMERA_OUTPUT_HORIZONTAL, "Horizontal" },
	{ (int)CameraOutput::CAMERA_OUTPUT_ZOOM, "Zoom" },
	{ (int)CameraOutput::CAMERA_OUTPUT_SELECT, "Select" },
	{ (int)CameraOutput::CAMERA_OUTPUT_CANCEL, "Cancel" }
};

const std::map<std::string, int> Camera::m_s_i_output_type_strings
{
	{ "Vertical", (int)CameraOutput::CAMERA_OUTPUT_VERTICAL},
	{ "Horizontal", (int)CameraOutput::CAMERA_OUTPUT_HORIZONTAL },
	{ "Zoom", (int)CameraOutput::CAMERA_OUTPUT_ZOOM },
	{ "Select", (int)CameraOutput::CAMERA_OUTPUT_SELECT },
	{ "Cancel", (int)CameraOutput::CAMERA_OUTPUT_CANCEL }
};

Camera::Camera()
{

	int2_cursor_position = Int2(-1, -1);

	b_cursor_updated = true;

	vec3_position = Vector3(0, 0, 1);

	m_i_m_s_i_outputs = std::map<int, std::map<std::string, int>>();

	m_i_m_s_f_sensitivities = std::map<int, std::map<std::string, float>>();
}

Camera::Camera(std::filesystem::path path_roaming_data_path)
{
	int2_cursor_position = Int2(-1, -1);

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
			m_i_m_s_i_outputs[i][name] = m_s_i_output_type_strings.at(key.at("output"));
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
				Globals::glob_get_globals().edit_soil_cover("Toolbar", i);

				b_cursor_updated = true;
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

			int2_cursor_position = int2_clicked_position;

			b_cursor_updated = true;
		}
	}
}

void Camera::cancel()
{
	int2_cursor_position = Int2(-1, -1);

	b_cursor_updated = true;
}

void Camera::late_update(int i_tile_size)
{
	sprt_soilcovers.setPosition(-vec3_position.x, vec3_position.y);

	sprt_soilcovers.setScale(1 + vec3_position.z, 1 + vec3_position.z);
}

void Camera::set_soilcovers(std::shared_ptr<sf::Texture> p_txtr_texture)
{
	sprt_soilcovers.setTexture(*p_txtr_texture);
}

sf::Sprite Camera::sprt_get_soilcovers_sprite()
{
	return sprt_soilcovers;
}