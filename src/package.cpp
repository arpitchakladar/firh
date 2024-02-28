#include <string>
#include <vector>
#include <unordered_map>
#include <ctime>
#include <iostream>
#include <fstream>

#include "git.hpp"
#include "package.hpp"
#include "package/package-configuration.hpp"
#include "command.hpp"
#include "path.hpp"
#include "file-system.hpp"
#include "loader/infinite.hpp"

Package::Package(PackageConfiguration&& configuration)
	: _configuration(std::move(configuration)),
		_git_repository(
			configuration.name,
			configuration.git_repository_remote_url,
			configuration.branch,
			configuration.commit
		),
		_built(false),
		_success(false)
{}

void Package::build() {
	if (!_built) {
		std::string build_script_path = Path::configuration_directory + _configuration.name + "/build.sh";
		InfiniteLoader loader("Building \033[32;1m" + _configuration.name + "\033[m");
		_success = Command::run(_configuration.name, build_script_path, "build.log");
		loader.finish(_success);
		_built = _success;
	}
}

std::vector<Package> Package::load_packages() {
	std::vector<std::string> package_directories = FileSystem::list_subdirectories(Path::configuration_directory);
	std::vector<Package> packages;

	for(const std::string& package_name : package_directories) {
		std::string package_directory = Path::configuration_directory + package_name + "/";
		PackageConfiguration configuration = YAML::LoadFile(package_directory + "config.yml")
			.as<PackageConfiguration>();
		// The name is not taken from the configuration but the name of the configuration folder
		configuration.name = package_name;
		packages.push_back(Package(std::move(configuration)));
	}

	return packages;
}

void Package::build_packages(std::vector<Package>& packages) {
	for (Package& package : packages) {
		bool build = true;

		for (const std::string& dependency_name : package._configuration.dependencies) {
			// Searching for the dependency
			Package* dependency;

			for (Package& dependency_package : packages) {
				if (dependency_package._configuration.name == dependency_name) {
					dependency = &dependency_package;
					break;
				}
			}

			// ensuring the dependency is built before the dependent package
			dependency->build();
			build = dependency->_success && dependency->_built;
			if (!build)
				break;
		}

		if (build) {
			package.build();
		}
	}
}
