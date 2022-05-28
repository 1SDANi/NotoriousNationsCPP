#pragma once
#ifndef Map_hpp
#define Map_hpp

#include "Asset.hpp"

#include "Int2.hpp"
#include "Tile.hpp"

#include <vector>

class Map : public Asset
{
public:
	Map();
	Map(std::string s_name, std::vector<Tile> v_tile_tiles, std::string s_shape, int width);

private:
	Int2 int2_size;

	std::string s_shape;

	std::vector<Tile> v_tile_tiles;
};

#endif