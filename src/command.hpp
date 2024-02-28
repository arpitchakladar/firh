#include <string>
#include <cstdint>

#pragma once

class Command {
public:
	enum Type : uint8_t {
		Build,
		PostBuild
	};
	static bool run(const std::string& name, const std::string& command, Type command_type);
};
