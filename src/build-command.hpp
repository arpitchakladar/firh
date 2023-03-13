#include <string>

#pragma once

class BuildCommand {
public:
	static bool run(const std::string& name, const std::string& command, const std::string& type);
};
