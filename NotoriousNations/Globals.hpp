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
    void draw(const GradientSprite gtsp_gradient_sprite, std::shared_ptr<sf::Shader> shdr_shader);
    void end_draw();

    void update_controllers();

    void update_mouse_wheel_input(int i_wheel, float f_delta);

    void gained_focus();

    void lost_focus();

    bool b_is_has_focus();

    std::string s_get_namebox_text();

    std::string s_get_namebox_text_sub();

    std::string s_get_namebox_text_dom();

    void set_namebox_text_dom(std::string s_text);

    void set_namebox_text_sub(std::string s_text);

    void edit_soil_cover(std::string s_name, int i);

    std::string s_get_current_map();

    std::shared_ptr<Map> p_map_get_current_map();

    std::shared_ptr<Player> plyr_get_turn_player();

    std::shared_ptr<sf::Shader> p_shdr_get_player_color_shader();

    static constexpr uint32_t hash(std::string_view data) noexcept {
        uint32_t hash = 5385;

        for (const auto& e : data) hash = ((hash << 5) + hash) + e;

        return hash;
    }

private:
    Globals() : wndw_window("Notorious Nations")
    {
        path_roaming_data_path = generate_roaming_data_path();

        p_shdr_player_color_shader = std::make_shared<sf::Shader>();

        if (p_shdr_player_color_shader->loadFromFile(path_roaming_data_path.string() + "\\PlayerColorShader.frag", sf::Shader::Type::Fragment))
        {
            std::wcout << "shader loaded from " << path_roaming_data_path.c_str() << "\\PlayerColorShader.frag\n";
        }

        p_asmp_asset_maps = std::shared_ptr<AssetMaps>(new AssetMaps(generate_roaming_data_path()));

        p_cmra_camera = std::shared_ptr<Camera>(new Camera(path_get_roaming_data_path()));

        p_menu_menu = std::shared_ptr<Menu>(new Menu(path_get_roaming_data_path()));

        m_i_cntr_controllers = std::map<int, Controller>();

        m_i_cntr_controllers[0] = Controller(path_get_roaming_data_path());

        b_has_focus = true;

        s_namebox_text_dom = "";

        s_namebox_text_sub = "";

        s_current_map = "Test Map 1";
    }

    Globals(Globals const&);

    Window wndw_window;

    // leave undefined
    void operator=(Globals const&);

    std::filesystem::path generate_roaming_data_path();

    std::string s_namebox_text_dom;

    std::string s_namebox_text_sub;

    std::string s_current_map;

    std::shared_ptr<AssetMaps> p_asmp_asset_maps;

    std::shared_ptr<Camera> p_cmra_camera;

    std::shared_ptr<Menu> p_menu_menu;

    std::shared_ptr<sf::Shader> p_shdr_player_color_shader;

    std::filesystem::path path_roaming_data_path;

    std::map<int, Controller> m_i_cntr_controllers;

    bool b_has_focus;
};

#endif