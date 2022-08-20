#include "UnitType.hpp"

AtlasYield::AtlasYield() : MultiYield()
{
	this->int2_atlas_coords = Int2(0, 0);
}

AtlasYield::AtlasYield(std::string s_name, Int2 int2_atlas_coords) : MultiYield(s_name)
{

	this->int2_atlas_coords = int2_atlas_coords;
}

Int2 AtlasYield::int2_get_atlas_coords()
{
	return int2_atlas_coords;
}