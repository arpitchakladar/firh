#include <string>

#include "path.hpp"
#include "file-system.hpp"

std::string Path::git_repository_cache_directory;
std::string Path::build_log_cache_directory;
std::string Path::package_configuration_file;
std::string Path::package_information_file;
std::string Path::patches_directory;

void Path::initialize() {
#ifdef DEBUG
	std::string current_directory = CURRENT_DIRECTORY;
	std::string data_directory = current_directory + "/build/tests/";
	package_configuration_file = current_directory + "/tests/packages.yml";
	patches_directory = current_directory + "/tests/patches/";
	git_repository_cache_directory = "/tmp/firh/repositories/";
#else
	std::string data_directory = "/usr/local/share/firh/";
	package_configuration_file = data_directory + "packages.yml";
	git_repository_cache_directory = "/usr/local/share/firh/repositories/";
	patches_directory = data_directory + "patches/";
	FileSystem::create_file(package_configuration_file);
#endif

	FileSystem::create_directory(data_directory);
	FileSystem::create_directory(git_repository_cache_directory);
	FileSystem::create_directory(patches_directory);

	build_log_cache_directory = "/tmp/firh/log/";
	FileSystem::create_directory(build_log_cache_directory);

	package_information_file = data_directory + ".package-data.yml";
	FileSystem::create_file(package_information_file);
}
