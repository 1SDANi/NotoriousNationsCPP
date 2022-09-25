#pragma once
#ifndef Map_hpp
#define Map_hpp

#include "Asset.hpp"

#include "Int2.hpp"
#include "Tile.hpp"
#include "Player.hpp"

#include  <vector>
#include <filesystem>
#include <iostream>

#include <SFML/Graphics.hpp>

class Map : public Asset
{
public:
	Map();
	Map(std::string s_name, std::map<int, std::shared_ptr<Tile>> m_i_p_tile_tiles, std::map<std::string, std::shared_ptr<Player>> m_s_p_plyr_players,
		std::map<int, std::string> m_i_s_turn_order, int i_turn_player, std::string s_shape, int width);

	std::string s_get_shape();

	Int2 int2_get_size();

	std::shared_ptr<Tile> p_tile_get_tile(Int2 int2_coordinates);

	void set_soil_cover(Int2 int2_coordinates, SoilCover scvr_soil_cover, std::shared_ptr<sf::Texture> p_txtr_soil_cover_atlas, int i_tile_size);

	std::shared_ptr<sf::Texture> p_txtr_get_soil_cover_texture();

	std::shared_ptr<sf::Texture> p_txtr_get_units_texture();

	std::shared_ptr<Player> p_plyr_get_player(std::string s_name);

	std::map<int, std::string> m_i_s_get_turn_order();

	int i_get_turn_player();

	void update_soil_cover_texture(std::shared_ptr<sf::Texture> p_txtr_soil_cover_atlas, int i_tile_size);

	void update_units_texture(std::shared_ptr<sf::Texture> p_txtr_unit_type_atlas, int i_tile_size);

private:
	Int2 int2_size;

	std::string s_shape;

	std::shared_ptr<sf::Texture> p_txtr_soil_cover_texture;

	std::shared_ptr<sf::Texture> p_txtr_units_texture;

	std::map<int,std::shared_ptr<Tile>> m_i_p_tile_tiles;

	std::map<std::string, std::shared_ptr<Player>> m_s_p_plyr_players;

	std::map<int, std::string> m_i_s_turn_order;

	int i_turn_player;
};

#endif