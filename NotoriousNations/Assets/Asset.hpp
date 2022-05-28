#pragma once
#ifndef Asset_hpp
#define Asset_hpp

#include <string>
#include <memory>

class Asset
{
public:
	Asset();
	Asset(std::string s_name);

	std::string s_get_name();

	bool v_set_name(std::string s_name);

private:
	std::string s_name;
};

#endif