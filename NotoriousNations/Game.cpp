#include "Game.hpp"

Game::Game() : wndw_window("Notorious Nations")
{
	Globals::glob_get_globals();

	menu = Menu();

	f_delta_time = clck_clock.restart().asSeconds();
}

void Game::update()
{
	Globals::glob_get_globals().update_controllers();

	menu.update_submenu(wndw_window.get_size(), "Toolbar");

	wndw_window.update();

	Globals::glob_get_globals().p_cmra_get_camera()->update(f_delta_time);
}

void Game::late_update()
{
	Vector3 vec3_position = Globals::glob_get_globals().p_cmra_get_camera()->vec3_get_position();

	sprt_soilcovers.setPosition(-vec3_position.x, vec3_position.y);

	sprt_soilcovers.setScale(1 + vec3_position.z, 1 + vec3_position.z);

	sprt_soilcovers.setTexture(*Globals::glob_get_globals().p_asmp_get_asset_maps()->map_get_map("Test Map 1").p_txtr_get_soil_cover_texture());
}

void Game::draw()
{
	wndw_window.begin_draw();

	wndw_window.draw(sprt_soilcovers);

	for (auto const& [i, s] : menu.get_submenu_sprites(wndw_window.get_size(), "Toolbar"))
	{
		wndw_window.draw(s);
	}

	wndw_window.end_draw();
}

bool Game::b_is_running() const
{
	return wndw_window.b_is_open();
}

void Game::update_delta_time()
{
	f_delta_time = clck_clock.restart().asSeconds();
}