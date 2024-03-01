#include <string>
#include <unordered_map>

#include "package/package.hpp"

#pragma once

class PackageManager {
public:
	void load_packages();
	void initialize_packages();
	void build_packages();

private:
	std::unordered_map<std::string, Package> _packages;
	Package& _load_package(const std::string& name);
};
