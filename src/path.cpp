#include <string>

#include "path.hpp"
#include "file-system.hpp"

std::string Path::git_repository_cache_directory;
std::string Path::build_log_cache_directory;
std::string Path::package_configuration_file_path;
std::string Path::package_information_file_path;

void Path::initialize() {
#ifdef DEBUG
	std::string current_directory = CURRENT_DIRECTORY;
	std::string data_directory = current_directory + "/build/tests/";
	package_configuration_file_path = current_directory + "/tests/packages.yml";
#else
	std::string data_directory = "/usr/local/share/firh/";
	package_configuration_file_path = data_directory + "packages.yml";
	FileSystem::create_file(package_configuration_file_path);
#endif

	FileSystem::create_directory(data_directory);

#ifdef DEBUG
	git_repository_cache_directory = "/tmp/firh/repositories/";
#else
	git_repository_cache_directory = "/usr/local/share/firh/repositories/";
#endif
	FileSystem::create_directory(git_repository_cache_directory);

	build_log_cache_directory = "/tmp/firh/log/";
	FileSystem::create_directory(build_log_cache_directory);

	package_information_file_path = data_directory + ".package-data.yml";
	FileSystem::create_file(package_information_file_path);
}
