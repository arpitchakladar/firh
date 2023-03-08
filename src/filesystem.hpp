#include <string>

#pragma once

namespace filesystem {
	void remove_directory(const std::string& path);
	std::fstream open_file(const std::string& path);
	void create_file(const std::string& path);
}
