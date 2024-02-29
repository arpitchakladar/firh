#include <string>
#include <vector>

#include "yaml-cpp/yaml.h"

#include "package/package-configuration.hpp"
#include "path.hpp"

template<>
struct YAML::convert<PackageConfiguration> {
	static YAML::Node encode(const PackageConfiguration& rhs);
	static bool decode(const YAML::Node& node, PackageConfiguration& rhs);
};

YAML::Node YAML::convert<PackageConfiguration>::encode(const PackageConfiguration& rhs) {
	YAML::Node node;
	node["url"] = rhs.url;
	node["branch"] = rhs.branch;

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

	rhs.url = node["url"].as<std::string>();
	rhs.branch = _get_optional_node_field<std::string>(node, "branch");
	rhs.dependencies = _get_optional_node_field<std::vector<std::string>>(node, "dependencies");
	rhs.commit = _get_optional_node_field<std::string>(node, "commit");

	return true;
}

PackageConfiguration PackageConfiguration::from_file(const std::string& path) {
	return YAML::LoadFile(path).as<PackageConfiguration>();
}
