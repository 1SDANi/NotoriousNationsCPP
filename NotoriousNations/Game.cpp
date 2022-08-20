#include "Game.hpp"

Game::Game()
{
	Globals::glob_get_globals();

	f_delta_time = clck_clock.restart().asSeconds();

	p_txtr_cursor = std::make_shared<sf::Texture>(sf::Texture());

	p_txtr_cursor->loadFromFile(Globals::glob_get_globals().path_get_roaming_data_path().string() + "\\JSON\\Menu\\textures\\Cursor.png");

	sprt_camera_cursor.setTexture(*p_txtr_cursor);

	sprt_menu_cursor.setTexture(*p_txtr_cursor);

	if (!font_font.loadFromFile(Globals::glob_get_globals().path_get_roaming_data_path().string() + "\\font.ttf"))
	{
		std::wcout << L"Failed to load font at " << Globals::glob_get_globals().path_get_roaming_data_path().c_str() << L"\\font.ttf\n";
	}
	else
	{
		text_text = sf::Text();
		text_text.setFont(font_font);
		text_text.setOutlineColor(sf::Color::White);
		text_text.setFillColor(sf::Color::White);
	}
}

void Game::update()
{
	Globals::glob_get_globals().update_controllers();

	Globals::glob_get_globals().set_namebox_text_dom("");

	std::shared_ptr<Menu> p_menu_menu = Globals::glob_get_globals().p_menu_get_menu();

	p_menu_menu->update_submenu(Globals::glob_get_globals().vec2_get_window_size(), "Toolbar");

	Globals::glob_get_globals().update_window();

	sf::FloatRect frct_iconbox_bounds = p_menu_menu->frct_get_iconbox_bounds(Globals::glob_get_globals().vec2_get_window_size(), "Toolbar");

	std::map<int, sf::FloatRect> m_i_frct_icon_bounds = p_menu_menu->m_i_frct_get_icon_bounds(Globals::glob_get_globals().vec2_get_window_size(), "Toolbar");

	if (m_i_frct_icon_bounds.size() > 0 && frct_iconbox_bounds.contains((sf::Vector2f)Globals::glob_get_globals().vc2i_get_mouse_position()))
	{
		for (int i = 0; i < m_i_frct_icon_bounds.size(); i++)
		{
			if (m_i_frct_icon_bounds[i].contains((sf::Vector2f)Globals::glob_get_globals().vc2i_get_mouse_position()))
			{
				if (std::shared_ptr<Tile> p_tile_tile = std::dynamic_pointer_cast<Tile>(Globals::glob_get_globals().p_cmra_get_camera()->get_selected_asset()))
				{
					int i_garrison_index = p_tile_tile->p_grsn_get_garrison()->m_s_unit_get_units().size() > 0 ? 1 : -1;

					if (i == 0)
					{
						Globals::glob_get_globals().set_namebox_text_dom("Terraform");
					}
					else if (i == i_garrison_index)
					{
						Globals::glob_get_globals().set_namebox_text_dom("Garrison");
					}
				}
				else if (std::shared_ptr<SoilCover> p_scvr_soil_cover = std::dynamic_pointer_cast<SoilCover>(Globals::glob_get_globals().p_cmra_get_camera()->get_selected_asset()))
				{
					Globals::glob_get_globals().set_namebox_text_dom("Set " + Globals::glob_get_globals().s_get_namebox_text_sub() + " to " + Globals::glob_get_globals().p_asmp_get_asset_maps()->
						m_s_slcv_get_soil_covers()[p_menu_menu->m_i_s_get_toolbar_sprite_names(Globals::glob_get_globals().vec2_get_window_size(), "Toolbar")[i]].s_get_name());
				}
				else if (std::shared_ptr<Garrison> p_grsn_garrison = std::dynamic_pointer_cast<Garrison>(Globals::glob_get_globals().p_cmra_get_camera()->get_selected_asset()))
				{
					Globals::glob_get_globals().set_namebox_text_dom("Instruct " + p_grsn_garrison->m_s_unit_get_units().at(p_menu_menu->m_i_s_get_toolbar_sprite_names(Globals::glob_get_globals().vec2_get_window_size(), "Toolbar")[i]).s_get_name());
				}
			}
		}
	}

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
		if (std::shared_ptr<Tile> p_tile_tile = std::dynamic_pointer_cast<Tile>(Globals::glob_get_globals().p_cmra_get_camera()->get_selected_asset()))
		{
			Globals::glob_get_globals().p_menu_get_menu()->populate_toolbar_tile(*p_tile_tile);
		}
		else if (std::shared_ptr<SoilCover> p_scvr_soil_cover = std::dynamic_pointer_cast<SoilCover>(Globals::glob_get_globals().p_cmra_get_camera()->get_selected_asset()))
		{
			Globals::glob_get_globals().set_namebox_text_sub(Globals::glob_get_globals().p_map_get_current_map()->p_tile_get_tile(int2_camera_cursor)->s_get_name());

			p_menu_menu->populate_toolbar_soil_covers(Globals::glob_get_globals().p_map_get_current_map()->p_tile_get_tile(int2_camera_cursor)->scvr_get_soil_cover().s_get_name(),
													  Globals::glob_get_globals().p_asmp_get_asset_maps()->m_s_slcv_get_soil_covers(),
													  Globals::glob_get_globals().p_asmp_get_asset_maps()->p_txtr_get_soil_cover_atlas());
		}
		else if (std::shared_ptr<Garrison> p_grsn_garrison = std::dynamic_pointer_cast<Garrison>(Globals::glob_get_globals().p_cmra_get_camera()->get_selected_asset()))
		{
			p_menu_menu->populate_toolbar_units(Globals::glob_get_globals().p_map_get_current_map()->p_tile_get_tile(int2_camera_cursor)->scvr_get_soil_cover().s_get_name(),
												p_grsn_garrison->m_s_unit_get_units(),
												Globals::glob_get_globals().p_asmp_get_asset_maps()->p_txtr_get_unit_type_atlas());
		}
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

	Globals::glob_get_globals().p_cmra_get_camera()->set_soilcovers(Globals::glob_get_globals().p_map_get_current_map()->p_txtr_get_soil_cover_texture());

	Globals::glob_get_globals().p_cmra_get_camera()->set_units(Globals::glob_get_globals().p_map_get_current_map()->p_txtr_get_units_texture());

	Globals::glob_get_globals().p_cmra_get_camera()->late_update(i_tile_size);
}

void Game::draw()
{
	std::shared_ptr<Menu> p_menu_menu = Globals::glob_get_globals().p_menu_get_menu();

	Globals::glob_get_globals().begin_draw();

	Globals::glob_get_globals().draw(Globals::glob_get_globals().p_cmra_get_camera()->sprt_get_soilcovers_sprite());

	Globals::glob_get_globals().draw(Globals::glob_get_globals().p_cmra_get_camera()->sprt_get_units_sprite());

	sf::FloatRect frct_iconbox_bounds = p_menu_menu->frct_get_iconbox_bounds(Globals::glob_get_globals().vec2_get_window_size(), "Toolbar");
	sf::FloatRect frct_namebox_bounds = p_menu_menu->frct_get_namebox_bounds(Globals::glob_get_globals().vec2_get_window_size(), "Toolbar");

	sf::RectangleShape iconbox_fill(sf::Vector2f(frct_iconbox_bounds.width, frct_iconbox_bounds.height));
	iconbox_fill.setFillColor(sf::Color(64, 64, 64, 255));
	iconbox_fill.setPosition(frct_iconbox_bounds.left, frct_iconbox_bounds.top);

	sf::RectangleShape namebox_fill(sf::Vector2f(frct_namebox_bounds.width, frct_namebox_bounds.height));
	namebox_fill.setFillColor(sf::Color(64, 64, 64, 255));
	namebox_fill.setPosition(frct_namebox_bounds.left, frct_namebox_bounds.top);

	Globals::glob_get_globals().draw(iconbox_fill);
	Globals::glob_get_globals().draw(namebox_fill);

	if (Globals::glob_get_globals().p_cmra_get_camera()->int2_get_cursor_position().x >= 0 && Globals::glob_get_globals().p_cmra_get_camera()->int2_get_cursor_position().y >= 0)
	{
		Globals::glob_get_globals().draw(sprt_camera_cursor);

		for (auto const& [i, s] : p_menu_menu->m_i_sprt_get_toolbar_sprites(Globals::glob_get_globals().vec2_get_window_size(), "Toolbar"))
		{
			Globals::glob_get_globals().draw(s);
		}

		if (p_menu_menu->i_get_cursor_position() >= 0)
		{
			Globals::glob_get_globals().draw(sprt_menu_cursor);
		}
		
	}

	for (auto const& [i, s] : p_menu_menu->m_i_sprt_get_submenu_sprites(Globals::glob_get_globals().vec2_get_window_size(), "Toolbar"))
	{
		Globals::glob_get_globals().draw(s);
	}

	if (p_menu_menu->i_get_nametext_height(Globals::glob_get_globals().vec2_get_window_size(), "Toolbar") > 0)
	{
		text_text.setCharacterSize(p_menu_menu->i_get_nametext_height(Globals::glob_get_globals().vec2_get_window_size(), "Toolbar"));
		text_text.setString(Globals::glob_get_globals().s_get_namebox_text());
		text_text.setPosition(p_menu_menu->vc2f_get_nametext_position(Globals::glob_get_globals().vec2_get_window_size(), "Toolbar"));
		Globals::glob_get_globals().draw(text_text);
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