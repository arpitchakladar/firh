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
	std::vector<std::string> build_dependencies;
	std::string commit;
};

std::unordered_map<std::string, PackageConfiguration> get_package_configuration();

namespace YAML {
	template<>
	struct convert<PackageConfiguration> {
		static Node encode(const PackageConfiguration& rhs);
		static bool decode(const Node& node, PackageConfiguration& rhs);
	};
}
