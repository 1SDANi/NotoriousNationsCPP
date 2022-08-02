#include "Game.hpp"

Game::Game() : wndw_window("Notorious Nations")
{
	Globals::glob_get_globals();

	menu = Menu();

	f_delta_time = clck_clock.restart().asSeconds();

	p_txtr_cursor = std::make_shared<sf::Texture>(sf::Texture());

	p_txtr_cursor->loadFromFile(Globals::glob_get_globals().path_get_roaming_data_path().string() + "\\JSON\\Menu\\textures\\Cursor.png");

	sprt_cursor.setTexture(*p_txtr_cursor);
}

void Game::update()
{
	Globals::glob_get_globals().update_controllers();

	menu.update_submenu(wndw_window.vec2_get_size(), "Toolbar");

	wndw_window.update();

	if (Globals::glob_get_globals().b_is_has_focus())
	{
		Globals::glob_get_globals().p_cmra_get_camera()->update(Globals::glob_get_globals().cntr_get_controller(0), wndw_window.vc2i_get_mouse_position(), wndw_window.vec2_get_size(), f_delta_time, Globals::glob_get_globals().p_asmp_get_asset_maps()->i_get_tile_size());
	}
}

void Game::late_update()
{
	int i_tile_size = Globals::glob_get_globals().p_asmp_get_asset_maps()->i_get_tile_size();

	Vector3 vec3_position = Globals::glob_get_globals().p_cmra_get_camera()->vec3_get_position();

	Int2 int2_cursor_position = Globals::glob_get_globals().p_cmra_get_camera()->int2_get_cursor_position();

	sprt_cursor.setScale(1 + vec3_position.z, 1 + vec3_position.z);

	sprt_cursor.setPosition(-(vec3_position.x + (float)(-int2_cursor_position.x) * i_tile_size * sprt_cursor.getScale().x),
							(vec3_position.y + (float)(int2_cursor_position.y) * i_tile_size * sprt_cursor.getScale().y));

	Globals::glob_get_globals().p_cmra_get_camera()->set_soilcovers(Globals::glob_get_globals().p_asmp_get_asset_maps()->map_get_map("Test Map 1").p_txtr_get_soil_cover_texture());

	Globals::glob_get_globals().p_cmra_get_camera()->late_update(i_tile_size);
}

void Game::draw()
{
	wndw_window.begin_draw();

	wndw_window.draw(Globals::glob_get_globals().p_cmra_get_camera()->sprt_get_soilcovers_sprite());

	wndw_window.draw(sprt_cursor);

	for (auto const& [i, s] : menu.get_submenu_sprites(wndw_window.vec2_get_size(), "Toolbar"))
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