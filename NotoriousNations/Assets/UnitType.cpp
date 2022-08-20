#include "UnitType.hpp"

UnitType::UnitType() : AtlasYield()
{
	s_combat_role = "";
	s_combat_range = "";

	m_s_m_s_i_specific_values = std::map<std::string, std::map<std::string, int>>();
	v_s_training = std::set<std::string>();
}

UnitType::UnitType(std::string s_name, Int2 int2_atlas_coords) : AtlasYield(s_name, int2_atlas_coords)
{
	s_combat_role = "";
	s_combat_range = "";

	m_s_m_s_i_specific_values = std::map<std::string, std::map<std::string, int>>();
	v_s_training = std::set<std::string>();
}

std::string UnitType::s_get_combat_role()
{
	return s_combat_role;
}

std::string UnitType::s_get_combat_range()
{
	return s_combat_range;
}

void UnitType::set_combat_role(std::string s_combat_role)
{
	this->s_combat_role = s_combat_role;
}

void UnitType::set_combat_range(std::string s_range)
{
	this->s_combat_range = s_combat_range;
}

std::map<std::string, std::map<std::string, int>> UnitType::m_s_i_get_specific_values()
{
	return m_s_m_s_i_specific_values;
}

std::map<std::string, int> UnitType::m_s_m_s_i_get_specific_specific_values(std::string s_key)
{
	if (b_has_specific_value(s_key))
	{
		return m_s_m_s_i_specific_values[s_key];
	}
	else
	{
		return std::map<std::string, int>();
	}
}

std::set<std::string> UnitType::s_get_training()
{
	return v_s_training;
}

bool UnitType::b_has_specific_value(std::string s_key)
{
	return m_s_m_s_i_specific_values.contains(s_key);
}

bool UnitType::b_has_specific_specific_value(std::string s_key, std::string s_specific_key)
{
	if (b_has_specific_value(s_key))
	{
		return m_s_m_s_i_specific_values.at(s_key).contains(s_specific_key);
	}

	return false;
}

bool UnitType::b_has_training(std::string s_key)
{
	return v_s_training.find(s_key) != v_s_training.end();
}

std::map<std::string, int> UnitType::m_s_i_get_specific_value(std::string s_key)
{
	if (b_has_specific_value(s_key))
	{
		return m_s_m_s_i_specific_values[s_key];
	}
	else
	{
		return std::map<std::string, int>();
	}
}

int UnitType::i_get_specific_specific_value(std::string s_key, std::string s_specific_key)
{
	if (b_has_specific_specific_value(s_key, s_specific_key))
	{
		return m_s_m_s_i_specific_values[s_key][s_specific_key];
	}
	else
	{
		return -1;
	}
}

void UnitType::set_specific_value(std::string s_key, std::map<std::string, int> s_i_value)
{
	if (b_has_specific_value(s_key))
	{
		m_s_m_s_i_specific_values[s_key] = s_i_value;
	}
	else
	{
		m_s_m_s_i_specific_values.emplace(s_key, s_i_value);
	}
}

void UnitType::set_specific_specific_value(std::string s_key, std::string s_specific_key, int i_value)
{
	if (b_has_specific_specific_value(s_key, s_specific_key))
	{
		m_s_m_s_i_specific_values[s_key][s_specific_key] = i_value;
	}
	else
	{
		m_s_m_s_i_specific_values[s_key].emplace(s_specific_key, i_value);
	}
}

void UnitType::add_training(std::string s_key)
{
	if (!b_has_training(s_key))
	{
		v_s_training.insert(s_key);
	}
}

void UnitType::set_all_specific_values(std::map<std::string, std::map<std::string, int>> m_s_m_s_i_specific_values)
{
	for (std::pair<std::string, std::map<std::string, int>> pair_s_m_s_i_pair : m_s_m_s_i_specific_values)
	{
		for (std::pair<std::string, int> pair_s_i_pair : pair_s_m_s_i_pair.second)
		{
			set_specific_specific_value(pair_s_m_s_i_pair.first, pair_s_i_pair.first, pair_s_i_pair.second);
		}
	}
}

void UnitType::set_all_training(std::set<std::string> v_s_training)
{
	for (std::string s_training : v_s_training)
	{
		add_training(s_training);
	}
}