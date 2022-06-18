#include "Game.hpp"

Game::Game() : wndw_window("Notorious Nations")
{
	Globals::glob_get_globals();

	sprt_soilcovers.setTexture(*Globals::glob_get_globals().p_asmp_get_asset_maps()->map_get_map("Test Map 1").p_txtr_get_soil_cover_texture());
	sprt_edges[0].setTexture(*Globals::glob_get_globals().p_asmp_get_asset_maps()->p_txtr_get_edge());
	sprt_edges[1].setTexture(*Globals::glob_get_globals().p_asmp_get_asset_maps()->p_txtr_get_edge());
	sprt_corners[0].setTexture(*Globals::glob_get_globals().p_asmp_get_asset_maps()->p_txtr_get_corner());
	sprt_corners[1].setTexture(*Globals::glob_get_globals().p_asmp_get_asset_maps()->p_txtr_get_corner());
	sprt_corners[2].setTexture(*Globals::glob_get_globals().p_asmp_get_asset_maps()->p_txtr_get_corner());
	sprt_corners[3].setTexture(*Globals::glob_get_globals().p_asmp_get_asset_maps()->p_txtr_get_corner());
	sprt_cursors.setTexture(*Globals::glob_get_globals().p_asmp_get_asset_maps()->p_txtr_get_cursor());

	f_delta_time = clck_clock.restart().asSeconds();
}

void Game::update()
{
	Globals::glob_get_globals().update_controllers();

	wndw_window.update();

	Globals::glob_get_globals().p_cmra_get_camera()->update(f_delta_time);
}

void Game::late_update()
{
	Vector3 vec3_position = Globals::glob_get_globals().p_cmra_get_camera()->vec3_get_position();

	sprt_soilcovers.setPosition(-vec3_position.x, vec3_position.y);

	sprt_soilcovers.setScale(1 + vec3_position.z, 1 + vec3_position.z);

	sf::Vector2f vec2_12_and_half_percent = sf::Vector2f(wndw_window.get_size().x / 8.0f, wndw_window.get_size().y / 8.0f);

	sf::Vector2f vec2_scale = sf::Vector2f((((vec2_12_and_half_percent.y) - f_buffer_size * 2.0f) / sprt_corners[0].getTexture()->getSize().y) / 2.0f,
		(((vec2_12_and_half_percent.y) - f_buffer_size * 2.0f) / sprt_corners[0].getTexture()->getSize().y) / 2.0f);

	float f_x_size = vec2_scale.y * sprt_corners[0].getTexture()->getSize().x;
	float f_y_size = vec2_scale.y * sprt_corners[0].getTexture()->getSize().y;
	float f_menu_top = wndw_window.get_size().y - f_y_size * 2.0f - f_buffer_size;
	float f_menu_bottom = wndw_window.get_size().y - f_buffer_size;
	float f_right = wndw_window.get_size().x - f_buffer_size;
	float f_top_edge_start = f_buffer_size + f_y_size;
	float f_bottom_edge_start = wndw_window.get_size().x - f_buffer_size - f_y_size;
	float f_edge_length = (wndw_window.get_size().x - f_buffer_size * 2.0f - vec2_scale.x * sprt_corners[0].getTexture()->getSize().x * 2.0f) /
		sprt_corners[0].getTexture()->getSize().x;

	sprt_corners[0].setPosition(f_buffer_size, f_menu_top);
	sprt_corners[1].setPosition(f_right, f_menu_top);
	sprt_corners[2].setPosition(f_right, f_menu_bottom);
	sprt_corners[3].setPosition(f_buffer_size, f_menu_bottom);

	sprt_edges[0].setPosition(f_top_edge_start, f_menu_top);
	sprt_edges[1].setPosition(f_bottom_edge_start, f_menu_bottom);

	sprt_corners[0].setRotation(0.0f);
	sprt_corners[1].setRotation(90.0f);
	sprt_corners[2].setRotation(180.0f);
	sprt_corners[3].setRotation(270.0f);

	sprt_edges[0].setRotation(0.0f);
	sprt_edges[1].setRotation(180.0f);

	sprt_corners[0].setScale(vec2_scale.x, vec2_scale.y);
	sprt_corners[1].setScale(vec2_scale.x, vec2_scale.y);
	sprt_corners[2].setScale(vec2_scale.x, vec2_scale.y);
	sprt_corners[3].setScale(vec2_scale.x, vec2_scale.y);

	sprt_edges[0].setScale(f_edge_length, vec2_scale.y);
	sprt_edges[1].setScale(f_edge_length, vec2_scale.y);
}

void Game::draw()
{
	wndw_window.begin_draw();

	wndw_window.draw(sprt_soilcovers);

	wndw_window.draw(sprt_corners[0]);
	wndw_window.draw(sprt_corners[1]);
	wndw_window.draw(sprt_corners[2]);
	wndw_window.draw(sprt_corners[3]);

	wndw_window.draw(sprt_edges[0]);
	wndw_window.draw(sprt_edges[1]);

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