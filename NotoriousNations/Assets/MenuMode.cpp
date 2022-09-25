#include "MenuMode.hpp"

MenuMode::MenuMode() : mnmd_menu_mode(MenuModes::MENU_MODE_NONE), p_asst_operator(p_asst_operator)
{
}

MenuMode::MenuMode(std::string s_name, MenuModes mnmd_menu_mode, std::shared_ptr<Asset> p_asst_operator) : Asset(s_name), mnmd_menu_mode(mnmd_menu_mode), p_asst_operator(p_asst_operator)
{
}

MenuMode::MenuModes MenuMode::mnmd_get_mode()
{
	return mnmd_menu_mode;
}

std::shared_ptr<Asset> MenuMode::p_asst_get_operator()
{
	return p_asst_operator;
}