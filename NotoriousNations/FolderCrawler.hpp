#pragma once
#ifndef FolderCrawler_hpp
#define FolderCrawler_hpp

#include <vector>
#include <string>
#include <iostream>
#include <filesystem>

class FolderCrawler
{
public:
	// static function
	// "s_path" is a string representing the path to crawl
	// "v_s_extensions" is a vector of strings representing extensions to look for
	// "v_path_matching_paths" is a vector of paths to append files with matching extensions to
	// returns true if at least 1 path was appended to "v_path_matching_paths"
	std::vector<std::filesystem::path> static inline b_crawl_folder(std::filesystem::path path_path, std::vector<std::wstring> v_path_extensions)
	{
		std::wstring wstr_extension;
		bool b_modified = false;
		std::vector<std::filesystem::path> v_path_matching_paths = {};

		for (std::filesystem::directory_entry dent_entry : std::filesystem::recursive_directory_iterator(path_path))
		{
			wstr_extension = dent_entry.path().extension().generic_wstring();

			if (std::find(v_path_extensions.begin(), v_path_extensions.end(), wstr_extension) != v_path_extensions.end())
			{
				v_path_matching_paths.push_back(dent_entry.path());
				b_modified = true;
			}
		}

		return v_path_matching_paths;
	}
};

#endif