#include "TileCover.hpp"

TileCover::TileCover() : MultiYield()
{
	int2_atlas_coords = Int2(0, 0);
	m_s_s_texts = std::map<std::string, std::string>();
	m_s_b_flags = std::map<std::string, bool>();
}


TileCover::TileCover(std::string s_name, Int2 int2_atlas_coords) : MultiYield(s_name)
{
	std::wcout << std::to_wstring(int2_atlas_coords.x) << L" " << std::to_wstring(int2_atlas_coords.y) << L"\n";
	this->int2_atlas_coords = int2_atlas_coords;
	m_s_s_texts = std::map<std::string, std::string>();
	m_s_b_flags = std::map<std::string, bool>();
}

Int2 TileCover::int2_get_atlas_coords()
{
	return int2_atlas_coords;
}

bool TileCover::b_has_text(std::string s_text)
{
	return m_s_s_texts.contains(s_text);
}

std::string TileCover::s_get_text(std::string s_text)
{
	if (b_has_text(s_text))
	{
		return m_s_s_texts[s_text];
	}
	else
	{
		return "-1";
	}
}

std::map<std::string, std::string> TileCover::m_s_s_get_all_texts()
{
	return m_s_s_texts;
}

bool TileCover::b_set_text(std::string s_text, std::string s_value)
{
	if (b_has_yield(s_text))
	{
		m_s_s_texts[s_text] = s_value;
		return true;
	}
	else
	{
		return m_s_s_texts.emplace(s_text, s_value).second;
	}
}

bool TileCover::b_set_all_texts(std::map<std::string, std::string> m_s_s_yields)
{
	for (std::pair<std::string, std::string> pair_s_s_pair : m_s_s_yields)
	{
		if (b_set_text(pair_s_s_pair.first, pair_s_s_pair.second))
		{
			continue;
		}

		return false;
	}

	return true;
}

bool TileCover::b_has_flag(std::string s_flag)
{
	return m_s_b_flags.contains(s_flag);
}

bool TileCover::s_get_flag(std::string s_flag)
{
	if (b_has_flag(s_flag))
	{
		return m_s_b_flags[s_flag];
	}
	else
	{
		return false;
	}
}

std::map<std::string, bool> TileCover::m_s_b_get_all_flags()
{
	return m_s_b_flags;
}

bool TileCover::b_set_flag(std::string s_flag, bool s_value)
{
	if (b_has_yield(s_flag))
	{
		return false;
	}
	else
	{
		return m_s_b_flags.emplace(s_flag, s_value).second;
	}
}

bool TileCover::b_set_all_flags(std::map<std::string, bool> m_s_b_yields)
{
	for (std::pair<std::string, bool> pair_s_s_pair : m_s_b_yields)
	{
		if (b_set_flag(pair_s_s_pair.first, pair_s_s_pair.second))
		{
			continue;
		}

		return false;
	}

	return true;
}