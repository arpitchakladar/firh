#include <string>

#include "yaml-cpp/yaml.h"

#pragma once

struct PackageInformation {
	std::string commit;
};

namespace YAML {
	template<>
	struct convert<PackageInformation> {
		static Node encode(const PackageInformation& rhs) {
			Node node;
			node["commit"] = rhs.commit;
			return node;
		}

		static bool decode(const Node& node, PackageInformation& rhs) {
			if (!node.IsMap()) {
				return false;
			}
			rhs.commit = std::move(node["commit"].as<std::string>());
			return true;
		}
	};
}
