#include <string>
#include <vector>
#include <unordered_map>

#include "git.hpp"
#include "package/package-configuration.hpp"
#include "package/package-information.hpp"

#pragma once

class Package {
public:
	Package(
		PackageConfiguration&& package_configuration,
		PackageInformation&& package_information
	);
/*
	void build();

*/
	void post_build();
	static std::vector<Package> load_packages();

private:
	// GitRepository _git_repository;
	std::vector<Package*> _dependencies;
	PackageConfiguration _package_configuration;
	PackageInformation _package_information;
	bool _built;
	bool _success;
};
