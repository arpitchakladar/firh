#include <string>

#include "path.hpp"
#include "file-system.hpp"

std::string Path::data_directory;
std::string Path::build_log_directory;
std::string Path::configuration_directory;

void Path::initialize() {
#ifdef DEBUG
	std::string current_directory = CURRENT_DIRECTORY;
	data_directory = current_directory + "/build/tests/";
	configuration_directory = current_directory + "/tests/";
#else
	data_directory = "/usr/local/share/firh/";
	configuration_directory = data_directory;
#endif

	FileSystem::create_directory(data_directory);
	FileSystem::create_directory(configuration_directory);

	build_log_directory = "/tmp/firh/log/";
	FileSystem::create_directory(build_log_directory);
}
