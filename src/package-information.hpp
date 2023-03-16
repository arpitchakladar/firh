#include <string>
#include <unordered_map>

#include "yaml-cpp/yaml.h"

#pragma once

struct PackageInformation {
	std::string commit;
	std::string last_updated;
	static std::unordered_map<std::string, PackageInformation> get();
	static void write(std::unordered_map<std::string, PackageInformation>&& package_informations);
};

template<>
struct YAML::convert<PackageInformation> {
	static Node encode(const PackageInformation& rhs);
	static bool decode(const Node& node, PackageInformation& rhs);
};
