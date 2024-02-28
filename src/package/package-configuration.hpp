#include <string>
#include <vector>
#include <unordered_map>

#include "yaml-cpp/yaml.h"

#pragma once

struct PackageConfiguration {
	std::string name;
	std::string git_repository_remote_url;
	std::string branch;
	std::vector<std::string> dependencies;
	std::string commit;
};

template<>
struct YAML::convert<PackageConfiguration> {
	static YAML::Node encode(const PackageConfiguration& rhs);
	static bool decode(const YAML::Node& node, PackageConfiguration& rhs);
};
