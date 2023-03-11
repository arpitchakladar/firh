#include <string>

#pragma once

class Path {
public:
	static std::string git_repository_cache_directory;
	static std::string package_configuration_file_path;
	static std::string package_information_file_path;
	static void init();
};
