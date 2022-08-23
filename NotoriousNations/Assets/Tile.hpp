#pragma once
#ifndef Tile_hpp
#define Tile_hpp

#include "Asset.hpp"

#include "Garrison.hpp"
#include "Int2.hpp"
#include "SoilCover.hpp"

class Tile : public Asset
{
public:
	Tile();
	Tile(std::string s_name, Int2 position, SoilCover scvr_soil_cover);

	SoilCover scvr_get_soil_cover();

	void scvr_set_soil_cover(SoilCover scvr_soil_cover);

	Int2 int2_get_position();

	std::shared_ptr<Garrison> p_grsn_get_garrison();

	bool b_can_mobilize(std::shared_ptr<Unit> p_unit_unit, std::shared_ptr<Tile> p_tile_tile);

	bool b_move_unit(std::shared_ptr<Unit> unit_unit, std::shared_ptr<Tile> p_tile_destination);

private:
	SoilCover scvr_soil_cover;

	Int2 int2_position;

	std::shared_ptr<Garrison> p_grsn_garrison;
};

#endif