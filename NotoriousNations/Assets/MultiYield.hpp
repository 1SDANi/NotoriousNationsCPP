#pragma once
#ifndef MultiYield_hpp
#define MultiYield_hpp

#include "Asset.hpp"

#include <map>
#include <string>
#include <vector>

class MultiYield : public Asset
{
public:
	MultiYield();
	MultiYield(std::string s_name);

	bool b_add_yield(std::string s_name);

	bool b_add_yield(std::string s_name, int i_value);

	bool b_remove_yield(std::string s_name);

	bool b_has_yield(std::string s_name);

	int i_get_yield(std::string s_name);

	std::map<std::string, int> m_s_i_get_all_yields();

	bool b_set_yield(std::string s_name, int i_value);

	bool b_set_all_yields(std::map<std::string, int> m_s_i_yields);

	bool b_change_yield(std::string s_name, int i_change);

private:
	std::map<std::string, int> m_s_i_yields;
};

#endif