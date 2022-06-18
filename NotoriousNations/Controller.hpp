#pragma once
#ifndef Controller_hpp
#define Controller_hpp

#include "Bitmask.hpp"

#include "json.hpp"

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <fstream>

class Controller
{
public:
	enum InputType
	{
		INPUT_TYPE_NONE = -1,
		INPUT_TYPE_KEY,
		INPUT_TYPE_MOUSE_BUTTON,
		INPUT_TYPE_MOUSE_WHEEL,
		INPUT_TYPE_NUM_INPUT_TYPES
	};

	static const std::map<int, std::string> m_i_s_input_type_strings;

	Controller();

	Controller(std::filesystem::path path_roaming_data_path);

	void update();

	void update_mouse_wheel_input(int i_wheel, float f_delta);

	bool b_is_input_positive(int i_type, std::string s_input);

	bool b_is_input_negative(int i_type, std::string s_input);

	bool b_is_input_neutral(int i_type, std::string s_input);

	bool b_is_input_changed(int i_type, std::string s_input);

	float f_get_input(int i_type, std::string s_input);

	float f_get_deadzone(int i_type, std::string s_input);

private:
	std::map<int, std::map<std::string, std::map<std::string, int>>> m_i_m_s_m_s_i_inputs;

	std::map<int, std::map<std::string, float>> m_i_m_s_f_current_inputs;
	std::map<int, std::map<std::string, float>> m_i_m_s_f_previous_inputs;

	std::map<int, std::map<std::string, float>> m_i_m_s_f_deadzones;

	std::filesystem::path path_roaming_data_path;
};
#endif 