#include <string>

#include "command.hpp"
#include "file-system.hpp"
#include "path.hpp"
#include "loader.hpp"

bool Command::run(const std::string& name, const std::string& command, CommandType command_type) {
	std::string absolute_log_directory_path = Path::build_log_cache_directory + name;
	FileSystem::create_directory(absolute_log_directory_path);
	std::string type = command_type == CommandType::Build ? "build" : "post-build";
	std::string final_command = "cd " + Path::git_repository_cache_directory + name + " && " + command + " > " + absolute_log_directory_path + "/" + type + ".log 2>&1";
	std::string loader_message = command_type == CommandType::Build
		? "Building \033[32;1m" + name + "\033[m"
		: "Running post-build for \033[32;1m" + name + "\033[m";
	InfiniteLoader loader(loader_message);
	bool success = system(final_command.c_str()) == 0;
	loader.finish(success);
	return success;
}
