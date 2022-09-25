#include "Game.hpp"

Game::Game()
{
	Globals::glob_get_globals();

	Globals::glob_get_globals().p_asmp_get_asset_maps()->generate_maps();

	Globals::glob_get_globals().p_map_get_current_map()->update_units_texture(Globals::glob_get_globals().p_asmp_get_asset_maps()->p_txtr_get_unit_type_atlas(),
																			  Globals::glob_get_globals().p_asmp_get_asset_maps()->i_get_tile_size());

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

	sf::Sprite sprt_soilcovers = Globals::glob_get_globals().p_cmra_get_camera()->sprt_get_soilcovers_sprite();

	sf::Vector2i vc2i_mouse_position = Globals::glob_get_globals().vc2i_get_mouse_position();

	if (m_i_frct_icon_bounds.size() > 0 && frct_iconbox_bounds.contains((sf::Vector2f)Globals::glob_get_globals().vc2i_get_mouse_position()))
	{
		for (int i = 0; i < m_i_frct_icon_bounds.size(); i++)
		{
			if (m_i_frct_icon_bounds[i].contains((sf::Vector2f)Globals::glob_get_globals().vc2i_get_mouse_position()))
			{
				if (std::shared_ptr<Tile> p_tile_tile = std::dynamic_pointer_cast<Tile>(Globals::glob_get_globals().p_cmra_get_camera()->get_selected_asset()))
				{
					std::map<int, std::string> m_i_s_garrison_indices = std::map<int, std::string>();

					int i_index = 1;

					if (p_tile_tile->p_grsn_get_garrison(Globals::glob_get_globals().plyr_get_turn_player()->s_get_name())->m_s_p_unit_get_units().size() > 0)
					{
						m_i_s_garrison_indices[i_index++] = Globals::glob_get_globals().plyr_get_turn_player()->s_get_name();
					}

					for (int j = 0; j < Globals::glob_get_globals().p_map_get_current_map()->m_i_s_get_turn_order().size(); j++)
					{
						std::string s_player = Globals::glob_get_globals().p_map_get_current_map()->m_i_s_get_turn_order()[j];
						if (Globals::glob_get_globals().plyr_get_turn_player()->s_get_name() == s_player) { continue; }
						if (p_tile_tile->p_grsn_get_garrison(s_player)->m_s_p_unit_get_units().size() > 0)
						{
							m_i_s_garrison_indices[i_index++] = s_player;
						}
					}

					if (i == 0)
					{
						Globals::glob_get_globals().set_namebox_text_dom("Terraform");
					}
					else if (m_i_s_garrison_indices.contains(i))
					{
						Globals::glob_get_globals().set_namebox_text_dom(Globals::glob_get_globals().p_map_get_current_map()->p_plyr_get_player(m_i_s_garrison_indices[i])->s_get_adjective() + " Garrison");
					}
				}
				else if (std::shared_ptr<SoilCover> p_scvr_soil_cover = std::dynamic_pointer_cast<SoilCover>(Globals::glob_get_globals().p_cmra_get_camera()->get_selected_asset()))
				{
					Globals::glob_get_globals().set_namebox_text_dom("Set " + Globals::glob_get_globals().s_get_namebox_text_sub() + " to " + Globals::glob_get_globals().p_asmp_get_asset_maps()->
						m_s_slcv_get_soil_covers()[p_menu_menu->m_i_s_get_toolbar_sprite_names(Globals::glob_get_globals().vec2_get_window_size(), "Toolbar")[i]].s_get_name());
				}
				else if (std::shared_ptr<Garrison> p_grsn_garrison = std::dynamic_pointer_cast<Garrison>(Globals::glob_get_globals().p_cmra_get_camera()->get_selected_asset()))
				{
					Globals::glob_get_globals().set_namebox_text_dom("Instruct " + p_grsn_garrison->m_s_p_unit_get_units().at(p_menu_menu->m_i_s_get_toolbar_sprite_names(Globals::glob_get_globals().vec2_get_window_size(), "Toolbar")[i])->s_get_name());
				}
				else if (std::shared_ptr<Unit> p_unit_unit = std::dynamic_pointer_cast<Unit>(Globals::glob_get_globals().p_cmra_get_camera()->get_selected_asset()))
				{
					int i_mobilize_index = p_unit_unit->i_get_mobility() > 0 ? 1 : -1;

					if (i == 0)
					{
						Globals::glob_get_globals().set_namebox_text_dom("Discharge " + p_unit_unit->s_get_name());
					}
					else if (i == i_mobilize_index)
					{
						std::string s_mobility_string = p_unit_unit->i_get_mobility() > 1 ? " moves " : " move ";

						Globals::glob_get_globals().set_namebox_text_dom("Mobilize " + p_unit_unit->s_get_name() + " (" + std::to_string(p_unit_unit->i_get_mobility()) + s_mobility_string + "left)");
					}
				}
				else if (std::shared_ptr<MenuMode> p_mnmd_menu_mode = std::dynamic_pointer_cast<MenuMode>(Globals::glob_get_globals().p_cmra_get_camera()->get_selected_asset()))
				{
					if (std::shared_ptr<Unit> p_unit_unit = std::dynamic_pointer_cast<Unit>(p_mnmd_menu_mode->p_asst_get_operator()))
					{
						if (p_mnmd_menu_mode->mnmd_get_mode() == MenuMode::MenuModes::MENU_MODE_MOBILIZE)
						{
							if (i == 0)
							{
								Globals::glob_get_globals().set_namebox_text_dom("Discharge " + p_unit_unit->s_get_name());
							}
						}
					}
				}
			}
		}
	}
	else if (Globals::glob_get_globals().p_cmra_get_camera()->sprt_get_soilcovers_sprite().getGlobalBounds().contains((sf::Vector2f)vc2i_mouse_position))
	{
		// don't handle hovering outside of the window
		if (vc2i_mouse_position.x < 0 ||
			vc2i_mouse_position.x > Globals::glob_get_globals().vec2_get_window_size().x ||
			vc2i_mouse_position.y < 0 ||
			vc2i_mouse_position.y > Globals::glob_get_globals().vec2_get_window_size().x)
		{
			return;
		}

		Vector2 relative_mouse_position = Vector2((vc2i_mouse_position.x - sprt_soilcovers.getGlobalBounds().left) / sprt_soilcovers.getScale().x,
			((vc2i_mouse_position.y - sprt_soilcovers.getGlobalBounds().top) / sprt_soilcovers.getScale().y));

		Vector2 vec2_soilcover_dimensions = Vector2(sprt_soilcovers.getTexture()->getSize().x / (float)Globals::glob_get_globals().p_asmp_get_asset_maps()->i_get_tile_size(),
			sprt_soilcovers.getTexture()->getSize().y / (float)Globals::glob_get_globals().p_asmp_get_asset_maps()->i_get_tile_size());

		Int2 int2_selected_position = Globals::glob_get_globals().p_cmra_get_camera()->int2_get_cursor_position();

		Int2 int2_hover_position = Int2((int)(relative_mouse_position.x / (float)Globals::glob_get_globals().p_asmp_get_asset_maps()->i_get_tile_size()),
			(int)(relative_mouse_position.y / (float)Globals::glob_get_globals().p_asmp_get_asset_maps()->i_get_tile_size()));

		std::shared_ptr<Tile> p_tile_selected_tile = nullptr;

		if (int2_selected_position.x > -1 && int2_selected_position.y > -1)
		{
			p_tile_selected_tile = Globals::glob_get_globals().p_map_get_current_map()->p_tile_get_tile(int2_selected_position);
		}

		std::shared_ptr<Tile> p_tile_hover_tile = Globals::glob_get_globals().p_map_get_current_map()->p_tile_get_tile(int2_hover_position);

		if (std::shared_ptr<MenuMode> p_mnmd_menu_mode = std::dynamic_pointer_cast<MenuMode>(Globals::glob_get_globals().p_cmra_get_camera()->get_selected_asset()))
		{
			if (std::shared_ptr<Unit> p_unit_unit = std::dynamic_pointer_cast<Unit>(p_mnmd_menu_mode->p_asst_get_operator()))
			{
				if (p_mnmd_menu_mode->mnmd_get_mode() == MenuMode::MenuModes::MENU_MODE_MOBILIZE && p_tile_selected_tile != nullptr && p_tile_selected_tile->b_can_mobilize(p_unit_unit, p_tile_hover_tile))
				{
					std::string s_mobility_string = p_unit_unit->i_get_mobility() > 1 ? " moves " : " move ";

					Globals::glob_get_globals().set_namebox_text_dom("Mobilize " + p_unit_unit->s_get_name() + " to " + p_tile_hover_tile->s_get_name() + " (" + std::to_string(p_unit_unit->i_get_mobility()) + s_mobility_string + "left)");
				}
			}
		}
		else
		{
			Globals::glob_get_globals().set_namebox_text_dom(Globals::glob_get_globals().p_map_get_current_map()->p_tile_get_tile(int2_hover_position)->s_get_name());
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
		if (std::shared_ptr<MenuMode> p_mnmd_menu_mode = std::dynamic_pointer_cast<MenuMode>(Globals::glob_get_globals().p_cmra_get_camera()->get_selected_asset()))
		{
			if (std::shared_ptr<Unit> p_unit_unit = std::dynamic_pointer_cast<Unit>(p_mnmd_menu_mode->p_asst_get_operator()))
			{
				if (p_mnmd_menu_mode->mnmd_get_mode() == MenuMode::MenuModes::MENU_MODE_MOBILIZE)
				{
					std::string s_mobility_string = p_unit_unit->i_get_mobility() > 1 ? " moves " : " move ";

					Globals::glob_get_globals().set_namebox_text_sub("Mobilize " + p_unit_unit->s_get_name() + " (" + std::to_string(p_unit_unit->i_get_mobility()) + s_mobility_string + "left)");

					p_menu_menu->populate_toolbar_unit_actions(p_unit_unit, 1);
				}
			}
		}
		else
		{
			Globals::glob_get_globals().set_namebox_text_sub(Globals::glob_get_globals().p_map_get_current_map()->p_tile_get_tile(int2_camera_cursor)->s_get_name());
		}

		if (std::shared_ptr<Tile> p_tile_tile = std::dynamic_pointer_cast<Tile>(Globals::glob_get_globals().p_cmra_get_camera()->get_selected_asset()))
		{
			Globals::glob_get_globals().p_menu_get_menu()->populate_toolbar_tile(*p_tile_tile);
		}
		else if (std::shared_ptr<SoilCover> p_scvr_soil_cover = std::dynamic_pointer_cast<SoilCover>(Globals::glob_get_globals().p_cmra_get_camera()->get_selected_asset()))
		{
			p_menu_menu->populate_toolbar_soil_covers(Globals::glob_get_globals().p_map_get_current_map()->p_tile_get_tile(int2_camera_cursor)->scvr_get_soil_cover().s_get_name(),
													  Globals::glob_get_globals().p_asmp_get_asset_maps()->m_s_slcv_get_soil_covers(),
													  Globals::glob_get_globals().p_asmp_get_asset_maps()->p_txtr_get_soil_cover_atlas());
		}
		else if (std::shared_ptr<Garrison> p_grsn_garrison = std::dynamic_pointer_cast<Garrison>(Globals::glob_get_globals().p_cmra_get_camera()->get_selected_asset()))
		{
			p_menu_menu->populate_toolbar_units(p_grsn_garrison->m_s_p_unit_get_units(),
												Globals::glob_get_globals().p_asmp_get_asset_maps()->p_txtr_get_unit_type_atlas());
		}
		else if (std::shared_ptr<Unit> p_unit_unit = std::dynamic_pointer_cast<Unit>(Globals::glob_get_globals().p_cmra_get_camera()->get_selected_asset()))
		{
			p_menu_menu->populate_toolbar_unit_actions(p_unit_unit, 0);
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

	if (Globals::glob_get_globals().p_cmra_get_camera()->int2_get_cursor_position().x >= 0 && Globals::glob_get_globals().p_cmra_get_camera()->int2_get_cursor_position().y >= 0)
	{
		Globals::glob_get_globals().draw(sprt_camera_cursor);
	}

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
		for (auto const& [i, s] : p_menu_menu->m_i_gtsp_get_toolbar_sprites(Globals::glob_get_globals().vec2_get_window_size(), "Toolbar"))
		{
			std::shared_ptr<sf::Shader> p_shdr_player_color_shader = Globals::glob_get_globals().p_shdr_get_player_color_shader();

			if (s.colr_primary_color == sf::Color::Transparent && s.colr_secondary_color == sf::Color::Transparent)
			{
				Globals::glob_get_globals().draw(s.sprt_sprite);
			}
			else
			{
				p_shdr_player_color_shader->setUniform("texture", sf::Shader::CurrentTexture);
				p_shdr_player_color_shader->setUniform("primary", sf::Glsl::Vec4(s.colr_primary_color));
				p_shdr_player_color_shader->setUniform("secondary", sf::Glsl::Vec4(s.colr_secondary_color));
				p_shdr_player_color_shader->setUniform("invert", s.b_invert_gradient);

				Globals::glob_get_globals().draw(s, p_shdr_player_color_shader);
			}
		}

		if (p_menu_menu->i_get_cursor_position() >= 0)
		{
			Globals::glob_get_globals().draw(sprt_menu_cursor);
		}
	}

	for (auto const& [i, s] : p_menu_menu->m_i_gtsp_get_submenu_sprites(Globals::glob_get_globals().vec2_get_window_size(), "Toolbar"))
	{
		std::shared_ptr<sf::Shader> p_shdr_player_color_shader = Globals::glob_get_globals().p_shdr_get_player_color_shader();

		p_shdr_player_color_shader->setUniform("texture", sf::Shader::CurrentTexture);
		p_shdr_player_color_shader->setUniform("primary", sf::Glsl::Vec4(s.colr_primary_color));
		p_shdr_player_color_shader->setUniform("secondary", sf::Glsl::Vec4(s.colr_secondary_color));
		p_shdr_player_color_shader->setUniform("invert", s.b_invert_gradient);

		Globals::glob_get_globals().draw(s, p_shdr_player_color_shader);
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