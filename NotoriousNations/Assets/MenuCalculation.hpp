#pragma once
#ifndef MenuCalculation_hpp
#define MenuCalculation_hpp\

#include "Asset.hpp"

enum MenuOperation
{
	MENU_OPERATION_NONE = -1,
	MENU_OPERATION_ADD,
	MENU_OPERATION_SUBTRACT,
	MENU_OPERATION_MULTIPLY,
	MENU_OPERATION_DIVIDE,
	MENU_OPERATION_MAX_OPERATIONS
};

struct MenuCalculation {
	int i_operation = -1;
	std::string s_value;
};

#endif