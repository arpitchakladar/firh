#include <string>
#include <vector>

#pragma once

class FileSystem {
public:
	static void create_directory(const std::string& path);
	static std::vector<std::string> list_subdirectories(const std::string& path);
	static bool file_exists(const std::string& path);
	static std::fstream open_empty_file(const std::string& path);
};
