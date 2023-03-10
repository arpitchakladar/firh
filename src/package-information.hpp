#include <string>
#include <unordered_map>

#include "yaml-cpp/yaml.h"

#pragma once

struct PackageInformation {
	std::string commit;
	std::string last_updated;
};

std::unordered_map<std::string, PackageInformation> get_package_informations();
void write_package_informations(std::unordered_map<std::string, PackageInformation>&& package_informations);

namespace YAML {
	template<>
	struct convert<PackageInformation> {
		static Node encode(const PackageInformation& rhs);
		static bool decode(const Node& node, PackageInformation& rhs);
	};
}
