#include <utility>
#include <stdexcept>

#include "logger.hpp"
#include "package/package.hpp"
#include "package/package-configuration.hpp"
#include "package/package-manager.hpp"
#include "path.hpp"
#include "file-system.hpp"

void PackageManager::load_packages() {
	std::vector<std::string> directories = FileSystem::list_subdirectories(Path::configuration_directory);

	for(const std::string& name : directories) {
		_load_package(name);
	}
}

void PackageManager::initialize_packages() {
	for (std::pair<std::string, Package> package : _packages) {
		package.second.initialize();
	}
}

void PackageManager::build_packages() {
	for (std::pair<std::string, Package> package : _packages) {
		bool build = true;
		for (Package* dependency : package.second.dependencies()) {
			dependency->build();
			build = dependency->built();
		}
		if (build) {
			package.second.build();
		} else {
			Logger::error("Failed to build \"" + package.first + "\" due to faulty dependency.");
		}
	}
}

Package& PackageManager::_load_package(const std::string& name) {
	std::unordered_map<std::string, Package>::iterator package = _packages.find(name);

	if (package == _packages.end()) {
		std::string directory = Path::configuration_directory + name + "/";
		PackageConfiguration configuration;
		try {
			configuration = PackageConfiguration::from_file(directory + "config.yml");
		} catch (const std::exception& exception) {
			throw std::runtime_error("Configuration for package \"" + name + "\" not found.");
		}

		std::vector<Package*> dependencies;

		for (const std::string& dependency_name : configuration.dependencies) {
			try {
				dependencies.push_back(&_load_package(dependency_name));
			} catch (const std::exception& exception) {
				throw std::runtime_error("Failed to resolve dependency \"" + dependency_name + "\" for package \"" + name + "\".");
			}
		}

		Package& package = _packages.insert({
			name,
			Package(
				name,
				std::move(dependencies),
				std::move(configuration)
			)
		}).first->second;

		return package;
	} else {
		return package->second;
	}
}

