#pragma once
#ifndef UnitType_hpp
#define UnitType_hpp

#include "Asset.hpp"

#include "Int2.hpp"

#include <map>
#include <vector>
#include <algorithm>

class UnitType : public Asset
{
public:
	UnitType();
	UnitType(std::string s_name);

	std::string s_get_combat_role();
	std::string s_get_combat_range();

	void set_combat_role(std::string s_combat_role);
	void set_combat_range(std::string s_combat_range);

	std::map<std::string, int> m_s_i_get_generic_values();
	std::map<std::string, std::map<std::string, int>> m_s_i_get_specific_values();
	std::map<std::string, int> m_s_m_s_i_get_specific_specific_values(std::string s_key);
	std::vector<std::string> s_get_training();

	bool b_has_generic_value(std::string s_key);
	bool b_has_specific_value(std::string s_key);
	bool b_has_specific_specific_value(std::string s_key, std::string s_specific_key);
	bool b_has_training(std::string s_key);

	int i_get_generic_value(std::string s_key);
	std::map<std::string, int> m_s_i_get_specific_value(std::string s_key);
	int i_get_specific_specific_value(std::string s_key, std::string s_specific_key);

	void set_generic_value(std::string s_key, int i_value);
	void set_specific_value(std::string s_key, std::map<std::string, int> s_i_value);
	void set_specific_specific_value(std::string s_key, std::string s_specific_key, int i_value);
	void add_training(std::string s_key);

	void set_all_generic_values(std::map<std::string, int> m_s_i_generic_values);
	void set_all_specific_values(std::map<std::string, std::map<std::string, int>> m_s_m_s_i_specific_values);
	void set_all_training(std::vector<std::string> v_s_training);

private:
	std::string s_combat_role;
	std::string s_combat_range;

	std::map<std::string, int> m_s_i_generic_values;
	std::map<std::string, std::map<std::string, int>> m_s_m_s_i_specific_values;
	std::vector<std::string> v_s_training;
};

#endif