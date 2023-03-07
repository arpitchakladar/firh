#include <string>

#include "yaml-cpp/yaml.h"

#pragma once

namespace package_control {
	struct PackageControlInformation {
		std::string commit;
	};
}

namespace YAML {
	template<>
	struct convert<package_control::PackageControlInformation> {
		static Node encode(const package_control::PackageControlInformation& rhs) {
			Node node;
			node["commit"] = rhs.commit;
			return node;
		}

		static bool decode(const Node& node, package_control::PackageControlInformation& rhs) {
			if (!node.IsMap()) {
				return false;
			}
			rhs.commit = std::move(node["commit"].as<std::string>());
			return true;
		}
	};
}
