#pragma once
#ifndef SoilCover_hpp
#define SoilCover_hpp

#include "TileCover.hpp"

class SoilCover : public TileCover
{
public:
	SoilCover();
	SoilCover(std::string s_name, Int2 int2_atlas_coords);

private:

};

#endif