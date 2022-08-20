#include "Tile.hpp"

Tile::Tile()
{
	int2_position = Int2(0, 0);

	p_grsn_garrison = std::make_shared<Garrison>();
}

Tile::Tile(std::string s_name, Int2 int2_position, SoilCover scvr_soil_cover) : Asset(s_name)
{
	this->int2_position = int2_position;
	this->scvr_soil_cover = scvr_soil_cover;

	p_grsn_garrison = std::make_shared<Garrison>();
}

SoilCover Tile::scvr_get_soil_cover()
{
	return scvr_soil_cover;
}

void Tile::scvr_set_soil_cover(SoilCover scvr_soil_cover)
{
	this->scvr_soil_cover = scvr_soil_cover;
}

Int2 Tile::int2_get_position()
{
	return int2_position;
}

std::shared_ptr<Garrison> Tile::p_grsn_get_garrison()
{
	return p_grsn_garrison;
}