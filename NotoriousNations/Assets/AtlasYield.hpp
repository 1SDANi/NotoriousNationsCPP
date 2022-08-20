#pragma once
#ifndef AtlasYield_hpp
#define AtlasYield_hpp

#include "MultiYield.hpp"

#include "Int2.hpp"

class AtlasYield : public MultiYield
{
public:
	AtlasYield();
	AtlasYield(std::string s_name, Int2 int2_atlas_coords);

	Int2 int2_get_atlas_coords();

private:
	Int2 int2_atlas_coords;
};
#endif