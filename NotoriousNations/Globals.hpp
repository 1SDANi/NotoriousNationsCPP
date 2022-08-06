#pragma once
#ifndef Globals_hpp
#define Globals_hpp

#include "Camera.hpp"
#include "Controller.hpp"
#include "Window.hpp"

#include "Assets/AssetMaps.hpp"
#include "Assets/Menu.hpp"

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

    std::shared_ptr<AssetMaps> p_asmp_get_asset_maps();

    std::shared_ptr<Camera> p_cmra_get_camera();

    std::shared_ptr<Menu> p_menu_get_menu();

    std::filesystem::path path_get_roaming_data_path();

    Controller cntr_get_controller(int i_controller);

    Vector2 vec2_get_window_size();

    sf::Vector2i vc2i_get_mouse_position();

    bool b_is_open() const;

    void update_window();

    void begin_draw();
    void draw(const sf::Drawable& drawable);
    void end_draw();

    void update_controllers();

    void update_mouse_wheel_input(int i_wheel, float f_delta);

    void gained_focus();

    void lost_focus();

    bool b_is_has_focus();

    void edit_soil_cover(std::string s_name, int i);

    static constexpr uint32_t hash(std::string_view data) noexcept {
        uint32_t hash = 5385;

        for (const auto& e : data) hash = ((hash << 5) + hash) + e;

        return hash;
    }

private:
    Globals() : wndw_window("Notorious Nations")
    {
        path_roaming_data_path = generate_roaming_data_path();

        p_asmp_asset_maps = std::shared_ptr<AssetMaps>(new AssetMaps(generate_roaming_data_path()));

        p_cmra_camera = std::shared_ptr<Camera>(new Camera(path_get_roaming_data_path()));

        p_menu_menu = std::shared_ptr<Menu>(new Menu(path_get_roaming_data_path()));

        m_i_cntr_controllers = std::map<int, Controller>();

        m_i_cntr_controllers[0] = Controller(path_get_roaming_data_path());

        b_has_focus = true;
    }

    Globals(Globals const&);

    Window wndw_window;

    // leave undefined
    void operator=(Globals const&);

    std::filesystem::path generate_roaming_data_path();

    std::shared_ptr<AssetMaps> p_asmp_asset_maps;

    std::shared_ptr<Camera> p_cmra_camera;

    std::shared_ptr<Menu> p_menu_menu;

    std::filesystem::path path_roaming_data_path;

    std::map<int, Controller> m_i_cntr_controllers;

    bool b_has_focus;
};

#endif