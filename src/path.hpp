#include <string>

#pragma once

class Path {
public:
	static std::string git_repository_cache_directory;
	static std::string build_log_cache_directory;
	static std::string package_configuration_file;
	static std::string package_information_file;
	static std::string patches_directory;
	static void initialize();
};
