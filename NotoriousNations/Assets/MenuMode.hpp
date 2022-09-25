#pragma once
#ifndef MenuMode_hpp
#define MenuMode_hpp

#include "Asset.hpp"

class MenuMode : public Asset
{
public:
	enum class MenuModes
	{
		MENU_MODE_NONE = -1,
		MENU_MODE_MOBILIZE,
		MENU_MODE_NUM_MODES
	};

	MenuMode();
	MenuMode(std::string s_name, MenuModes mnmd_menu_mode, std::shared_ptr<Asset> p_asst_operator);

	MenuModes mnmd_get_mode();

	std::shared_ptr<Asset> p_asst_get_operator();

private:
	const MenuModes mnmd_menu_mode;

	std::shared_ptr<Asset> p_asst_operator;
};

#endif