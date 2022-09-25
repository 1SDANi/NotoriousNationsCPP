#pragma once
#ifndef Camera_hpp
#define Camera_hpp

#include "Controller.hpp"

#include "Assets/Asset.hpp"
#include "Assets/Int2.hpp"
#include "Assets/Vector2.hpp"
#include "Assets/Vector3.hpp"
#include "Assets/MenuMode.hpp"

#include "json.hpp"

#include <filesystem>
#include <fstream>

class Camera
{
public:

	enum class CameraOutput
	{
		CAMERA_OUTPUT_NONE = -1,
		CAMERA_OUTPUT_VERTICAL,
		CAMERA_OUTPUT_HORIZONTAL,
		CAMERA_OUTPUT_ZOOM,
		CAMERA_OUTPUT_SELECT,
		CAMERA_OUTPUT_CANCEL,
		CAMERA_OUTPUT_NUM_OUTPUTS
	};

	static const std::map<Camera::CameraOutput, std::string> m_cotp_s_output_type_strings;
	static const std::map<std::string, Camera::CameraOutput> m_s_cotp_output_type_strings;

	Camera();

	Camera(std::filesystem::path path_roaming_data_path);

	void update(Controller cntr_controller, sf::Vector2i vc2i_mouse_position, Vector2 vec2_window_size, float f_delta_time, int i_tile_size);

	void late_update(int i_tile_size);

	void set_soilcovers(std::shared_ptr<sf::Texture> p_txtr_texture);

	void set_units(std::shared_ptr<sf::Texture> p_txtr_texture);

	sf::Sprite sprt_get_soilcovers_sprite();

	sf::Sprite sprt_get_units_sprite();

	Vector3 vec3_get_position();

	bool b_is_cursor_updated();

	Int2 int2_get_cursor_position();

	std::shared_ptr<Asset> get_selected_asset();

private:
	Vector3 vec3_position;

	float f_toolbar_height = 1.0f / 8.0f;

	std::map<int, std::map<std::string, int>> m_i_m_s_i_outputs;

	std::map<int, std::map<std::string, float>> m_i_m_s_f_sensitivities;

	sf::Sprite sprt_soilcovers;

	sf::Sprite sprt_units;

	std::filesystem::path path_roaming_data_path;

	std::shared_ptr<Asset> p_asst_selected_asset;

	void select(sf::Vector2i vc2i_mouse_position, Vector2 vec2_window_size, int i_tile_size);

	void cancel();

	Int2 int2_cursor_position;

	bool b_cursor_updated;
};
#endif 