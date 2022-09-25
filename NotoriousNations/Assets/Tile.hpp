#pragma once
#ifndef Tile_hpp
#define Tile_hpp

#include "Asset.hpp"

#include "Player.hpp"
#include "Garrison.hpp"
#include "Int2.hpp"
#include "SoilCover.hpp"

class Tile : public Asset
{
public:
	Tile();
	Tile(std::string s_name, Int2 position, SoilCover scvr_soil_cover, std::string s_player);

	SoilCover scvr_get_soil_cover();

	void scvr_set_soil_cover(SoilCover scvr_soil_cover);

	Int2 int2_get_position();

	std::string s_get_player();

	void set_player(std::string s_player);

	std::map<std::string, std::shared_ptr<Garrison>> p_grsn_get_garrisons();

	std::shared_ptr<Garrison> p_grsn_get_garrison(std::string s_player);

	std::shared_ptr<Garrison> p_grsn_get_garrison(std::string s_player, std::string s_adjective);

	std::map<std::string, std::shared_ptr<Unit>> m_s_p_unit_get_war_units(std::shared_ptr<Player> p_plyr_player);

	std::map<std::string, std::shared_ptr<Unit>> m_s_p_unit_get_war_units(std::string s_player);

	std::map<std::string, std::shared_ptr<Unit>> m_s_p_unit_get_pact_units(std::shared_ptr<Player> p_plyr_player);

	std::map<std::string, std::shared_ptr<Unit>> m_s_p_unit_get_pact_units(std::string s_player);

	std::map<std::string, std::shared_ptr<Unit>> m_s_p_unit_get_peace_units(std::shared_ptr<Player> p_plyr_player);

	std::map<std::string, std::shared_ptr<Unit>> m_s_p_unit_get_peace_units(std::string s_player);

	bool b_can_mobilize(std::shared_ptr<Unit> p_unit_unit, std::shared_ptr<Tile> p_tile_tile);

	bool b_move_unit(std::shared_ptr<Unit> p_unit_unit, std::shared_ptr<Tile> p_tile_destination);

private:
	SoilCover scvr_soil_cover;

	std::string s_player;

	Int2 int2_position;

	std::map<std::string,std::shared_ptr<Garrison>> m_s_p_grsn_garrison;
};

#endif