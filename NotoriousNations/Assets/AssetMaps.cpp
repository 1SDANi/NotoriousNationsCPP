#include "AssetMaps.hpp"

AssetMaps::AssetMaps()
{

}

AssetMaps::AssetMaps(std::filesystem::path path_roaming_data_path)
{
	this->path_roaming_data_path = path_roaming_data_path;

	p_m_s_slcv_soil_covers = std::make_shared<std::map<std::string, SoilCover>>();

	p_m_s_untp_unit_types = std::make_shared<std::map<std::string, UnitType>>();

	p_txtr_soil_cover_atlas = generate_atlas(FolderCrawler::b_crawl_folder(path_roaming_data_path.string() + "\\JSON\\SoilCovers", { L".json" }),
											 p_m_s_slcv_soil_covers, slcv_generate_soil_cover, slcv_populate_soil_cover, i_tile_size);

	p_txtr_unit_type_atlas = generate_atlas(FolderCrawler::b_crawl_folder(path_roaming_data_path.string() + "\\JSON\\UnitTypes", { L".json" }),
											 p_m_s_untp_unit_types, untp_generate_unit_type, untp_populate_unit_type, i_tile_size);
}

bool AssetMaps::b_has_map(std::string s_name)
{
	return m_s_p_map_maps.contains(s_name);
}

std::shared_ptr<Map> AssetMaps::p_map_get_map(std::string s_name)
{
	if (b_has_map(s_name))
	{
		return m_s_p_map_maps[s_name];
	}

	return std::make_shared<Map>(Map());
}

void AssetMaps::set_soil_cover(std::string s_map, Int2 int2_coordinates, SoilCover scvr_soil_cover)
{
	m_s_p_map_maps[s_map]->set_soil_cover(int2_coordinates, scvr_soil_cover, p_txtr_soil_cover_atlas, i_tile_size);
}

std::shared_ptr<sf::Texture> AssetMaps::p_txtr_get_soil_cover_atlas() { return p_txtr_soil_cover_atlas; }

std::shared_ptr<sf::Texture> AssetMaps::p_txtr_get_unit_type_atlas() { return p_txtr_unit_type_atlas; }

std::map<std::string, SoilCover> AssetMaps::m_s_slcv_get_soil_covers() { return *p_m_s_slcv_soil_covers; }

std::map<std::string, UnitType> AssetMaps::m_s_untp_get_unit_types() { return *p_m_s_untp_unit_types; }

int AssetMaps::i_get_tile_size() { return i_tile_size; }

void AssetMaps::save_map(std::string s_in_name, std::string s_out_name, std::filesystem::path path_path)
{
	nlohmann::json json_json = {};

	std::shared_ptr<Map> p_map_map = m_s_p_map_maps[s_in_name];

	json_json["s_name"] = s_out_name;
	json_json["s_shape"] = p_map_map->s_get_shape();
	json_json["s_type"] = "Map";
	json_json["i_x"] = p_map_map->int2_get_size().x;
	json_json["i_y"] = p_map_map->int2_get_size().y;
	
	for (int x = 0; x < p_map_map->int2_get_size().x; x++)
	{
		for (int y = 0; y < p_map_map->int2_get_size().y; y++)
		{
			std::string s_coords = std::to_string(x) + "," + std::to_string(y);
			
			std::shared_ptr<Tile> p_tile_tile = p_map_map->p_tile_get_tile(Int2(x, y));

			json_json["dict_vec2_tile_tiles"][s_coords]["s_name"] = p_tile_tile->s_get_name();
			json_json["dict_vec2_tile_tiles"][s_coords]["s_type"] = "Tile";
			json_json["dict_vec2_tile_tiles"][s_coords]["s_soil_cover"] = p_tile_tile->scvr_get_soil_cover().s_get_name();
		}
	}

	std::ofstream ofst_file(path_path);
	ofst_file << std::setw(4) << json_json;
	ofst_file.close();
}

void AssetMaps::generate_maps()
{
	std::vector<std::filesystem::path>  v_path_matching_paths = FolderCrawler::b_crawl_folder(path_roaming_data_path.string() + "\\JSON\\Maps", { L".json" });
	if (v_path_matching_paths.size() > 0)
	{
		std::shared_ptr<Map> p_map_iteration;

		nlohmann::json json_json;

		for (std::filesystem::path path_path : v_path_matching_paths)
		{
			std::ifstream ifst_ifstream(path_path.c_str());

			json_json = nlohmann::json::parse(ifst_ifstream);

			p_map_iteration = p_map_populate_map(json_json, path_path);

			m_s_p_map_maps[p_map_iteration->s_get_name()] = p_map_iteration;
		}
	}
}

Unit AssetMaps::unit_populate_unit(nlohmann::json json_json, std::filesystem::path path_path)
{
	Unit unit_return_unit = Unit(json_json.at("s_name"), p_m_s_untp_unit_types->at(json_json.at("s_unit_type")));

	if (json_json.at("s_type") != "Unit")
	{
		std::throw_with_nested(path_path.string() + "is not a Unit");
	}

	if (json_json.contains("a_s_training") && json_json.at("a_s_training").is_array())
	{
		for (const auto& item : json_json.at("a_s_training").items())
		{
			unit_return_unit.add_training(item.value());
		}
	}

	return unit_return_unit;
}

std::shared_ptr<Map> AssetMaps::p_map_populate_map(nlohmann::json json_json, std::filesystem::path path_path)
{
	Int2 int2_size = Int2(-1, -1);

	std::string s_shape = "-1";
	std::string s_map_name = "-1";
	std::string s_coords = "-1";

	std::string s_tile_name = "-1";
	std::string s_soil_cover = "-1";

	std::shared_ptr<Tile> p_tile_tile = std::make_shared<Tile>();

	if (json_json.at("s_type") != "Map")
	{
		std::throw_with_nested(path_path.string() + "is not a Map");
	}

	if (json_json.at("s_name").is_string())
	{
		s_map_name = json_json.at("s_name");
	}

	if (json_json.at("s_shape").is_string())
	{
		s_shape = json_json.at("s_shape");
	}

	if (json_json.at("i_x").is_number() && json_json.at("i_y").is_number())
	{
		int2_size = Int2(json_json.at("i_x"), json_json.at("i_y"));
	}

	std::map<int, std::shared_ptr<Tile>> m_i_p_tile_tiles;

	if (json_json.at("dict_vec2_tile_tiles").is_object())
	{
		for (int i = 0; i < int2_size.x * int2_size.y; i++)
		{
			s_coords = std::to_string(i % int2_size.x) + "," + std::to_string(i / int2_size.x);

			if (json_json.at("dict_vec2_tile_tiles").contains(s_coords))
			{
				if (json_json.at("dict_vec2_tile_tiles").at(s_coords).at("s_type") != "Tile")
				{
					std::throw_with_nested(path_path.string() + "/dict_vec2_tile_tiles/" + s_coords + "/s_type " + "is not a Tile");
				}

				if (json_json.at("dict_vec2_tile_tiles").at(s_coords).at("s_name").is_string())
				{
					s_tile_name = json_json.at("dict_vec2_tile_tiles").at(s_coords).at("s_name");
				}

				if (json_json.at("dict_vec2_tile_tiles").at(s_coords).at("s_soil_cover").is_string())
				{
					s_soil_cover = json_json.at("dict_vec2_tile_tiles").at(s_coords).at("s_soil_cover");

					std::wcout << L"loaded " << s_soil_cover.c_str() << " at " << s_coords.c_str() << L"\n";
				}

				p_tile_tile = std::make_shared<Tile>(s_tile_name, Int2(i % int2_size.x, i / int2_size.x), p_m_s_slcv_soil_covers->at(s_soil_cover));

				if (json_json.at("dict_vec2_tile_tiles").at(s_coords).contains("a_unit_units") && json_json.at("dict_vec2_tile_tiles").at(s_coords).at("a_unit_units").is_object())
				{
					for (const auto& item : json_json.at("dict_vec2_tile_tiles").at(s_coords).at("a_unit_units").items())
					{
						p_tile_tile->p_grsn_get_garrison()->add_unit(std::make_shared<Unit>(unit_populate_unit(item.value(), path_path)));
					}
				}
			}

			m_i_p_tile_tiles[i] = p_tile_tile;
		}
	}
	
	std::shared_ptr<Map> p_map_map = std::make_shared<Map>(Map(s_map_name, m_i_p_tile_tiles, s_shape, int2_size.x));

	p_map_map->update_soil_cover_texture(p_txtr_soil_cover_atlas, i_tile_size);

	p_map_map->update_units_texture(p_txtr_unit_type_atlas, i_tile_size);

	return p_map_map;
}

template <typename T>
void generate_default(std::shared_ptr<std::map<std::string, T>> p_m_s_t_map,
					  std::vector<std::filesystem::path> v_path_matching_paths,
					  T (*populate)(T t_t, nlohmann::json json_json, std::filesystem::path path_path))
{
	nlohmann::json json_json;

	for (std::filesystem::path path_path : v_path_matching_paths)
	{
		std::ifstream ifst_ifstream(path_path.c_str());

		if (path_path.stem().string() == "default")
		{
			json_json = nlohmann::json::parse(ifst_ifstream);

			if (!p_m_s_t_map->contains("default"))
			{
				p_m_s_t_map->emplace("default", populate(T(), json_json, path_path));
			}
		}
	}
}

SoilCover slcv_generate_soil_cover(nlohmann::json json_json, std::filesystem::path path_path, int i, int x, SoilCover scvr_default)
{
	SoilCover slcv_return = SoilCover("default", Int2(i % x, i / x));

	slcv_return = slcv_prepopulate_soil_cover(slcv_return, scvr_default);

	slcv_return = slcv_populate_soil_cover(slcv_return, json_json, path_path);

	return slcv_return;
}

UnitType untp_generate_unit_type(nlohmann::json json_json, std::filesystem::path path_path, int i, int x, UnitType untp_default)
{
	UnitType untp_return = UnitType("default", Int2(i % x, i / x));

	untp_return = untp_prepopulate_unit_type(untp_return, untp_default);

	untp_return = untp_populate_unit_type(untp_return, json_json, path_path);

	return untp_return;
}

template <typename T>
std::shared_ptr<sf::Texture> generate_atlas(std::vector<std::filesystem::path>  v_path_matching_paths,
											std::shared_ptr<std::map<std::string, T>> p_m_s_t_map,
											T(*generate)(nlohmann::json json_json, std::filesystem::path path_path, int i, int x, T t_default),
											T(*populate)(T t_t, nlohmann::json json_json, std::filesystem::path path_path),
											int i_tile_size)
{
	generate_default(p_m_s_t_map, v_path_matching_paths, populate);

	std::map<std::string, int> m_s_i_atlas_dimensions = m_s_i_calculate_atlas_dimensions(static_cast<int>(v_path_matching_paths.size()));

	int x = m_s_i_atlas_dimensions["x"];
	int y = m_s_i_atlas_dimensions["y"];

	sf::Texture txtr_temp_texture;
	sf::RenderTexture rtxr_temp_texture;
	sf::Sprite sprt_temp_sprite;

	rtxr_temp_texture.create(i_tile_size * x, i_tile_size * y);

	T t_iteration;

	int i = 0;

	for (std::filesystem::path path_path : v_path_matching_paths)
	{
		if (path_path.stem().string() == "default")
		{
			continue;
		}

		std::ifstream ifst_ifstream(path_path.c_str());

		t_iteration = generate(nlohmann::json::parse(ifst_ifstream), path_path, i, x, p_m_s_t_map->at("default"));

		std::string s_name = t_iteration.s_get_name();

		if (!p_m_s_t_map->contains(s_name) && txtr_temp_texture.loadFromFile(path_path.string().substr(0, path_path.string().size() - 5) + ".png"))
		{
			p_m_s_t_map->emplace(s_name, t_iteration);

			sprt_temp_sprite.setTexture(txtr_temp_texture);
			sprt_temp_sprite.setPosition(static_cast<float>((i % x) * i_tile_size), static_cast<float>((i / x) * i_tile_size));
			rtxr_temp_texture.draw(sprt_temp_sprite);

			std::wcout << L"loaded " << path_path.wstring().substr(0, path_path.wstring().size() - 5) + L".png at (" << std::to_wstring(i % x) + L"," << std::to_wstring(i / x) << L")\n";
				
			i++;
		}
	}

	return std::make_shared<sf::Texture>(sf::Texture(rtxr_temp_texture.getTexture()));
}

std::map<std::string, int> m_s_i_calculate_atlas_dimensions(int images)
{
	std::map<std::string, int> m_s_i_atlas_dimensions = {};

	double d_sqrt = std::sqrt(images);

	m_s_i_atlas_dimensions["x"] = (int)std::floor(d_sqrt);
	m_s_i_atlas_dimensions["y"] = (int)std::ceil(d_sqrt);

	return m_s_i_atlas_dimensions;
}

SoilCover slcv_prepopulate_soil_cover(SoilCover slcv_soil_cover, SoilCover slcv_default_soil_cover)
{
	SoilCover slcv_return_soil_cover = slcv_soil_cover;

	slcv_return_soil_cover.set_all_flags(slcv_default_soil_cover.m_s_b_get_all_flags());
	slcv_return_soil_cover.set_all_texts(slcv_default_soil_cover.m_s_s_get_all_texts());
	slcv_return_soil_cover.set_all_yields(slcv_default_soil_cover.m_s_i_get_all_yields());

	return slcv_return_soil_cover;
}

UnitType untp_prepopulate_unit_type(UnitType untp_unit_type, UnitType untp_default_unit_type)
{
	UnitType untp_return_unit_type = untp_unit_type;

	untp_return_unit_type.set_all_yields(untp_default_unit_type.m_s_i_get_all_yields());
	untp_return_unit_type.set_all_specific_values(untp_default_unit_type.m_s_i_get_specific_values());
	untp_return_unit_type.set_all_training(untp_default_unit_type.s_get_training());

	return untp_return_unit_type;
}

SoilCover slcv_populate_soil_cover(SoilCover slcv_soil_cover, nlohmann::json json_json, std::filesystem::path path_path)
{
	SoilCover slcv_return_soil_cover = slcv_soil_cover;

	if (json_json.at("s_type") != "SoilCover")
	{
		std::throw_with_nested(path_path.string() + "is not a SoilCover");
	}

	slcv_return_soil_cover.set_name(json_json.at("s_name"));

	for (const auto& item : json_json.items())
	{
		if (item.value().is_number())
		{
			slcv_return_soil_cover.set_yield(item.key(), item.value());
		}

		else if (item.value().is_string() && item.key() != "s_name")
		{
			slcv_return_soil_cover.set_text(item.key(), item.value());
		}

		else if (item.value().is_boolean())
		{
			slcv_return_soil_cover.set_flag(item.key(), item.value());
		}
	}

	return slcv_return_soil_cover;
}

UnitType untp_populate_unit_type(UnitType untp_unit_type, nlohmann::json json_json, std::filesystem::path path_path)
{
	UnitType untp_return_unit_type = untp_unit_type;

	if (json_json.at("s_type") != "UnitType")
	{
		std::throw_with_nested(path_path.string() + "is not a UnitType");
	}

	untp_return_unit_type.set_name(json_json.at("s_name"));
	untp_return_unit_type.set_combat_role(json_json.at("s_combat_role"));
	untp_return_unit_type.set_combat_range(json_json.at("s_combat_range"));

	for (const auto& item : json_json.items())
	{
		if (item.value().is_number())
		{
			untp_return_unit_type.set_yield(item.key(), item.value());
		}

		else if (item.value().is_array())
		{
			for (const auto& item2 : item.value().items())
			{
				untp_return_unit_type.add_training(item2.value());
			}
		}
		else if (item.value().is_object())
		{
			for (const auto& item2 : item.value().items())
			{
				untp_return_unit_type.set_specific_specific_value(item.key(), item2.key(), item2.value());
			}
		}
	}

	return untp_return_unit_type;
}