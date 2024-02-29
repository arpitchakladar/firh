#include <utility>

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

Package& PackageManager::_load_package(const std::string& name) {
	std::unordered_map<std::string, Package>::iterator package = _packages.find(name);

	if (package == _packages.end()) {
		std::string directory = Path::configuration_directory + name + "/";
		PackageConfiguration configuration = PackageConfiguration::from_file(directory + "config.yml");

		std::vector<Package*> dependencies;

		for (const std::string& dependency_name : configuration.dependencies) {
			dependencies.push_back(&_load_package(dependency_name));
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
