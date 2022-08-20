#pragma once
#ifndef Garrison_hpp
#define Garrison_hpp

#include "Unit.hpp"

class Garrison : public Asset
{
public:
	Garrison();
	Garrison(std::string s_name);

	bool b_has_unit(Unit unit_unit);

	std::map<std::string, Unit> m_s_unit_get_units();

	void add_unit(Unit unit_unit);

	void remove_unit(Unit unit_unit);

private:
	std::map<std::string, Unit> m_s_unit_units;

};

#endif