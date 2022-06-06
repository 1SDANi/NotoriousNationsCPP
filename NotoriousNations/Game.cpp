#include "Game.hpp"

Game::Game() : window("Notorious Nations")
{
	Globals::glob_get_globals();
	testSprite.setTexture(*Globals::glob_get_globals().asmp_get_asset_maps().map_get_map("Test Map 1").p_txtr_get_soil_cover_texture());
	f_delta_time = clock.restart().asSeconds();
}

void Game::update()
{
	Globals::glob_get_globals().update_controllers();

	window.update();

	Globals::glob_get_globals().cmra_get_camera().update(f_delta_time);
}

void Game::late_update()
{
	Vector3 vec3_position = Globals::glob_get_globals().cmra_get_camera().vec3_get_position();

	testSprite.setPosition(vec3_position.x, vec3_position.y);

	testSprite.setScale(1 + vec3_position.z, 1 + vec3_position.z);
}

void Game::draw()
{
	window.begin_draw();

	window.draw(testSprite);

	window.end_draw();
}

bool Game::b_is_running() const
{
	return window.b_is_open();
}

void Game::update_delta_time()
{
	f_delta_time = clock.restart().asSeconds();
}