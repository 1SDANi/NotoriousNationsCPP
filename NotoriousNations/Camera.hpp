#pragma once
#ifndef Camera_hpp
#define Camera_hpp

#include "Controller.hpp"

#include "Assets/Vector3.hpp"

#include "json.hpp"

#include <filesystem>
#include <fstream>

class Globals;
class Camera
{
public:
	Camera();

	Camera(std::filesystem::path path_roaming_data_path);

	void update(float f_delta_time);

	Vector3 vec3_get_position();

	enum CameraOutput
	{
		CAMERA_OUTPUT_NONE = -1,
		CAMERA_OUTPUT_VERTICAL,
		CAMERA_OUTPUT_HORIZONTAL,
		CAMERA_OUTPUT_ZOOM,
		CAMERA_OUTPUT_NUM_OUTPUTS
	};

private:
	Vector3 vec3_position;

	std::map<int, std::map<std::string, int>> m_i_m_s_i_outputs;

	std::map<int, std::map<std::string, float>> m_i_m_s_f_sensitivities;

	std::filesystem::path path_roaming_data_path;
};
#endif 