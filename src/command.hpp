#include <string>
#include <cstdint>

#pragma once

class Command {
public:
	static bool run(const std::string& name, const std::string& command, std::string log_file);
};
