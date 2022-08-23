#include "MultiYield.hpp"

MultiYield::MultiYield()
{
	m_s_i_yields = std::map<std::string, int>();
}

MultiYield::MultiYield(std::string s_name) : Asset(s_name)
{
	m_s_i_yields = std::map<std::string, int>();
}

void MultiYield::remove_yield(std::string s_name)
{
	if (b_has_yield(s_name))
	{
		m_s_i_yields.erase(s_name);
	}
	
}

bool MultiYield::b_has_yield(std::string s_name)
{
	return m_s_i_yields.contains(s_name);
}

void MultiYield::set_yield(std::string s_name, int i_value)
{
	if (b_has_yield(s_name))
	{
		m_s_i_yields[s_name] = i_value;
	}
	else
	{
		m_s_i_yields.emplace(s_name, i_value);
	}
}

void MultiYield::set_all_yields(std::map<std::string, int> m_s_i_yields)
{
	for (std::pair<std::string, int> pair_s_i_pair : m_s_i_yields)
	{
		set_yield(pair_s_i_pair.first, pair_s_i_pair.second);
	}
}

void MultiYield::change_yield(std::string s_name, int i_change)
{
	if (b_has_yield(s_name))
	{
		set_yield(s_name, i_get_yield(s_name) + i_change);
	}
}

int MultiYield::i_get_yield(std::string s_name)
{
	if (b_has_yield(s_name))
	{
		return m_s_i_yields[s_name];
	}
	else
	{
		return -1;
	}
}

std::map<std::string, int> MultiYield::m_s_i_get_all_yields()
{
	return m_s_i_yields;
}