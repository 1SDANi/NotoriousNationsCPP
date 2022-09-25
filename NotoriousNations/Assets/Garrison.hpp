#pragma once
#ifndef Garrison_hpp
#define Garrison_hpp

#include "Unit.hpp"
#include "Player.hpp"

class Garrison : public Asset
{
public:
	Garrison();
	Garrison(std::string s_name);

	bool b_has_unit(std::shared_ptr<Unit> unit_unit);

	bool b_has_unit(int i_id);

	std::map<std::string, std::shared_ptr<Unit>> m_s_p_unit_get_units();

	std::shared_ptr<Unit> p_unit_get_unit(int i_id);

	void add_unit(std::shared_ptr<Unit> unit_unit, bool b_update_units_texture);

	void remove_unit(std::shared_ptr<Unit> unit_unit);

	bool b_move_unit(std::shared_ptr<Unit> unit_unit, std::shared_ptr<Garrison> p_grsn_destination);

private:
	std::map<std::string, std::shared_ptr<Unit>> m_s_p_unit_units;
};

#endif