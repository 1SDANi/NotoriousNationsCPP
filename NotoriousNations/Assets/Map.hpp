#pragma once
#ifndef Map_hpp
#define Map_hpp

#include "Asset.hpp"

#include "Int2.hpp"
#include "Tile.hpp"

#include  <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

class Map : public Asset
{
public:
	Map();
	Map(std::string s_name, std::map<int, Tile> m_i_tile_tiles, std::string s_shape, int width);

	std::shared_ptr<sf::Texture> p_txtr_get_soil_cover_texture();

	void update_soil_cover_texture(std::shared_ptr<sf::Texture> p_txtr_soil_cover_atlas, int i_tile_size);

private:
	Int2 int2_size;

	std::string s_shape;

	std::shared_ptr<sf::Texture> p_txtr_soil_cover_texture;

	std::map<int,Tile> m_i_tile_tiles;
};

#endif