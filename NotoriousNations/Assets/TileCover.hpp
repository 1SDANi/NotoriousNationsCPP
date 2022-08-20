#pragma once
#ifndef TileCover_hpp
#define TileCover_hpp

#include "AtlasYield.hpp"

class TileCover : public AtlasYield
{
public:
	TileCover();
	TileCover(std::string s_name, Int2 int2_atlas_coords);

	bool b_has_text(std::string s_text);

	std::string s_get_text(std::string s_text);

	std::map<std::string, std::string> m_s_s_get_all_texts();

	void set_text(std::string s_text, std::string s_value);

	void set_all_texts(std::map<std::string, std::string> m_s_s_yields);

	bool b_has_flag(std::string s_flag);

	bool s_get_flag(std::string s_flag);

	std::map<std::string, bool> m_s_b_get_all_flags();

	void set_flag(std::string s_flag, bool s_value);

	void set_all_flags(std::map<std::string, bool> m_s_b_yields);

private:
	std::map<std::string, std::string> m_s_s_texts;

	std::map<std::string, bool> m_s_b_flags;
};

#endif