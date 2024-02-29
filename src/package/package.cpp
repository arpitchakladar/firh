#include <string>
#include <vector>
#include <unordered_map>
#include <ctime>
#include <iostream>
#include <fstream>
#include <stdexcept>

#include "git.hpp"
#include "package.hpp"
#include "package/package-configuration.hpp"
#include "command.hpp"
#include "path.hpp"
#include "file-system.hpp"
#include "loader/infinite.hpp"

Package::Package(PackageConfiguration&& configuration)
	: _git(
			configuration.name,
			configuration.url,
			configuration.branch,
			configuration.commit
		),
		_built(false),
		_success(false),
		_name(configuration.name)
{}
/*
void Package::build() {
	if (!_built) {
		std::string build_script_path = Path::configuration_directory + _configuration.name + "/build.sh";
		InfiniteLoader loader("Building \033[32;1m" + _configuration.name + "\033[m");
		_success = Command::run(_configuration.name, build_script_path, "build.log");
		loader.finish(_success);
		_built = _success;
	}
}



void Package::build_packages(std::vector<Package>& packages) {
	for (Package& package : packages) {
		bool build = true; // to see if all dependencies built successfully

		for (const std::string& dependency_name : package._configuration.dependencies) {
			// Searching for the dependency
			Package* dependency = nullptr;

			for (Package& dependency_package : packages) {
				if (dependency_package._configuration.name == dependency_name) {
					dependency = &dependency_package;
					break;
				}
			}

			// ensuring the dependency is built before the dependent package
			if (dependency == nullptr) {
				build = false;
				throw std::runtime_error("Dependency \"" + dependency_name + "\" for package \"" + package._configuration.name + "\" not found.");
			} else {
				dependency->build();
				build = dependency->_success && dependency->_built;
				if (!build)
					break;
			}
		}

		if (build) {
			package.build();
		}
	}
}*/
