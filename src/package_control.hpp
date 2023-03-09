#include <string>

#include "yaml-cpp/yaml.h"

#pragma once

struct PackageControl {
	std::string commit;
};

namespace YAML {
	template<>
	struct convert<PackageControl> {
		static Node encode(const PackageControl& rhs) {
			Node node;
			node["commit"] = rhs.commit;
			return node;
		}

		static bool decode(const Node& node, PackageControl& rhs) {
			if (!node.IsMap()) {
				return false;
			}
			rhs.commit = std::move(node["commit"].as<std::string>());
			return true;
		}
	};
}
