#include "TileCover.hpp"

TileCover::TileCover() : AtlasYield()
{
	m_s_s_texts = std::map<std::string, std::string>();
	m_s_b_flags = std::map<std::string, bool>();
}


TileCover::TileCover(std::string s_name, Int2 int2_atlas_coords) : AtlasYield(s_name, int2_atlas_coords)
{
	std::wcout << std::to_wstring(int2_atlas_coords.x) << L" " << std::to_wstring(int2_atlas_coords.y) << L"\n";
	m_s_s_texts = std::map<std::string, std::string>();
	m_s_b_flags = std::map<std::string, bool>();
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

void TileCover::set_text(std::string s_text, std::string s_value)
{
	if (b_has_text(s_text))
	{
		m_s_s_texts[s_text] = s_value;
	}
	else
	{
		m_s_s_texts.emplace(s_text, s_value);
	}
}

void TileCover::set_all_texts(std::map<std::string, std::string> m_s_s_yields)
{
	for (std::pair<std::string, std::string> pair_s_s_pair : m_s_s_yields)
	{
		set_text(pair_s_s_pair.first, pair_s_s_pair.second);
	}
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

void TileCover::set_flag(std::string s_flag, bool s_value)
{
	if (b_has_flag(s_flag))
	{
		m_s_b_flags[s_flag] = s_value;
	}
	else
	{
		m_s_b_flags.emplace(s_flag, s_value);
	}
}

void TileCover::set_all_flags(std::map<std::string, bool> m_s_b_yields)
{
	for (std::pair<std::string, bool> pair_s_s_pair : m_s_b_yields)
	{
		set_flag(pair_s_s_pair.first, pair_s_s_pair.second);
	}
}