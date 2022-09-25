#include "Player.hpp"

Player::Player() : AtlasYield()
{
	s_adjective = "Unnamed";

	m_s_wrst_war_states = std::map<std::string, WarStates>();
}


Player::Player(std::string s_name, Int2 int2_atlas_coords, std::string s_adjective, sf::Color colr_primary, sf::Color colr_secondary, bool b_invert_unit_gradient) : AtlasYield(s_name, int2_atlas_coords)
{
	this->s_adjective = s_adjective;

	this->colr_primary = colr_primary;
	this->colr_secondary = colr_secondary;
	this->b_invert_unit_gradient = b_invert_unit_gradient;

	m_s_wrst_war_states = std::map<std::string, WarStates>();
}

std::string Player::s_get_adjective()
{
	return s_adjective;
}

sf::Color Player::colr_get_primary_color()
{
	return colr_primary;
}

sf::Color Player::colr_get_secondary_color()
{
	return colr_secondary;
}

bool Player::b_get_invert_unit_gradient()
{
	return b_invert_unit_gradient;
}

Player::WarStates Player::wrst_get_war_state(std::string s_player)
{
	if (m_s_wrst_war_states.contains(s_player))
	{
		return m_s_wrst_war_states[s_player];
	}

	return Player::WarStates::WAR_STATE_PEACE;
}

std::vector<std::string> Player::v_s_get_war_players()
{
	std::vector<std::string> v_s_return = std::vector<std::string>();

	for (std::pair<std::string, WarStates> pair_s_wrst_pair : m_s_wrst_war_states)
	{
		if (pair_s_wrst_pair.second == Player::WarStates::WAR_STATE_WAR)
		{
			v_s_return.push_back(pair_s_wrst_pair.first);
		}
	}

	return v_s_return;
}

std::vector<std::string> Player::v_s_get_pact_players()
{
	std::vector<std::string> v_s_return = std::vector<std::string>();

	for (std::pair<std::string, WarStates> pair_s_wrst_pair : m_s_wrst_war_states)
	{
		if (pair_s_wrst_pair.second == Player::WarStates::WAR_STATE_PEACE)
		{
			v_s_return.push_back(pair_s_wrst_pair.first);
		}
	}

	return v_s_return;
}

void Player::set_war_state(std::string s_player, WarStates wrst_war_state)
{
	m_s_wrst_war_states[s_player] = wrst_war_state;
}