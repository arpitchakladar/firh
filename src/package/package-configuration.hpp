#include <string>
#include <vector>

#include "yaml-cpp/yaml.h"

#pragma once

struct PackageConfiguration {
	std::string name;
	std::string url;
	std::string branch;
	std::vector<std::string> dependencies;
	std::string commit;
};

template<>
struct YAML::convert<PackageConfiguration> {
	static YAML::Node encode(const PackageConfiguration& rhs);
	static bool decode(const YAML::Node& node, PackageConfiguration& rhs);
};
