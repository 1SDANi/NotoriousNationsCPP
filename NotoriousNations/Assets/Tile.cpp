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

bool Tile::b_can_mobilize(std::shared_ptr<Unit> p_unit_unit, std::shared_ptr<Tile> p_tile_tile)
{
	if (std::abs(int2_position.x - p_tile_tile->int2_get_position().x) > 1)
	{
		return false;
	}
	else if (std::abs(int2_position.y - p_tile_tile->int2_get_position().y) > 1)
	{
		return false;
	}
	else if (int2_position.x == p_tile_tile->int2_get_position().x && int2_position.y == p_tile_tile->int2_get_position().y)
	{
		return false;
	}
	else if (p_unit_unit->i_get_mobility() <= 0)
	{
		return false;
	}

	return true;
}

bool Tile::b_move_unit(std::shared_ptr<Unit> unit_unit, std::shared_ptr<Tile> p_tile_destination)
{
	if (b_can_mobilize(unit_unit, p_tile_destination))
	{
		return p_grsn_garrison->b_move_unit(unit_unit, p_tile_destination->p_grsn_get_garrison());
	}

	return false;
}