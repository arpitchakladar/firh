#include <utility>

#include "package/package.hpp"
#include "package/package-configuration.hpp"
#include "package/package-manager.hpp"
#include "path.hpp"
#include "file-system.hpp"

using PackageInsertion = std::pair<std::unordered_map<std::string, Package>::iterator, bool>;

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
		PackageConfiguration configuration = YAML::LoadFile(directory + "config.yml")
			.as<PackageConfiguration>();
		// The name is not taken from the configuration but the name of the configuration folder
		configuration.name = name;
		PackageInsertion package = _packages.insert({name, Package(std::move(configuration))});
		return package.first->second;
	} else {
		return package->second;
	}
}
