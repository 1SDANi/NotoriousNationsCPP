#pragma once
#ifndef Unit_hpp
#define Unit_hpp

#include "UnitType.hpp"

class Unit : public Asset
{
public:
	Unit();

	Unit(std::string s_name, UnitType untp_unit_type);

	UnitType untp_get_unit_type();

	void add_training(std::string s_training);

	std::vector<std::string> s_get_training();

	bool b_is_has_training(std::string s_key);

private:
	UnitType untp_unit_type;

	std::vector<std::string> v_s_training;
};

#endif