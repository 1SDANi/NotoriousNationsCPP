#include "Unit.hpp"

Unit::Unit() : Asset()
{
	set_s_training = std::set<std::string>();

	i_id = ID_tracker::idtr_get_id_tracker().get_new_id();
}

Unit::Unit(std::string s_name, UnitType untp_unit_type) : Asset(s_name)
{
	this->untp_unit_type = untp_unit_type;

	i_id = ID_tracker::idtr_get_id_tracker().get_new_id();
}

UnitType Unit::untp_get_unit_type()
{
	return untp_unit_type;
}

void Unit::set_unit_type(UnitType untp_unit_type)
{
	this->untp_unit_type = untp_unit_type;
}

void Unit::add_training(std::string s_training)
{
	set_s_training.insert(s_training);
}

std::set<std::string> Unit::s_get_training()
{
	return set_s_training;
}

bool Unit::b_is_has_training(std::string s_key)
{
	return std::find(set_s_training.begin(), set_s_training.end(), s_key) != set_s_training.end();
}

int Unit::i_get_id()
{
	return i_id;
}