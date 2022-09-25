#include "Map.hpp"

#include "../Globals.hpp"

Map::Map() : Asset()
{
	int2_size = Int2(0, 0);
	this->s_shape = "ERROR";
	m_i_p_tile_tiles = std::map<int, std::shared_ptr<Tile>>();
	m_s_p_plyr_players = std::map<std::string, std::shared_ptr<Player>>();
	m_i_s_turn_order = std::map<int, std::string>();
	i_turn_player = 0;
}

Map::Map(std::string s_name, std::map<int, std::shared_ptr<Tile>> m_i_p_tile_tiles, std::map<std::string, std::shared_ptr<Player>> m_s_p_plyr_players,
		 std::map<int, std::string> m_i_s_turn_order, int i_turn_player, std::string s_shape, int width) : Asset(s_name)
{
	int2_size = Int2(width, static_cast<int>(m_i_p_tile_tiles.size() / width));

	this->s_shape = s_shape;

	this->m_i_p_tile_tiles = std::move(m_i_p_tile_tiles);

	this->m_s_p_plyr_players = std::move(m_s_p_plyr_players);

	this->m_i_s_turn_order = std::move(m_i_s_turn_order);

	this->i_turn_player = i_turn_player;
}

std::string Map::s_get_shape()
{
	return s_shape;
}

Int2 Map::int2_get_size()
{
	return int2_size;
}

std::shared_ptr<Tile> Map::p_tile_get_tile(Int2 int2_coordinates)
{
	return m_i_p_tile_tiles.at(int2_coordinates.x + int2_coordinates.y * int2_size.x);
}

void Map::set_soil_cover(Int2 int2_coordinates, SoilCover scvr_soil_cover, std::shared_ptr<sf::Texture> p_txtr_soil_cover_atlas, int i_tile_size)
{
	m_i_p_tile_tiles.at(int2_coordinates.x + int2_coordinates.y * int2_size.x)->scvr_set_soil_cover(scvr_soil_cover);

	update_soil_cover_texture(p_txtr_soil_cover_atlas, i_tile_size);
}

std::shared_ptr<sf::Texture> Map::p_txtr_get_soil_cover_texture() { return p_txtr_soil_cover_texture; }

std::shared_ptr<sf::Texture> Map::p_txtr_get_units_texture() { return p_txtr_units_texture; }

std::shared_ptr<Player> Map::p_plyr_get_player(std::string s_name) { return m_s_p_plyr_players[s_name]; }

std::map<int, std::string> Map::m_i_s_get_turn_order() { return m_i_s_turn_order; }

int Map::i_get_turn_player() { return i_turn_player; }

void Map::update_soil_cover_texture(std::shared_ptr<sf::Texture> p_txtr_soil_cover_atlas, int i_tile_size)
{
	sf::RenderTexture rtxr_temp_texture;

	sf::Sprite sprt_temp_sprite = sf::Sprite(*p_txtr_soil_cover_atlas);

	Int2 int2_atlas_coords;

	rtxr_temp_texture.create(i_tile_size * int2_size.x, i_tile_size  * int2_size.y);

	for (int i = 0; i < int2_size.x * int2_size.y; i++)
	{
		int2_atlas_coords = m_i_p_tile_tiles[i]->scvr_get_soil_cover().int2_get_atlas_coords();
		sprt_temp_sprite.setTextureRect(sf::Rect(int2_atlas_coords.x * i_tile_size, ((int)p_txtr_soil_cover_atlas->getSize().y) - ((int2_atlas_coords.y + 1) * i_tile_size), i_tile_size, i_tile_size));
		sprt_temp_sprite.setPosition(static_cast<float>((i % int2_size.x) * i_tile_size),
									 static_cast<float>((int2_size.y - ((i / int2_size.x) + 1)) * i_tile_size));
		rtxr_temp_texture.draw(sprt_temp_sprite);
	}

	p_txtr_soil_cover_texture = std::make_shared<sf::Texture>(sf::Texture(rtxr_temp_texture.getTexture()));
}

void Map::update_units_texture(std::shared_ptr<sf::Texture> p_txtr_unit_type_atlas, int i_tile_size)
{
	sf::RenderTexture rtxr_temp_texture;

	sf::Sprite sprt_temp_sprite = sf::Sprite(*p_txtr_unit_type_atlas);

	Int2 int2_atlas_coords;

	rtxr_temp_texture.create(i_tile_size * (int2_size.x * 8), i_tile_size * (int2_size.y * 8));

	int i_unit_iteration;

	for (int i = 0; i < int2_size.x * int2_size.y; i++)
	{
		std::map<std::string, std::shared_ptr<Unit>> m_s_p_unit_war_units = m_i_p_tile_tiles[i]->m_s_p_unit_get_war_units(Globals::glob_get_globals().plyr_get_turn_player());
		std::map<std::string, std::shared_ptr<Unit>> m_s_p_unit_pact_units = m_i_p_tile_tiles[i]->m_s_p_unit_get_pact_units(Globals::glob_get_globals().plyr_get_turn_player());
		std::map<std::string, std::shared_ptr<Unit>> m_s_p_unit_peace_units = m_i_p_tile_tiles[i]->m_s_p_unit_get_peace_units(Globals::glob_get_globals().plyr_get_turn_player());

		if (m_i_p_tile_tiles[i]->p_grsn_get_garrison(Globals::glob_get_globals().plyr_get_turn_player()->s_get_name())->m_s_p_unit_get_units().size() > 0)
		{
			i_unit_iteration = 0;

			for (std::pair<std::string, std::shared_ptr<Unit>> pair_s_unit_pair : m_i_p_tile_tiles[i]->p_grsn_get_garrison(Globals::glob_get_globals().plyr_get_turn_player()->s_get_name())->m_s_p_unit_get_units())
			{
				int2_atlas_coords = pair_s_unit_pair.second->untp_get_unit_type().int2_get_atlas_coords();
				sprt_temp_sprite.setTextureRect(sf::Rect(int2_atlas_coords.x * i_tile_size, ((int)p_txtr_unit_type_atlas->getSize().y) - ((int2_atlas_coords.y + 1) * i_tile_size), i_tile_size, i_tile_size));
				sprt_temp_sprite.setPosition(static_cast<float>((((i % int2_size.x) * 8) + (i_unit_iteration % 4)) * i_tile_size),
					static_cast<float>((((int2_size.y - ((i / int2_size.x) + 1)) * 8) + (3 - (i_unit_iteration / 4))) * i_tile_size));

				std::shared_ptr<sf::Shader> p_shdr_player_color_shader = Globals::glob_get_globals().p_shdr_get_player_color_shader();

				p_shdr_player_color_shader->setUniform("texture", sf::Shader::CurrentTexture);
				p_shdr_player_color_shader->setUniform("primary", sf::Glsl::Vec4(m_s_p_plyr_players[pair_s_unit_pair.second->s_get_player()]->colr_get_primary_color()));
				p_shdr_player_color_shader->setUniform("secondary", sf::Glsl::Vec4(m_s_p_plyr_players[pair_s_unit_pair.second->s_get_player()]->colr_get_secondary_color()));
				p_shdr_player_color_shader->setUniform("invert", m_s_p_plyr_players[pair_s_unit_pair.second->s_get_player()]->b_get_invert_unit_gradient());

				rtxr_temp_texture.draw(sprt_temp_sprite, &*p_shdr_player_color_shader);

				i_unit_iteration++;
				if (i_unit_iteration >= 8) { break; }
			}
		}

		if (m_s_p_unit_war_units.size() > 0)
		{
			i_unit_iteration = 0;

			for (std::pair<std::string, std::shared_ptr<Unit>> pair_s_unit_pair : m_s_p_unit_war_units)
			{
				int2_atlas_coords = pair_s_unit_pair.second->untp_get_unit_type().int2_get_atlas_coords();
				sprt_temp_sprite.setTextureRect(sf::Rect(int2_atlas_coords.x * i_tile_size, ((int)p_txtr_unit_type_atlas->getSize().y) - ((int2_atlas_coords.y + 1) * i_tile_size), i_tile_size, i_tile_size));
				sprt_temp_sprite.setPosition(static_cast<float>((((i % int2_size.x) * 8) + (i_unit_iteration % 4) + 4) * i_tile_size),
					static_cast<float>((((int2_size.y - ((i / int2_size.x) + 1)) * 8) + (3 - (i_unit_iteration / 4)) - 2) * i_tile_size));

				std::shared_ptr<sf::Shader> p_shdr_player_color_shader = Globals::glob_get_globals().p_shdr_get_player_color_shader();

				p_shdr_player_color_shader->setUniform("texture", sf::Shader::CurrentTexture);
				p_shdr_player_color_shader->setUniform("primary", sf::Glsl::Vec4(m_s_p_plyr_players[pair_s_unit_pair.second->s_get_player()]->colr_get_primary_color()));
				p_shdr_player_color_shader->setUniform("secondary", sf::Glsl::Vec4(m_s_p_plyr_players[pair_s_unit_pair.second->s_get_player()]->colr_get_secondary_color()));
				p_shdr_player_color_shader->setUniform("invert", m_s_p_plyr_players[pair_s_unit_pair.second->s_get_player()]->b_get_invert_unit_gradient());

				rtxr_temp_texture.draw(sprt_temp_sprite, &*p_shdr_player_color_shader);

				i_unit_iteration++;
				if (i_unit_iteration >= 8) { break; }
			}
		}

		if (m_s_p_unit_pact_units.size() > 0)
		{
			i_unit_iteration = 0;

			for (std::pair<std::string, std::shared_ptr<Unit>> pair_s_unit_pair : m_s_p_unit_pact_units)
			{
				int2_atlas_coords = pair_s_unit_pair.second->untp_get_unit_type().int2_get_atlas_coords();
				sprt_temp_sprite.setTextureRect(sf::Rect(int2_atlas_coords.x * i_tile_size, ((int)p_txtr_unit_type_atlas->getSize().y) - ((int2_atlas_coords.y + 1) * i_tile_size), i_tile_size, i_tile_size));
				sprt_temp_sprite.setPosition(static_cast<float>((((i % int2_size.x) * 8) + (i_unit_iteration % 4) + 4) * i_tile_size),
					static_cast<float>((((int2_size.y - ((i / int2_size.x) + 1)) * 8) + (3 - (i_unit_iteration / 4))) * i_tile_size));

				std::shared_ptr<sf::Shader> p_shdr_player_color_shader = Globals::glob_get_globals().p_shdr_get_player_color_shader();

				p_shdr_player_color_shader->setUniform("texture", sf::Shader::CurrentTexture);
				p_shdr_player_color_shader->setUniform("primary", sf::Glsl::Vec4(m_s_p_plyr_players[pair_s_unit_pair.second->s_get_player()]->colr_get_primary_color()));
				p_shdr_player_color_shader->setUniform("secondary", sf::Glsl::Vec4(m_s_p_plyr_players[pair_s_unit_pair.second->s_get_player()]->colr_get_secondary_color()));
				p_shdr_player_color_shader->setUniform("invert", m_s_p_plyr_players[pair_s_unit_pair.second->s_get_player()]->b_get_invert_unit_gradient());

				rtxr_temp_texture.draw(sprt_temp_sprite, &*p_shdr_player_color_shader);

				i_unit_iteration++;
				if (i_unit_iteration >= 8) { break; }
			}
		}

		if (m_s_p_unit_peace_units.size() > 0)
		{
			i_unit_iteration = 0;

			for (std::pair<std::string, std::shared_ptr<Unit>> pair_s_unit_pair : m_s_p_unit_peace_units)
			{
				int2_atlas_coords = pair_s_unit_pair.second->untp_get_unit_type().int2_get_atlas_coords();
				sprt_temp_sprite.setTextureRect(sf::Rect(int2_atlas_coords.x * i_tile_size, ((int)p_txtr_unit_type_atlas->getSize().y) - ((int2_atlas_coords.y + 1) * i_tile_size), i_tile_size, i_tile_size));
				sprt_temp_sprite.setPosition(static_cast<float>((((i % int2_size.x) * 8) + (i_unit_iteration % 4)) * i_tile_size),
					static_cast<float>((((int2_size.y - ((i / int2_size.x) + 1)) * 8) + (3 - (i_unit_iteration / 4)) - 2) * i_tile_size));

				std::shared_ptr<sf::Shader> p_shdr_player_color_shader = Globals::glob_get_globals().p_shdr_get_player_color_shader();

				p_shdr_player_color_shader->setUniform("texture", sf::Shader::CurrentTexture);
				p_shdr_player_color_shader->setUniform("primary", sf::Glsl::Vec4(m_s_p_plyr_players[pair_s_unit_pair.second->s_get_player()]->colr_get_primary_color()));
				p_shdr_player_color_shader->setUniform("secondary", sf::Glsl::Vec4(m_s_p_plyr_players[pair_s_unit_pair.second->s_get_player()]->colr_get_secondary_color()));
				p_shdr_player_color_shader->setUniform("invert", m_s_p_plyr_players[pair_s_unit_pair.second->s_get_player()]->b_get_invert_unit_gradient());

				rtxr_temp_texture.draw(sprt_temp_sprite, &*p_shdr_player_color_shader);

				i_unit_iteration++;
				if (i_unit_iteration >= 8) { break; }
			}
		}
	}

	p_txtr_units_texture = std::make_shared<sf::Texture>(sf::Texture(rtxr_temp_texture.getTexture()));
}