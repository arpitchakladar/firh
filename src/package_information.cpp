#include <string>
#include <unordered_map>
#include <fstream>

#include "yaml-cpp/yaml.h"

#include "package_information.hpp"
#include "filesystem.hpp"

static std::string _data_folder = std::string(std::getenv("HOME")) + "/.local/share/firh/";
static std::string _package_information_path = _data_folder + "package-control.yml";

std::unordered_map<std::string, PackageInformation> get_package_informations() {
	create_directory(_data_folder);
	std::unordered_map<std::string, PackageInformation> package_informations;
	create_file(_package_information_path);
	YAML::Node package_informations_data = YAML::LoadFile(_package_information_path);
	for (const YAML::detail::iterator_value& package_information : package_informations_data) {
		package_informations[package_information.first.as<std::string>()] = package_information.second.as<PackageInformation>();
	}
	return package_informations;
}

void write_package_informations(std::unordered_map<std::string, PackageInformation>&& package_informations) {
	std::fstream package_informations_file = open_file(_package_information_path);
	package_informations_file << YAML::Node(package_informations);
}

namespace YAML {
	Node convert<PackageInformation>::encode(const PackageInformation& rhs) {
		Node node;
		node["commit"] = rhs.commit;
		node["last_updated"] = rhs.last_updated;
		return node;
	}

	bool convert<PackageInformation>::decode(const Node& node, PackageInformation& rhs) {
		if (!node.IsMap()) {
			return false;
		}
		rhs.commit = std::move(node["commit"].as<std::string>());
		rhs.last_updated = std::move(node["last_updated"].as<std::string>());
		return true;
	}
}
