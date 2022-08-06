#pragma once
#ifndef Tile_hpp
#define Tile_hpp

#include "Asset.hpp"

#include "Int2.hpp"
#include "SoilCover.hpp"

class Tile : Asset
{
public:
	Tile();
	Tile(std::string s_name, Int2 position, SoilCover scvr_soil_cover);

	SoilCover scvr_get_soil_cover();

	void scvr_set_soil_cover(SoilCover scvr_soil_cover);

	Int2 int2_get_position();

private:
	SoilCover scvr_soil_cover;

	Int2 int2_position;
};

#endif