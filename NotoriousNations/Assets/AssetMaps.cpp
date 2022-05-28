#include "AssetMaps.hpp"

AssetMaps::AssetMaps()
{
	this->path_roaming_data_path = generate_roaming_data_path();

	generate_soil_cover_atlas();

	generate_maps();
}

std::shared_ptr<sf::Texture> AssetMaps::p_txtr_get_soil_cover_atlas() { return p_txtr_soil_cover_atlas; }

void AssetMaps::generate_maps()
{
	std::vector<std::filesystem::path>  v_path_matching_paths = FolderCrawler::b_crawl_folder(path_get_roaming_data_path().string() + "\\JSON\\Maps", { L".json" });
	if (v_path_matching_paths.size() > 0)
	{
		Map map_iteration;

		nlohmann::json json_json;

		for (std::filesystem::path path_path : v_path_matching_paths)
		{
			std::ifstream ifst_ifstream(path_path.c_str());

			json_json = nlohmann::json::parse(ifst_ifstream);

			map_iteration = map_populate_map(json_json, path_path);

			m_s_p_map_maps[map_iteration.s_get_name()] = map_iteration;
		}
	}
}

Map AssetMaps::map_populate_map(nlohmann::json json_json, std::filesystem::path path_path)
{
	Map map_map;

	Int2 int2_size = Int2(-1, -1);

	std::string s_shape = "-1";
	std::string s_map_name = "-1";
	std::string s_coords = "-1";

	std::string s_tile_name = "-1";
	std::string s_soil_cover = "-1";

	Tile tile_tile = Tile();

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

	std::vector<Tile> v_tile_tiles(int2_size.x * int2_size.y);

	if (json_json.at("dict_tiles").is_object())
	{
		for (int i = 0; i < int2_size.x * int2_size.y; i++)
		{
			s_coords = std::to_string(i % int2_size.x) + "," + std::to_string(i / int2_size.x);

			if (json_json.at("dict_tiles").contains(s_coords))
			{
				if (json_json.at("dict_tiles").at(s_coords).at("s_type") != "Tile")
				{
					std::throw_with_nested(path_path.string() + "/dict_tiles/" + s_coords + "/s_type " + "is not a Tile");
				}

				if (json_json.at("dict_tiles").at(s_coords).at("s_name").is_string())
				{
					s_tile_name = json_json.at("dict_tiles").at(s_coords).at("s_name");
				}

				if (json_json.at("dict_tiles").at(s_coords).at("s_soil_cover").is_string())
				{
					s_soil_cover = json_json.at("dict_tiles").at(s_coords).at("s_soil_cover");

					std::wcout << L"loaded " << s_soil_cover.c_str() << " at " << s_coords.c_str() << L"\n";
				}

				tile_tile = Tile(s_tile_name, Int2(i / int2_size.x), m_s_slcv_soil_covers[s_soil_cover]);
			}

			v_tile_tiles[i] = tile_tile;
		}
	}

	return map_map;
}

void AssetMaps::generate_soil_cover_atlas()
{
	std::vector<std::filesystem::path>  v_path_matching_paths = FolderCrawler::b_crawl_folder(path_get_roaming_data_path().string() + "\\JSON\\SoilCovers", {L".json"});
	if (v_path_matching_paths.size() > 0)
	{
		std::map<std::string, int> m_s_i_atlas_dimensions = m_s_i_calculate_atlas_dimensions(static_cast<int>(v_path_matching_paths.size()));

		int x = m_s_i_atlas_dimensions["x"];
		int y = m_s_i_atlas_dimensions["y"];

		sf::Texture txtr_temp_texture;
		sf::RenderTexture rtxr_temp_texture;
		sf::Sprite sprt_temp_sprite;

		rtxr_temp_texture.create(tile_size * x, tile_size * y);

		m_s_slcv_soil_covers = std::map<std::string, SoilCover>();

		SoilCover slcv_iteration;

		nlohmann::json json_json;

		for (std::filesystem::path path_path : v_path_matching_paths)
		{
			std::ifstream ifst_ifstream(path_path.c_str());

			if (path_path.stem().string() == "default")
			{
				json_json = nlohmann::json::parse(ifst_ifstream);

				slcv_iteration = slcv_populate_soil_cover(SoilCover(), json_json, path_path);

				if (!m_s_slcv_soil_covers.contains("default"))
				{
					m_s_slcv_soil_covers.emplace("default", slcv_iteration);
				}
			}
		}

		int i = 0;

		for (std::filesystem::path path_path : v_path_matching_paths)
		{
			if (path_path.stem().string() == "default")
			{
				continue;
			}

			std::ifstream ifst_ifstream(path_path.c_str());

			json_json = nlohmann::json::parse(ifst_ifstream);

			slcv_iteration = SoilCover(Int2(i % x, i / x));

			slcv_iteration = slcv_prepopulate_soil_cover(slcv_iteration, m_s_slcv_soil_covers["default"]);

			slcv_iteration = slcv_populate_soil_cover(SoilCover(), json_json, path_path);

			std::string s_name = slcv_iteration.s_get_text("s_name");

			if (!m_s_slcv_soil_covers.contains(s_name) && txtr_temp_texture.loadFromFile(path_path.string().substr(0, path_path.string().size() - 5) + ".png"))
			{
				m_s_slcv_soil_covers.emplace(s_name, slcv_iteration);

				sprt_temp_sprite.setTexture(txtr_temp_texture);
				sprt_temp_sprite.setPosition(static_cast<float>(i % x * tile_size), static_cast<float>(i / x * tile_size));
				rtxr_temp_texture.draw(sprt_temp_sprite);

				std::wcout << L"loaded " << path_path.wstring().substr(0, path_path.wstring().size() - 5) + L".png at (" << std::to_wstring(i / x) + L"," << std::to_wstring(i % x) << L")\n";
				
				i++;
			}
		}

		p_txtr_soil_cover_atlas = std::make_shared<sf::Texture>(sf::Texture(rtxr_temp_texture.getTexture()));
	}
	else
	{
		std::throw_with_nested(std::runtime_error(path_get_roaming_data_path().string() + "\\JSON\\SoilCovers contains no .json files"));
	}
}

std::map<std::string, int> AssetMaps::m_s_i_calculate_atlas_dimensions(int images)
{
	std::map<std::string, int> m_s_i_atlas_dimensions = {};

	double d_sqrt = std::sqrt(images);

	m_s_i_atlas_dimensions["x"] = (int)std::floor(d_sqrt);
	m_s_i_atlas_dimensions["y"] = (int)std::ceil(d_sqrt);

	return m_s_i_atlas_dimensions;
}

std::filesystem::path AssetMaps::path_get_roaming_data_path()
{
	return path_roaming_data_path;
}

SoilCover AssetMaps::slcv_prepopulate_soil_cover(SoilCover slcv_soil_cover, SoilCover slcv_default_soil_cover)
{
	SoilCover slcv_return_soil_cover = slcv_soil_cover;

	slcv_return_soil_cover.b_set_all_flags(slcv_default_soil_cover.m_s_b_get_all_flags());
	slcv_return_soil_cover.b_set_all_texts(slcv_default_soil_cover.m_s_s_get_all_texts());
	slcv_return_soil_cover.b_set_all_yields(slcv_default_soil_cover.m_s_i_get_all_yields());

	return slcv_return_soil_cover;
}

SoilCover AssetMaps::slcv_populate_soil_cover(SoilCover slcv_soil_cover, nlohmann::json json_json, std::filesystem::path path_path)
{
	SoilCover slcv_return_soil_cover = slcv_soil_cover;

	if (json_json.at("s_type") != "SoilCover")
	{
		std::throw_with_nested(path_path.string() + "is not a SoilCover");
	}

	for (const auto& item : json_json.items())
	{
		if (item.value().is_number())
		{
			slcv_return_soil_cover.b_set_yield(item.key(), item.value());
		}

		else if (item.value().is_string())
		{
			slcv_return_soil_cover.b_set_text(item.key(), item.value());
		}

		else if (item.value().is_boolean())
		{
			slcv_return_soil_cover.b_set_flag(item.key(), item.value());
		}
	}

	return slcv_return_soil_cover;
}

// static function
// sets "path" to a pointer to a unicode string containing the path to the current user's Appdata/Roaming/NotoriousNations folder
// returns true if "path" is successfully set
std::filesystem::path AssetMaps::generate_roaming_data_path()
{
	std::filesystem::path path_path;
	PWSTR pwst_path;

	if (SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &pwst_path) != S_OK)
	{
		std::throw_with_nested(std::runtime_error("cannot find ...Appdata\\Roaming, got " + (*((wchar_t*)pwst_path))));
	}

	path_path = std::filesystem::path(pwst_path);

	path_path += "\\NotoriousNations";

	if (path_path.empty())
	{
		if (std::filesystem::create_directories(path_path))
		{
			std::wcout << L"folder " << path_path.generic_wstring() << L" created" << "\n";
		}
		else
		{
			std::throw_with_nested(std::runtime_error("failed to create ...Appdata\\Roaming\\NotoriousNations"));
		}
	}
	else
	{
		std::wcout << L"folder " << path_path.generic_wstring() << L" found" << "\n";
	}

	return path_path;
}