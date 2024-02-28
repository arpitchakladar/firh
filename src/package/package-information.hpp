#include <string>
#include <unordered_map>

#include "yaml-cpp/yaml.h"

#pragma once

struct PackageInformation {
	std::string commit;
	std::string last_updated;
};

template<>
struct YAML::convert<PackageInformation> {
	static Node encode(const PackageInformation& rhs);
	static bool decode(const Node& node, PackageInformation& rhs);
};
