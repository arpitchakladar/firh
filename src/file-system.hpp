#include <string>

#pragma once

class FileSystem {
public:
	static void remove_directory(const std::string& path);
	static void create_directory(const std::string& path);
	static std::fstream open_file(const std::string& path);
	static void create_file(const std::string& path);
};
