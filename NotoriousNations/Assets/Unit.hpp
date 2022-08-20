#pragma once
#ifndef Unit_hpp
#define Unit_hpp

#include "UnitType.hpp"

#include "../ID_tracker.hpp"

class Unit : public Asset
{
public:
	Unit();

	Unit(std::string s_name, UnitType untp_unit_type);

	UnitType untp_get_unit_type();

	void set_unit_type(UnitType untp_unit_type);

	void add_training(std::string s_training);

	std::set<std::string> s_get_training();

	bool b_is_has_training(std::string s_key);

	int i_get_id();

private:
	UnitType untp_unit_type;

	int i_id;

	std::set<std::string> set_s_training;
};

#endif