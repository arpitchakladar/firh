#include <string>
#include <vector>
#include <unordered_map>

#include "yaml-cpp/yaml.h"

#include "package-configuration.hpp"
#include "path.hpp"

std::unordered_map<std::string, PackageConfiguration> PackageConfiguration::get() {
	std::unordered_map<std::string, PackageConfiguration> package_configurations;
	YAML::Node package_configurations_data = YAML::LoadFile(Path::package_configuration_file_path);

	for (const YAML::detail::iterator_value& package_configuration : package_configurations_data)
		package_configurations[package_configuration.first.as<std::string>()] = package_configuration.second.as<PackageConfiguration>();

	return package_configurations;
}

YAML::Node YAML::convert<PackageConfiguration>::encode(const PackageConfiguration& rhs) {
	YAML::Node node;
	node["url"] = rhs.git_repository_remote_url;
	node["branch"] = rhs.branch;

	if (!rhs.build_command.empty())
		node["build"] = rhs.build_command;

	if (!rhs.post_build_command.empty())
		node["post-build"] = rhs.post_build_command;

	if (!rhs.dependencies.empty())
		node["dependencies"] = rhs.dependencies;

	if (!rhs.commit.empty())
		node["commit"] = rhs.commit;

	return node;
}

template<typename T>
static T _get_optional_node_field(const YAML::Node& node, std::string&& field) {
	return node[field] ? node[field].as<T>() : T();
}

bool YAML::convert<PackageConfiguration>::decode(const YAML::Node& node, PackageConfiguration& rhs) {
	if (!node.IsMap())
		return false;

	rhs.git_repository_remote_url = node["url"].as<std::string>();
	rhs.branch = _get_optional_node_field<std::string>(node, "branch");
	rhs.build_command = _get_optional_node_field<std::string>(node, "build");
	rhs.post_build_command = _get_optional_node_field<std::string>(node, "post-build");
	rhs.dependencies = _get_optional_node_field<std::vector<std::string>>(node, "dependencies");
	rhs.commit = _get_optional_node_field<std::string>(node, "commit");

	return true;
}
