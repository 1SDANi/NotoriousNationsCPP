#include "Garrison.hpp"

#include "../Globals.hpp"

Garrison::Garrison()
{
	m_s_p_unit_units = std::map<std::string, std::shared_ptr<Unit>>();
}

Garrison::Garrison(std::string s_name) : Asset(s_name)
{
	m_s_p_unit_units = std::map<std::string, std::shared_ptr<Unit>>();
}

bool Garrison::b_has_unit(std::shared_ptr<Unit> unit_unit)
{
	return m_s_p_unit_units.contains(std::to_string(unit_unit->i_get_id()));
}

bool Garrison::b_has_unit(int i_id)
{
	return m_s_p_unit_units.contains(std::to_string(i_id));
}

std::map<std::string, std::shared_ptr<Unit>> Garrison::m_s_p_unit_get_units()
{
	return m_s_p_unit_units;
}

std::shared_ptr<Unit> Garrison::p_unit_get_unit(int i_id)
{
	if (b_has_unit(i_id))
	{
		return m_s_p_unit_units.at(std::to_string(i_id));
	}

	return nullptr;
}

void Garrison::add_unit(std::shared_ptr<Unit> unit_unit, bool b_update_units_texture)
{
	m_s_p_unit_units.emplace(std::to_string(unit_unit->i_get_id()), unit_unit);

	if (b_update_units_texture)
	{
		Globals::glob_get_globals().p_map_get_current_map()->update_units_texture(Globals::glob_get_globals().p_asmp_get_asset_maps()->p_txtr_get_unit_type_atlas(),
																				  Globals::glob_get_globals().p_asmp_get_asset_maps()->i_get_tile_size());
	}
	
}

void Garrison::remove_unit(std::shared_ptr<Unit> unit_unit)
{
	if (b_has_unit(unit_unit))
	{
		m_s_p_unit_units.erase(std::to_string(unit_unit->i_get_id()));

		Globals::glob_get_globals().p_map_get_current_map()->update_units_texture(Globals::glob_get_globals().p_asmp_get_asset_maps()->p_txtr_get_unit_type_atlas(),
																				  Globals::glob_get_globals().p_asmp_get_asset_maps()->i_get_tile_size());
	}
}

bool Garrison::b_move_unit(std::shared_ptr<Unit> unit_unit, std::shared_ptr<Garrison> p_grsn_destination)
{
	if (b_has_unit(unit_unit) && unit_unit->reduce_mobility())
	{
		p_grsn_destination->add_unit(unit_unit, true);

		m_s_p_unit_units.erase(std::to_string(unit_unit->i_get_id()));

		Globals::glob_get_globals().p_map_get_current_map()->update_units_texture(Globals::glob_get_globals().p_asmp_get_asset_maps()->p_txtr_get_unit_type_atlas(),
																				  Globals::glob_get_globals().p_asmp_get_asset_maps()->i_get_tile_size());

		return true;
	}

	return false;
}