#include <string>

#include "build-command.hpp"
#include "file-system.hpp"
#include "path.hpp"

bool BuildCommand::run(const std::string& command, const std::string& context_directory, const std::string& log_file_path) {
	std::string absolute_log_file_path = Path::build_log_cache_directory + log_file_path;
	std::string final_command = "cd " + context_directory + " && " + command + " > " + absolute_log_file_path + ".log 2> " + absolute_log_file_path + ".err.log";
	return system(final_command.c_str()) == 0;
}
