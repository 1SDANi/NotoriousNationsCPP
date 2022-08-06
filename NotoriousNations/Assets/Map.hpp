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
	Map(std::string s_name, std::map<int, std::shared_ptr<Tile>> m_i_p_tile_tiles, std::string s_shape, int width);

	std::shared_ptr<Tile> p_tile_get_tile(Int2 int2_coordinates);

	void set_soil_cover(Int2 int2_coordinates, SoilCover scvr_soil_cover, std::shared_ptr<sf::Texture> p_txtr_soil_cover_atlas, int i_tile_size);

	std::shared_ptr<sf::Texture> p_txtr_get_soil_cover_texture();

	void update_soil_cover_texture(std::shared_ptr<sf::Texture> p_txtr_soil_cover_atlas, int i_tile_size);

private:
	Int2 int2_size;

	std::string s_shape;

	std::shared_ptr<sf::Texture> p_txtr_soil_cover_texture;

	std::map<int,std::shared_ptr<Tile>> m_i_p_tile_tiles;
};

#endif