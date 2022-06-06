#pragma once
#ifndef Globals_hpp
#define Globals_hpp

#include "Assets/AssetMaps.hpp"
#include "Camera.hpp"
#include "Controller.hpp"

#include <Shlobj_core.h>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>

class Globals
{
public:
    static Globals& glob_get_globals()
    {
        static Globals instance;
        return instance;
    }

	AssetMaps asmp_get_asset_maps();

    Camera cmra_get_camera();

    std::filesystem::path path_get_roaming_data_path();

    Controller cntr_get_controller(int i_controller);

    void update_controllers();

    void update_mouse_wheel_input(int i_wheel, float f_delta);

private:
    Globals()
    {
        path_roaming_data_path = generate_roaming_data_path();

        asmp_asset_maps = AssetMaps(path_get_roaming_data_path());

        cmra_camera = Camera(path_get_roaming_data_path());

        m_i_cntr_controllers = std::map<int, Controller>();

        m_i_cntr_controllers[0] = Controller(path_get_roaming_data_path());
    }

    Globals(Globals const&);

    // leave undefined
    void operator=(Globals const&);

    std::filesystem::path generate_roaming_data_path();

    AssetMaps asmp_asset_maps;

    Camera cmra_camera;

    std::filesystem::path path_roaming_data_path;

    std::map<int, Controller> m_i_cntr_controllers;
};

#endif