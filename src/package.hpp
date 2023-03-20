#include <string>
#include <vector>
#include <unordered_map>

#include "git.hpp"
#include "package-configuration.hpp"
#include "package-information.hpp"

#pragma once

class Package {
public:
	Package(
		const std::string& name,
		const std::string& git_repository_remote_url,
		std::string&& branch,
		std::string&& build_command,
		std::string&& post_build_command,
		std::vector<Package*>&& dependencies,
		std::string&& commit
	);
	void build(std::unordered_map<std::string, PackageInformation>& package_informations);
	void post_build();
	static std::unordered_map<std::string, Package> from_configurations(
		std::unordered_map<std::string, PackageConfiguration>& package_configurations
	);

private:
	std::string _name;
	GitRepository _git_repository;
	std::string _build_command;
	std::string _post_build_command;
	std::vector<Package*> _dependencies;
	bool _built;
	bool _success;
	static Package* _from_configurations(
		const std::string& name,
		std::unordered_map<std::string, Package>& packages,
		std::unordered_map<std::string, PackageConfiguration>& package_configurations
	);
};
