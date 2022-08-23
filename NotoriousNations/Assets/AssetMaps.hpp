#pragma once
#ifndef AssetMaps_hpp
#define AssetMaps_hpp

#include "Shlobj_core.h"
#include "SoilCover.hpp"
#include "UnitType.hpp"
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
#include <any>


SoilCover slcv_prepopulate_soil_cover(SoilCover slcv_soil_cover, SoilCover slcv_default_soil_cover);

UnitType untp_prepopulate_unit_type(UnitType untp_unit_type, UnitType untp_default_unit_type);

SoilCover slcv_populate_soil_cover(SoilCover slcv_soil_cover, nlohmann::json json_json, std::filesystem::path path_path);

UnitType untp_populate_unit_type(UnitType untp_unit_type, nlohmann::json json_json, std::filesystem::path path_path);

SoilCover slcv_generate_soil_cover(nlohmann::json json_json, std::filesystem::path path_path, int i, int x, SoilCover scvr_default);

UnitType untp_generate_unit_type(nlohmann::json json_json, std::filesystem::path path_path, int i, int x, UnitType untp_default);

template <typename T>
void generate_default(std::shared_ptr<std::map<std::string, T>> p_m_s_t_map,
					  std::vector<std::filesystem::path> v_path_matching_paths,
					  T(*populate)(T t_t, nlohmann::json json_json, std::filesystem::path path_path));

template <typename T>
std::shared_ptr<sf::Texture> generate_atlas(std::vector<std::filesystem::path>  v_path_matching_paths,
											std::shared_ptr<std::map<std::string, T>> p_m_s_p_t_map,
											T(*generate)(nlohmann::json json_json, std::filesystem::path path_path, int i, int x, T t_default),
											T(*populate)(T t_t, nlohmann::json json_json, std::filesystem::path path_path),
											int i_tile_size);

std::map<std::string, int> m_s_i_calculate_atlas_dimensions(int images);

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

	std::shared_ptr<sf::Texture> p_txtr_get_unit_type_atlas();

	std::map<std::string, SoilCover> m_s_slcv_get_soil_covers();

	std::map<std::string, UnitType> m_s_untp_get_unit_types();

	void generate_maps();

private:
	int i_tile_size = 32;

	void save_map(std::string s_in_name, std::string s_out_name, std::filesystem::path path_path);

	Unit unit_populate_unit(nlohmann::json json_json, std::filesystem::path path_path);

	std::shared_ptr<Map> p_map_populate_map(nlohmann::json json_json, std::filesystem::path path_path);

	std::shared_ptr<std::map<std::string, SoilCover>> p_m_s_slcv_soil_covers;

	std::shared_ptr<std::map<std::string, UnitType>> p_m_s_untp_unit_types;

	std::map<std::string, std::shared_ptr<Map>> m_s_p_map_maps;

	std::shared_ptr<sf::Texture> p_txtr_soil_cover_atlas;

	std::shared_ptr<sf::Texture> p_txtr_unit_type_atlas;

	std::filesystem::path path_roaming_data_path;
};

#endif