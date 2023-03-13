#include <string>

#include "build-command.hpp"
#include "file-system.hpp"
#include "path.hpp"

bool BuildCommand::run(const std::string& name, const std::string& command, const std::string& type) {
	std::string absolute_log_directory_path = Path::build_log_cache_directory + name;
	FileSystem::create_directory(absolute_log_directory_path);
	std::string final_command = "cd " + Path::git_repository_cache_directory + name + " && " + command + " > " + absolute_log_directory_path + "/" + type + ".log 2>&1";
	return system(final_command.c_str()) == 0;
}
