#include "Tile.hpp"

#include "../Globals.hpp"

Tile::Tile()
{
	int2_position = Int2(0, 0);

	std::string s_player = "ERROR_NO_PLAYER";

	m_s_p_grsn_garrison = std::map<std::string, std::shared_ptr<Garrison>>();
}

Tile::Tile(std::string s_name, Int2 int2_position, SoilCover scvr_soil_cover, std::string s_player) : Asset(s_name)
{
	this->int2_position = int2_position;
	this->scvr_soil_cover = scvr_soil_cover;
	this->s_player = s_player;

	m_s_p_grsn_garrison = std::map<std::string, std::shared_ptr<Garrison>>();
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

std::string Tile::s_get_player()
{
	return s_player;
}

void Tile::set_player(std::string s_player)
{
	this->s_player = s_player;
}

std::map<std::string, std::shared_ptr<Garrison>> Tile::p_grsn_get_garrisons()
{
	return m_s_p_grsn_garrison;
}

std::shared_ptr<Garrison> Tile::p_grsn_get_garrison(std::string s_player)
{
	if (!m_s_p_grsn_garrison.contains(s_player))
	{
		m_s_p_grsn_garrison[s_player] = std::make_shared<Garrison>(Garrison((std::string)Globals::glob_get_globals().p_map_get_current_map()->p_plyr_get_player(s_player)->s_get_adjective() + " Garrison"));
	}

	return m_s_p_grsn_garrison[s_player];
}

std::shared_ptr<Garrison> Tile::p_grsn_get_garrison(std::string s_player, std::string s_adjective)
{
	if (!m_s_p_grsn_garrison.contains(s_player))
	{
		m_s_p_grsn_garrison[s_player] = std::make_shared<Garrison>(Garrison(s_adjective + " Garrison"));
	}

	return m_s_p_grsn_garrison[s_player];
}

std::map<std::string, std::shared_ptr<Unit>> Tile::m_s_p_unit_get_war_units(std::shared_ptr<Player> p_plyr_player)
{
	std::map<std::string, std::shared_ptr<Unit>> m_s_p_unit_units = std::map<std::string, std::shared_ptr<Unit>>();

	for (std::string s_war_player : p_plyr_player->v_s_get_war_players())
	{
		if (m_s_p_grsn_garrison.contains(s_war_player))
		{
			for (std::pair<std::string, std::shared_ptr<Unit>> pair_s_p_unit_pair : m_s_p_grsn_garrison[s_war_player]->m_s_p_unit_get_units())
			{
				m_s_p_unit_units[pair_s_p_unit_pair.first] = pair_s_p_unit_pair.second;
			}
		}
	}

	return m_s_p_unit_units;
}

std::map<std::string, std::shared_ptr<Unit>> Tile::m_s_p_unit_get_war_units(std::string s_player)
{
	m_s_p_unit_get_war_units(Globals::glob_get_globals().p_map_get_current_map()->p_plyr_get_player(s_player));
}

std::map<std::string, std::shared_ptr<Unit>> Tile::m_s_p_unit_get_pact_units(std::shared_ptr<Player> p_plyr_player)
{
	std::map<std::string, std::shared_ptr<Unit>> m_s_p_unit_units = std::map<std::string, std::shared_ptr<Unit>>();

	for (std::string s_pact_player : p_plyr_player->v_s_get_pact_players())
	{
		if (m_s_p_grsn_garrison.contains(s_pact_player))
		{
			for (std::pair<std::string, std::shared_ptr<Unit>> pair_s_p_unit_pair : m_s_p_grsn_garrison[s_pact_player]->m_s_p_unit_get_units())
			{
				m_s_p_unit_units[pair_s_p_unit_pair.first] = pair_s_p_unit_pair.second;
			}
		}
	}

	return m_s_p_unit_units;
}

std::map<std::string, std::shared_ptr<Unit>> Tile::m_s_p_unit_get_pact_units(std::string s_player)
{
	m_s_p_unit_get_pact_units(Globals::glob_get_globals().p_map_get_current_map()->p_plyr_get_player(s_player));
}

std::map<std::string, std::shared_ptr<Unit>> Tile::m_s_p_unit_get_peace_units(std::shared_ptr<Player> p_plyr_player)
{
	std::map<std::string, std::shared_ptr<Unit>> m_s_p_unit_units = std::map<std::string, std::shared_ptr<Unit>>();

	for (std::pair<std::string, std::shared_ptr<Garrison>> pair_s_p_grsn_pair : m_s_p_grsn_garrison)
	{
		if (pair_s_p_grsn_pair.first == p_plyr_player->s_get_name()) { continue; }
		if (p_plyr_player->wrst_get_war_state(pair_s_p_grsn_pair.first) == Player::WarStates::WAR_STATE_PEACE)
		{
			for (std::pair<std::string, std::shared_ptr<Unit>> pair_s_p_unit_pair : pair_s_p_grsn_pair.second->m_s_p_unit_get_units())
			{
				m_s_p_unit_units[pair_s_p_unit_pair.first] = pair_s_p_unit_pair.second;
			}
		}
	}

	return m_s_p_unit_units;
}

std::map<std::string, std::shared_ptr<Unit>> Tile::m_s_p_unit_get_peace_units(std::string s_player)
{
	m_s_p_unit_get_peace_units(Globals::glob_get_globals().p_map_get_current_map()->p_plyr_get_player(s_player));
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

bool Tile::b_move_unit(std::shared_ptr<Unit> p_unit_unit, std::shared_ptr<Tile> p_tile_destination)
{
	if (b_can_mobilize(p_unit_unit, p_tile_destination))
	{
		return m_s_p_grsn_garrison[p_unit_unit->s_get_player()]->b_move_unit(p_unit_unit, p_tile_destination->p_grsn_get_garrison(p_unit_unit->s_get_player()));
	}

	return false;
}