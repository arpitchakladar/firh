#include <string>
#include <vector>
#include <unordered_map>

#include "yaml-cpp/yaml.h"

#pragma once

struct PackageConfiguration {
	std::string url;
	std::string branch;
	std::string build_command;
	std::string post_build_command;
	std::vector<std::string> dependencies;
	std::string commit;
};

std::unordered_map<std::string, PackageConfiguration> get_package_configurations();

template<>
struct YAML::convert<PackageConfiguration> {
	static YAML::Node encode(const PackageConfiguration& rhs);
	static bool decode(const YAML::Node& node, PackageConfiguration& rhs);
};
