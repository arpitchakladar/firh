#include <string>
#include <vector>
#include <unordered_map>

#include "yaml-cpp/yaml.h"

#include "package_configuration.hpp"
#include "filesystem.hpp"

static std::string _packages_path = "./tests/packages.yml";

std::unordered_map<std::string, PackageConfiguration> get_package_configurations() {
	std::unordered_map<std::string, PackageConfiguration> package_configuration;
	create_file(_packages_path);
	YAML::Node firh_packages = YAML::LoadFile(_packages_path);
	for (YAML::const_iterator it = firh_packages.begin(); it != firh_packages.end(); it++) {
		package_configuration[it->first.as<std::string>()] = it->second.as<PackageConfiguration>();
	}
	return package_configuration;
}

template<typename T>
static T _get_optional_node_field(const YAML::Node& node, std::string&& field) {
	if (node[field]) {
		return node[field].as<T>();
	} else {
		return T();
	}
}

namespace YAML {
	Node convert<PackageConfiguration>::encode(const PackageConfiguration& rhs) {
		Node node;
		node["url"] = rhs.url;
		node["branch"] = rhs.branch;
		node["build_command"] = rhs.build_command;
		if (rhs.post_build_command.size() > 0) node["post_build_command"] = rhs.post_build_command;
		if (rhs.dependencies.size() > 0) node["dependencies"] = rhs.dependencies;
		if (rhs.build_dependencies.size() > 0) node["build_dependencies"] = rhs.build_dependencies;
		if (rhs.commit.size() > 0) node["commit"] = rhs.commit;
		return node;
	}

	bool convert<PackageConfiguration>::decode(const Node& node, PackageConfiguration& rhs) {
		if (!node.IsMap()) {
			return false;
		}
		rhs.url = std::move(node["url"].as<std::string>());
		rhs.branch = std::move(node["branch"].as<std::string>());
		rhs.build_command = std::move(node["build_command"].as<std::string>());
		rhs.post_build_command = _get_optional_node_field<std::string>(node, "post_build_command");
		rhs.dependencies = _get_optional_node_field<std::vector<std::string>>(node, "dependencies");
		rhs.build_dependencies = _get_optional_node_field<std::vector<std::string>>(node, "build_dependencies");
		rhs.commit = _get_optional_node_field<std::string>(node, "commit");
		return true;
	}
}
