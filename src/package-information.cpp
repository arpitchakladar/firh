#include <string>
#include <unordered_map>
#include <fstream>

#include "yaml-cpp/yaml.h"

#include "package-information.hpp"
#include "file-system.hpp"
#include "path.hpp"

std::unordered_map<std::string, PackageInformation> PackageInformation::get() {
	std::unordered_map<std::string, PackageInformation> package_informations;
	YAML::Node package_informations_data = YAML::LoadFile(Path::package_information_file);

	for (const YAML::detail::iterator_value& package_information : package_informations_data)
		package_informations.insert({ package_information.first.as<std::string>(), package_information.second.as<PackageInformation>() });

	return package_informations;
}

void PackageInformation::write(std::unordered_map<std::string, PackageInformation>&& package_informations) {
	std::fstream package_informations_file = FileSystem::open_file(Path::package_information_file);
	package_informations_file << YAML::Node(package_informations);
	package_informations_file.close();
}

YAML::Node YAML::convert<PackageInformation>::encode(const PackageInformation& rhs) {
	YAML::Node node;
	node["commit"] = rhs.commit;
	node["last_updated"] = rhs.last_updated;

	return node;
}

bool YAML::convert<PackageInformation>::decode(const YAML::Node& node, PackageInformation& rhs) {
	if (!node.IsMap())
		return false;

	rhs.commit = std::move(node["commit"].as<std::string>());
	rhs.last_updated = std::move(node["last_updated"].as<std::string>());

	return true;
}
