#include <string>
#include <vector>

#include "git.hpp"
#include "package/package-configuration.hpp"

#pragma once

class Package {
public:
	Package(PackageConfiguration&& configuration);
	/*
	void build();
	static std::vector<Package> load_packages();
	static void build_packages(std::vector<Package>& packages);*/

private:
	Git _git;
	std::string _name;
	std::vector<Package*> _dependencies;
	bool _built;
	bool _success;
};
