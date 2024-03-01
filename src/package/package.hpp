#include <string>
#include <vector>

#include "git.hpp"
#include "package/package-configuration.hpp"

#pragma once

class Package {
public:
	Package(
		const std::string& name,
		std::vector<Package*>&& dependencies,
		PackageConfiguration&& configuration
	);
	void initialize();
	void build();

private:
	Git _git;
	std::string _name;
	std::vector<Package*> _dependencies;
	bool _built;
	bool _success;
};
