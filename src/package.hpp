#include <string>
#include <vector>
#include <unordered_map>

#include "git.hpp"
#include "package/package-configuration.hpp"

#pragma once

class Package {
public:
	Package(PackageConfiguration&& configuration);
	void build();
	static std::vector<Package> load_packages();
	static void build_packages(std::vector<Package>& packages);

private:
	GitRepository _git_repository;
	PackageConfiguration _configuration;
	bool _built;
	bool _success;
};
