#pragma once
#ifndef AssetMaps_hpp
#define AssetMaps_hpp

#include "Shlobj_core.h"
#include "SoilCover.hpp"
#include "Int2.hpp"
#include "Map.hpp"

#include "../FolderCrawler.hpp"
#include "../json.hpp"

#include <memory>
#include <fstream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <fstream>

class AssetMaps
{
public:
	AssetMaps();
	
	AssetMaps(std::filesystem::path path_roaming_data_path);

	int i_get_tile_size();

	bool b_has_map(std::string s_name);

	std::shared_ptr<Map> p_map_get_map(std::string s_name);

	void set_soil_cover(std::string s_map, Int2 int2_coordinates, SoilCover scvr_soil_cover);

	std::shared_ptr<sf::Texture> p_txtr_get_soil_cover_atlas();

	std::map<std::string, SoilCover> m_sslcv_get_soil_covers();

private:
	int i_tile_size = 32;

	void generate_soil_cover_atlas();

	void save_map(std::string s_in_name, std::string s_out_name, std::filesystem::path path_path);

	void generate_maps();

	std::map<std::string, SoilCover> m_s_slcv_soil_covers;

	std::map<std::string, std::shared_ptr<Map>> m_s_p_map_maps;

	std::shared_ptr<sf::Texture> p_txtr_soil_cover_atlas;

	std::map<std::string, int> m_s_i_calculate_atlas_dimensions(int images);

	SoilCover slcv_populate_soil_cover(SoilCover slcv_soil_cover, nlohmann::json json_json, std::filesystem::path path_path);

	SoilCover slcv_prepopulate_soil_cover(SoilCover slcv_soil_cover, SoilCover slcv_default_soil_cover);

	std::shared_ptr<Map> p_map_populate_map(nlohmann::json json_json, std::filesystem::path path_path);

	std::filesystem::path path_roaming_data_path;
};

#endif