#include "MultiYield.hpp"

MultiYield::MultiYield()
{
	m_s_i_yields = std::map<std::string, int>();
}


bool MultiYield::b_add_yield(std::string s_name)
{
	return b_add_yield(s_name, 0);
}

bool MultiYield::b_add_yield(std::string s_name, int i_value)
{
	if (b_has_yield(s_name))
	{
		return false;
	}
	else
	{
		return m_s_i_yields.emplace(s_name,i_value).second;
	}
}

bool MultiYield::b_remove_yield(std::string s_name)
{
	if (b_has_yield(s_name))
	{
		return m_s_i_yields.erase(s_name) > 0;
	}

	return false;
	
}

bool MultiYield::b_has_yield(std::string s_name)
{
	return m_s_i_yields.contains(s_name);
}

bool MultiYield::b_set_yield(std::string s_name, int i_value)
{
	if (b_has_yield(s_name))
	{
		return m_s_i_yields[s_name] = i_value;
	}
	else
	{
		return false;
	}
}

bool MultiYield::b_set_all_yields(std::map<std::string, int> m_s_i_yields)
{
	for (std::pair<std::string, int> pair_s_i_pair : m_s_i_yields)
	{
		if (b_set_yield(pair_s_i_pair.first, pair_s_i_pair.second))
		{
			continue;
		}

		return false;
	}

	return true;
}

bool  MultiYield::b_change_yield(std::string s_name, int i_change)
{
	if (b_has_yield(s_name))
	{
		return b_set_yield(s_name, i_get_yield(s_name) + i_change);
	}
	else
	{
		return false;
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