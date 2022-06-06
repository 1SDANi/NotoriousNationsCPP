#pragma once
#ifndef Asset_hpp
#define Asset_hpp

#include <string>
#include <memory>

#include <iostream>

class Asset
{
public:
	Asset();
	Asset(std::string s_name);

	std::string s_get_name();

	bool b_set_name(std::string s_name);

private:
	std::string s_name;
};

#endif