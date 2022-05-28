#include "Tile.hpp"

Tile::Tile()
{
	int2_position = Int2(0, 0);
}

Tile::Tile(std::string s_name, Int2 int2_position, SoilCover slcv_soil_cover) : Asset(s_name)
{
	this->int2_position = int2_position;
	this->slcv_soil_cover = slcv_soil_cover;
}

SoilCover Tile::slcv_get_soil_cover()
{
	return slcv_soil_cover;
}

Int2 Tile::int2_get_position()
{
	return int2_position;
}