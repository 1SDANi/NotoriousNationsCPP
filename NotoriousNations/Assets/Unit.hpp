#pragma once
#ifndef Unit_hpp
#define Unit_hpp

#include "UnitType.hpp"

#include "../ID_tracker.hpp"

class Tile;

class Unit : public Asset
{
public:
	Unit();

	Unit(std::string s_name, UnitType untp_unit_type, std::string s_player);

	UnitType untp_get_unit_type();

	void set_unit_type(UnitType untp_unit_type);

	void add_training(std::string s_training);

	std::set<std::string> s_get_training();

	std::string s_get_player();

	void set_player(std::string s_player);

	int i_get_mobility();

	void refresh_mobility();

	bool reduce_mobility();

	bool reduce_mobility(int i_amount);

	bool b_is_has_training(std::string s_key);

	bool b_can_move_to(Tile p_tile_tile);

	int i_get_id();

private:
	UnitType untp_unit_type;

	std::string s_player;

	int i_id;

	int i_mobility;

	std::set<std::string> set_s_training;
};

#endif