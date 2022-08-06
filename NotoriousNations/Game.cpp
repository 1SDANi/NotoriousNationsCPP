#include "Game.hpp"

Game::Game()
{
	Globals::glob_get_globals();

	f_delta_time = clck_clock.restart().asSeconds();

	p_txtr_cursor = std::make_shared<sf::Texture>(sf::Texture());

	p_txtr_cursor->loadFromFile(Globals::glob_get_globals().path_get_roaming_data_path().string() + "\\JSON\\Menu\\textures\\Cursor.png");

	sprt_camera_cursor.setTexture(*p_txtr_cursor);

	sprt_menu_cursor.setTexture(*p_txtr_cursor);
}

void Game::update()
{
	Globals::glob_get_globals().update_controllers();

	std::shared_ptr<Menu> p_menu_menu = Globals::glob_get_globals().p_menu_get_menu();

	p_menu_menu->update_submenu(Globals::glob_get_globals().vec2_get_window_size(), "Toolbar");

	Globals::glob_get_globals().update_window();

	if (Globals::glob_get_globals().b_is_has_focus())
	{
		Globals::glob_get_globals().p_cmra_get_camera()->update(Globals::glob_get_globals().cntr_get_controller(0),
																Globals::glob_get_globals().vc2i_get_mouse_position(),
																Globals::glob_get_globals().vec2_get_window_size(),
																f_delta_time,
																Globals::glob_get_globals().p_asmp_get_asset_maps()->i_get_tile_size());
	}

	Int2 int2_camera_cursor = Globals::glob_get_globals().p_cmra_get_camera()->int2_get_cursor_position();

	if (Globals::glob_get_globals().p_cmra_get_camera()->b_is_cursor_updated() && int2_camera_cursor.x >= 0 && int2_camera_cursor.y >= 0)
	{

		std::shared_ptr<Tile> p_tile_selected_tile = Globals::glob_get_globals().p_asmp_get_asset_maps()->p_map_get_map("Test Map 1")->p_tile_get_tile(int2_camera_cursor);

		p_menu_menu->populate_toolbar_soil_covers(p_tile_selected_tile->scvr_get_soil_cover().s_get_name());
	}
}

void Game::late_update()
{
	std::shared_ptr<Menu> p_menu_menu = Globals::glob_get_globals().p_menu_get_menu();

	int i_tile_size = Globals::glob_get_globals().p_asmp_get_asset_maps()->i_get_tile_size();

	Vector3 vec3_position = Globals::glob_get_globals().p_cmra_get_camera()->vec3_get_position();

	Int2 int2_camera_cursor_position = Globals::glob_get_globals().p_cmra_get_camera()->int2_get_cursor_position();

	Vector2 vec2_window_size = Globals::glob_get_globals().vec2_get_window_size();

	sf::Vector2f vc2f_menu_cursor_position = p_menu_menu->vc2f_get_icon_screen_coordinates(vec2_window_size, "Toolbar", p_menu_menu->i_get_cursor_position());

	sprt_camera_cursor.setScale(1 + vec3_position.z, 1 + vec3_position.z);
	sprt_menu_cursor.setScale(p_menu_menu->f_get_icon_scale(vec2_window_size, "Toolbar"), p_menu_menu->f_get_icon_scale(vec2_window_size, "Toolbar"));

	sprt_camera_cursor.setPosition(-(vec3_position.x + (float)(-int2_camera_cursor_position.x) * i_tile_size * sprt_camera_cursor.getScale().x),
							(vec3_position.y + (float)(int2_camera_cursor_position.y) * i_tile_size * sprt_camera_cursor.getScale().y));
	sprt_menu_cursor.setPosition(vc2f_menu_cursor_position);

	Globals::glob_get_globals().p_cmra_get_camera()->set_soilcovers(Globals::glob_get_globals().p_asmp_get_asset_maps()->p_map_get_map("Test Map 1")->p_txtr_get_soil_cover_texture());

	Globals::glob_get_globals().p_cmra_get_camera()->late_update(i_tile_size);
}

void Game::draw()
{
	std::shared_ptr<Menu> p_menu_menu = Globals::glob_get_globals().p_menu_get_menu();

	Globals::glob_get_globals().begin_draw();

	Globals::glob_get_globals().draw(Globals::glob_get_globals().p_cmra_get_camera()->sprt_get_soilcovers_sprite());

	if (Globals::glob_get_globals().p_cmra_get_camera()->int2_get_cursor_position().x >= 0 && Globals::glob_get_globals().p_cmra_get_camera()->int2_get_cursor_position().y >= 0)
	{
		Globals::glob_get_globals().draw(sprt_camera_cursor);

		for (auto const& [i, s] : p_menu_menu->m_i_sprt_get_toolbar_sprites(Globals::glob_get_globals().vec2_get_window_size(), "Toolbar"))
		{
			Globals::glob_get_globals().draw(s);
		}

		Globals::glob_get_globals().draw(sprt_menu_cursor);
	}

	for (auto const& [i, s] : p_menu_menu->m_i_sprt_get_submenu_sprites(Globals::glob_get_globals().vec2_get_window_size(), "Toolbar"))
	{
		Globals::glob_get_globals().draw(s);
	}

	Globals::glob_get_globals().end_draw();
}

bool Game::b_is_running() const
{
	return Globals::glob_get_globals().b_is_open();
}

void Game::update_delta_time()
{
	f_delta_time = clck_clock.restart().asSeconds();
}