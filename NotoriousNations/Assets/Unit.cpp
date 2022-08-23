#include "Unit.hpp"

Unit::Unit() : Asset()
{
	set_s_training = std::set<std::string>();

	i_id = ID_tracker::idtr_get_id_tracker().get_new_id();

	refresh_mobility();
}

Unit::Unit(std::string s_name, UnitType untp_unit_type) : Asset(s_name)
{
	this->untp_unit_type = untp_unit_type;

	i_id = ID_tracker::idtr_get_id_tracker().get_new_id();

	refresh_mobility();
}

UnitType Unit::untp_get_unit_type()
{
	return untp_unit_type;
}

void Unit::set_unit_type(UnitType untp_unit_type)
{
	this->untp_unit_type = untp_unit_type;
}

int Unit::i_get_mobility()
{
	return i_mobility;
}

void Unit::refresh_mobility()
{
	if (untp_unit_type.b_has_yield("i_speed"))
	{
		i_mobility = untp_unit_type.i_get_yield("i_speed");
	}
	else
	{
		i_mobility = 0;
	}
}

bool Unit::reduce_mobility()
{
	if (i_mobility > 0)
	{
		i_mobility--;
		return true;
	}
	else
	{
		return false;
	}
}

bool Unit::reduce_mobility(int i_amount)
{
	if (i_mobility >= i_amount)
	{
		i_mobility -= i_amount;
		return true;
	}
	else
	{
		return false;
	}
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