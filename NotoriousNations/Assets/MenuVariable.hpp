#pragma once
#ifndef MenuVariable_hpp
#define MenuVariable_hpp\

#include "MenuCalculation.hpp"

#include <map>

struct MenuVariable {
	std::string s_name;
	std::string s_value;
	float f_output;
	std::map<int, MenuCalculation> m_i_mncl_menu_calculations;
};

#endif