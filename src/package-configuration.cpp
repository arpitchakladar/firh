#include <string>
#include <vector>
#include <unordered_map>

#include "yaml-cpp/yaml.h"

#include "package-configuration.hpp"
#include "path.hpp"

std::unordered_map<std::string, PackageConfiguration> get_package_configurations() {
	std::unordered_map<std::string, PackageConfiguration> package_configurations;
	YAML::Node package_configurations_data = YAML::LoadFile(Path::package_configuration_file_path);
	for (const YAML::detail::iterator_value& package_configuration : package_configurations_data) {
		package_configurations[package_configuration.first.as<std::string>()] = package_configuration.second.as<PackageConfiguration>();
	}
	return package_configurations;
}

template<typename T>
static T _get_optional_node_field(const YAML::Node& node, std::string&& field) {
	if (node[field]) {
		return node[field].as<T>();
	} else {
		return T();
	}
}

YAML::Node YAML::convert<PackageConfiguration>::encode(const PackageConfiguration& rhs) {
	YAML::Node node;
	node["url"] = rhs.url;
	node["branch"] = rhs.branch;
	if (!rhs.build_command.empty()) node["build_command"] = rhs.build_command;
	if (!rhs.post_build_command.empty()) node["post_build_command"] = rhs.post_build_command;
	if (!rhs.dependencies.empty()) node["dependencies"] = rhs.dependencies;
	if (!rhs.commit.empty()) node["commit"] = rhs.commit;
	return node;
}

bool YAML::convert<PackageConfiguration>::decode(const YAML::Node& node, PackageConfiguration& rhs) {
	if (!node.IsMap()) {
		return false;
	}
	rhs.url = std::move(node["url"].as<std::string>());
	rhs.branch = _get_optional_node_field<std::string>(node, "branch");
	rhs.build_command = _get_optional_node_field<std::string>(node, "build_command");
	rhs.post_build_command = _get_optional_node_field<std::string>(node, "post_build_command");
	rhs.dependencies = _get_optional_node_field<std::vector<std::string>>(node, "dependencies");
	rhs.commit = _get_optional_node_field<std::string>(node, "commit");
	return true;
}
