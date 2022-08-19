#include "Asset.hpp"

Asset::Asset()
{
	this->s_name = "Unnamed";
}

Asset::Asset(std::string s_name)
{
	this->s_name = s_name;
}

std::string Asset::s_get_name()
{
	return s_name;
}

void Asset::set_name(std::string s_name)
{
	this->s_name = s_name;
}