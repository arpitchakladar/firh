#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

#include "yaml-cpp/yaml.h"

#include "package_configuration.hpp"
#include "filesystem.hpp"

namespace package_configuration {
	std::unordered_map<std::string, PackageConfigurationInformation> get_package_configuration() {
		std::string firh_packages_path = std::string(std::getenv("HOME")) + "/.config/firh/packages.yml";
		filesystem::create_file(firh_packages_path);
		std::unordered_map<std::string, PackageConfigurationInformation> package_configuration;
		YAML::Node firh_packages = YAML::LoadFile(firh_packages_path);
		for (YAML::const_iterator it = firh_packages.begin(); it != firh_packages.end(); it++) {
			package_configuration[it->first.as<std::string>()] = it->second.as<PackageConfigurationInformation>();
		}
		return package_configuration;
	}
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
	Node convert<package_configuration::PackageConfigurationInformation>::encode(const package_configuration::PackageConfigurationInformation& rhs) {
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

	bool convert<package_configuration::PackageConfigurationInformation>::decode(const Node& node, package_configuration::PackageConfigurationInformation& rhs) {
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
