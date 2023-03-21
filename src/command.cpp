#include <string>

#include "command.hpp"
#include "file-system.hpp"
#include "path.hpp"
#include "loader/infinite.hpp"

bool Command::run(const std::string& name, const std::string& command, Command::Type command_type) {
	std::string absolute_log_directory_path = Path::build_log_cache_directory + name;
	FileSystem::create_directory(absolute_log_directory_path);

	std::string type;
	std::string loader_message;

	switch (command_type) {
	case Command::Type::Build:
		type = "build";
		loader_message = "Building \033[32;1m" + name + "\033[m";
		break;
	
	case Command::Type::PostBuild:
		type = "post-build";
		loader_message = "Running post-build for \033[32;1m" + name + "\033[m";
	}

	std::string final_command =
		"cd " + Path::git_repository_cache_directory + name
		+ " && " + command
		+ " > " + absolute_log_directory_path + "/"
		+ type + ".log 2>&1";

	InfiniteLoader loader(loader_message);
	bool success = system(final_command.c_str()) == 0;
	loader.finish(success);

	return success;
}
