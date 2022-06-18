#include "Controller.hpp"

const std::map<int, std::string> Controller::m_i_s_input_type_strings
{
	{ INPUT_TYPE_KEY, "Key" },
	{ INPUT_TYPE_MOUSE_BUTTON, "Mouse Button" },
	{ INPUT_TYPE_MOUSE_WHEEL, "Mouse Wheel" }
};

Controller::Controller()
{
	m_i_m_s_m_s_i_inputs = std::map<int, std::map<std::string, std::map<std::string, int>>>();

	m_i_m_s_f_current_inputs = std::map<int, std::map<std::string, float>>();
	m_i_m_s_f_previous_inputs = std::map<int, std::map<std::string, float>>();

	m_i_m_s_f_deadzones = std::map<int, std::map<std::string, float>>();
}

Controller::Controller(std::filesystem::path path_roaming_data_path)
{
	this->path_roaming_data_path = path_roaming_data_path;

	m_i_m_s_m_s_i_inputs = std::map<int, std::map<std::string, std::map<std::string, int>>>();

	m_i_m_s_f_current_inputs = std::map<int, std::map<std::string, float>>();
	m_i_m_s_f_previous_inputs = std::map<int, std::map<std::string, float>>();

	m_i_m_s_f_deadzones = std::map<int, std::map<std::string, float>>();

	nlohmann::json json_json;

	std::ifstream ifst_ifstream((path_roaming_data_path.string() + "\\JSON\\Controller\\input.json").c_str());

	json_json = nlohmann::json::parse(ifst_ifstream);
	
	for (int i = 0; i < INPUT_TYPE_NUM_INPUT_TYPES; i++)
	{
		if (!json_json.contains(m_i_s_input_type_strings.at(i)))
		{
			continue;
		}

		for (auto& [name, key] : json_json.at(m_i_s_input_type_strings.at(i)).items())
		{
			m_i_m_s_m_s_i_inputs[i][name]["positive"] = key.at("positive");
			m_i_m_s_m_s_i_inputs[i][name]["negative"] = key.at("negative");
			m_i_m_s_m_s_i_inputs[i][name]["invert"] = (int)key.at("invert");
			m_i_m_s_f_deadzones[i][name] = key.at("deadzone");
		}
	}
}

void Controller::update()
{
	m_i_m_s_f_previous_inputs = m_i_m_s_f_current_inputs;

	for (auto& [name, key] : m_i_m_s_m_s_i_inputs[INPUT_TYPE_KEY])
	{
		float p = key["positive"] != -1 ? (float)sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key["positive"]) : 0;
		float n = key["negative"] != -1 ? 0 - (float)sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key["negative"]) : 0;
		if (key.contains("invert") && key["invert"])
		{
			p = 0 - p;
			n = 0 - n;
		}

		m_i_m_s_f_current_inputs[INPUT_TYPE_KEY][name] = p + n;
	}

	for (auto& [name, mouse_button] : m_i_m_s_m_s_i_inputs[INPUT_TYPE_MOUSE_BUTTON])
	{
		float p = mouse_button["positive"] != -1 ? (float)sf::Mouse::isButtonPressed((sf::Mouse::Button)mouse_button["positive"]) : 0.0f;
		float n = mouse_button["negative"] != -1 ? 0 - (float)sf::Mouse::isButtonPressed((sf::Mouse::Button)mouse_button["negative"]) : 0.0f;
		if (mouse_button.contains("invert") && mouse_button["invert"])
		{
			p = 0 - p;
			n = 0 - n;
		}

		m_i_m_s_f_current_inputs[INPUT_TYPE_MOUSE_BUTTON][name] = p + n;
	}

	for (auto& [name, mouse_wheel] : m_i_m_s_m_s_i_inputs[INPUT_TYPE_MOUSE_WHEEL])
	{
		m_i_m_s_f_current_inputs[INPUT_TYPE_MOUSE_WHEEL][name] = 0.0f;
	}
}

void Controller::update_mouse_wheel_input(int i_wheel, float f_delta)
{
	for (auto& [name, mouse_wheel] : m_i_m_s_m_s_i_inputs[INPUT_TYPE_MOUSE_WHEEL])
	{
		if (mouse_wheel["positive"] == i_wheel)
		{
			if (mouse_wheel.contains("invert") && mouse_wheel["invert"])
			{
				m_i_m_s_f_current_inputs[INPUT_TYPE_MOUSE_WHEEL][name] += f_delta;
			}
			else
			{
				m_i_m_s_f_current_inputs[INPUT_TYPE_MOUSE_WHEEL][name] -= f_delta;
			}
		}
		if (mouse_wheel["negative"] == i_wheel)
		{
			if (mouse_wheel.contains("invert") && mouse_wheel["invert"])
			{
				m_i_m_s_f_current_inputs[INPUT_TYPE_MOUSE_WHEEL][name] -= f_delta;
			}
			else
			{
				m_i_m_s_f_current_inputs[INPUT_TYPE_MOUSE_WHEEL][name] += f_delta;
			}
		}
	}
}

bool Controller::b_is_input_positive(int i_type, std::string s_input)
{
	return m_i_m_s_f_current_inputs[i_type][s_input] > m_i_m_s_f_deadzones[i_type][s_input];
}

bool Controller::b_is_input_negative(int i_type, std::string s_input)
{
	return m_i_m_s_f_current_inputs[i_type][s_input] < -m_i_m_s_f_deadzones[i_type][s_input];
}

bool Controller::b_is_input_neutral(int i_type, std::string s_input)
{
	return !(b_is_input_positive(i_type, s_input) || b_is_input_negative(i_type, s_input));
}

bool Controller::b_is_input_changed(int i_type, std::string s_input)
{
	bool a = m_i_m_s_f_current_inputs[i_type][s_input] - m_i_m_s_f_previous_inputs[i_type][s_input] > m_i_m_s_f_deadzones[i_type][s_input];
	bool b = m_i_m_s_f_current_inputs[i_type][s_input] - m_i_m_s_f_previous_inputs[i_type][s_input] < -m_i_m_s_f_deadzones[i_type][s_input];
	bool c = m_i_m_s_f_previous_inputs[i_type][s_input] - m_i_m_s_f_current_inputs[i_type][s_input] > m_i_m_s_f_deadzones[i_type][s_input];
	bool d = m_i_m_s_f_previous_inputs[i_type][s_input] - m_i_m_s_f_current_inputs[i_type][s_input] < -m_i_m_s_f_deadzones[i_type][s_input];

	return a || b || c || d;
}

float Controller::f_get_input(int i_type, std::string s_input)
{
	if (b_is_input_neutral(i_type, s_input))
	{
		return 0.0f;
	}
	else
	{
		return m_i_m_s_f_current_inputs[i_type][s_input];
	}
}

float Controller::f_get_deadzone(int i_type, std::string s_input)
{
	return m_i_m_s_f_deadzones[i_type][s_input];
}