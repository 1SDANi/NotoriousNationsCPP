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
	Tile(std::string s_name, Int2 position, SoilCover slcv_soil_cover);

	SoilCover slcv_get_soil_cover();

	Int2 int2_get_position();

private:
	SoilCover slcv_soil_cover;

	Int2 int2_position;
};

#endif