#include <string>

#pragma once

class Path {
public:
	static std::string build_log_directory;
	static std::string configuration_directory;
	static std::string data_directory;
	static void initialize();
};
