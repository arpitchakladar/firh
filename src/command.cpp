#include <string>

#include "command.hpp"
#include "file-system.hpp"
#include "path.hpp"

bool Command::run(const std::string& name, const std::string& command, std::string log_file) {
	std::string build_log_directory_path = Path::build_log_directory + name;
	std::string git_repository_directory = Path::configuration_directory + name + "/repository";
	FileSystem::create_directory(build_log_directory_path);

	std::string final_command =
		"cd " + git_repository_directory
		+ " && " + command
		+ " > " + build_log_directory_path + "/"
		+ log_file + " 2>&1";

	return system(final_command.c_str()) == 0;
}
