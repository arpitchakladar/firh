#include <string>

#pragma once

enum class CommandType {
	Build,
	PostBuild
};

class Command {
public:
	static bool run(const std::string& name, const std::string& command, CommandType command_type);
};
