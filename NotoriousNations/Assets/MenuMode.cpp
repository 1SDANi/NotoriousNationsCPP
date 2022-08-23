#include "MenuMode.hpp"

MenuMode::MenuMode() : i_menu_mode(-1), p_asst_operator(p_asst_operator)
{
}

MenuMode::MenuMode(std::string s_name, int i_menu_mode, std::shared_ptr<Asset> p_asst_operator) : Asset(s_name), i_menu_mode(i_menu_mode), p_asst_operator(p_asst_operator)
{
}

int MenuMode::i_get_mode()
{
	return i_menu_mode;
}

std::shared_ptr<Asset> MenuMode::p_asst_get_operator()
{
	return p_asst_operator;
}