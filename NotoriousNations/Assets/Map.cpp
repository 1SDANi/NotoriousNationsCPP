#include "Map.hpp"

Map::Map()
{
	int2_size = Int2(0, 0);
	v_tile_tiles = std::vector<Tile>();
}

Map::Map(std::string s_name, std::vector<Tile> v_tile_tiles, std::string s_shape, int width) : Asset(s_name)
{
	int2_size = Int2(width, static_cast<int>(v_tile_tiles.size() / width));

	this->s_shape = s_shape;

	this->v_tile_tiles = std::move(v_tile_tiles);
}