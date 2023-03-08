#include <string>
#include <vector>
#include <unordered_map>

#pragma once

namespace package_configuration {
	struct PackageConfigurationInformation {
		std::string url;
		std::string branch;
		std::string build_command;
		std::string post_build_command;
		std::vector<std::string> dependencies;
		std::vector<std::string> build_dependencies;
		std::string commit;
	};

	std::unordered_map<std::string, PackageConfigurationInformation> get_package_configuration();
}


namespace YAML {
	template<>
	struct convert<package_configuration::PackageConfigurationInformation> {
		static Node encode(const package_configuration::PackageConfigurationInformation& rhs);
		static bool decode(const Node& node, package_configuration::PackageConfigurationInformation& rhs);
	};
}
