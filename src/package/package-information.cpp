#include <string>
#include <unordered_map>
#include <fstream>

#include "yaml-cpp/yaml.h"

#include "package/package-information.hpp"
#include "file-system.hpp"
#include "path.hpp"

YAML::Node YAML::convert<PackageInformation>::encode(const PackageInformation& rhs) {
	YAML::Node node;
	node["commit"] = rhs.commit;
	node["last_updated"] = rhs.last_updated;

	return node;
}

bool YAML::convert<PackageInformation>::decode(const YAML::Node& node, PackageInformation& rhs) {
	if (!node.IsMap())
		return false;

	rhs.commit = std::move(node["commit"].as<std::string>());
	rhs.last_updated = std::move(node["last_updated"].as<std::string>());

	return true;
}
