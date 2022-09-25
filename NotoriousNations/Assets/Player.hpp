#pragma once
#ifndef Player_hpp
#define Player_hpp

#include "AtlasYield.hpp"

#include <SFML/Graphics.hpp>

class Player : public AtlasYield
{
public:
	enum class WarStates
	{
		WAR_STATE_NONE = -1,
		WAR_STATE_PEACE,
		WAR_STATE_PACT,
		WAR_STATE_WAR,
		CAMERA_OUTPUT_NUM_OUTPUTS
	};

	Player();
	Player(std::string s_name, Int2 int2_atlas_coords, std::string s_adjective, sf::Color colr_primary, sf::Color colr_secondary, bool b_invert_unit_gradient);

	std::string s_get_adjective();

	sf::Color colr_get_primary_color();
	sf::Color colr_get_secondary_color();

	bool b_get_invert_unit_gradient();

	WarStates wrst_get_war_state(std::string s_player);

	std::vector<std::string> v_s_get_war_players();

	std::vector<std::string> v_s_get_pact_players();

	void set_war_state(std::string s_player, WarStates wrst_war_state);

private:
	std::string s_adjective;

	sf::Color colr_primary;
	sf::Color colr_secondary;

	bool b_invert_unit_gradient;

	std::map<std::string, WarStates> m_s_wrst_war_states;
};

#endif