#include <string>
#include <vector>
#include <unordered_map>

#include "git.hpp"
#include "package/package-configuration.hpp"

#pragma once

class Package {
public:
	Package(PackageConfiguration&& package_configuration);
	void build();
	static std::vector<Package> load_packages();

private:
	GitRepository _git_repository;
	PackageConfiguration _package_configuration;
	bool _built;
	bool _success;
};
