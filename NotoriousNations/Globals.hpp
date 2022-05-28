#pragma once
#ifndef Globals_hpp
#define Globals_hpp

#include "Assets/AssetMaps.hpp"

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

private:
    Globals() { }

    Globals(Globals const&);

    // leave undefined
    void operator=(Globals const&);

private:
    AssetMaps asmp_asset_maps;
};

#endif