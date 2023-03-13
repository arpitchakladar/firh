#include <string>

#pragma once

class BuildCommand {
public:
	static bool run(const std::string& command, const std::string& context_directory, const std::string& log_path);
};
