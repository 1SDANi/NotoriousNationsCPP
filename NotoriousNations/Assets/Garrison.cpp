#include "Garrison.hpp"

Garrison::Garrison()
{
	m_s_unit_units = std::map<std::string, Unit>();
}

Garrison::Garrison(std::string s_name) : Asset(s_name)
{
	m_s_unit_units = std::map<std::string, Unit>();
}

bool Garrison::b_has_unit(Unit unit_unit)
{
	for (std::pair<std::string, Unit> pair_i_unit_pair : m_s_unit_units)
	{
		if (pair_i_unit_pair.second.i_get_id() == unit_unit.i_get_id())
		{
			return true;
		}
	}

	return false;
}

std::map<std::string, Unit> Garrison::m_s_unit_get_units()
{
	return m_s_unit_units;
}

void Garrison::add_unit(Unit unit_unit)
{
	m_s_unit_units.emplace(std::to_string(unit_unit.i_get_id()), unit_unit);
}

void Garrison::remove_unit(Unit unit_unit)
{
	m_s_unit_units.erase(std::to_string(unit_unit.i_get_id()));
}