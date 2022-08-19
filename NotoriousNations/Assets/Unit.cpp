#include "Unit.hpp"

Unit::Unit() : Asset()
{
	v_s_training = std::vector<std::string>();
}

Unit::Unit(std::string s_name, UnitType untp_unit_type) : Asset(s_name)
{
	this->untp_unit_type = untp_unit_type;
}

UnitType Unit::untp_get_unit_type()
{
	return untp_unit_type;
}

void Unit::add_training(std::string s_training)
{
	v_s_training.push_back(s_training);
}

std::vector<std::string> Unit::s_get_training()
{
	return v_s_training;
}

bool Unit::b_is_has_training(std::string s_key)
{
	return std::find(v_s_training.begin(), v_s_training.end(), s_key) != v_s_training.end();
}