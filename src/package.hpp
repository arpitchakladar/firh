#include <string>
#include <vector>
#include <unordered_map>

#include "git.hpp"
#include "package-configuration.hpp"
#include "package-information.hpp"

#pragma once

class Package {
public:
	Package(const std::string& name, const std::string& git_repository_url, const std::string& branch, const std::string& build_command, const std::string& post_build_command, std::vector<Package*>&& dependencies, std::vector<Package*>&& build_dependencies, const std::string& commit);
	void build(std::unordered_map<std::string, PackageInformation>& package_informations);
	void post_build();
	static std::unordered_map<std::string, Package> from_configurations(const std::unordered_map<std::string, PackageConfiguration>& package_configurations);

private:
	std::string _name;
	GitRepository _git_repository;
	std::string _build_command;
	std::string _post_build_command;
	std::vector<Package*> _dependencies;
	std::vector<Package*> _build_dependencies;
	bool _built;
	bool _build_success;
	static void _from_configurations(const std::string& name, std::unordered_map<std::string, Package>& packages, const std::unordered_map<std::string, PackageConfiguration>& package_configurations);
};
