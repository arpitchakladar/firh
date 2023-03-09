#include <string>
#include <vector>
#include <unordered_map>

#include "git.hpp"
#include "package_configuration.hpp"

#pragma once

class Package {
public:
	Package(const std::string& name, const std::string& repository_url, const std::string& branch, const std::string& build_command, const std::string& post_build_command, std::vector<Package*>&& dependencies, std::vector<Package*>&& build_dependencies, const std::string& commit);
	void build();

private:
	std::string _name;
	GitRepository _repository;
	std::string _branch;
	std::string _build_command;
	std::string _post_build_command;
	std::vector<Package*> _dependencies;
	std::vector<Package*> _build_dependencies;
	std::string _commit;
	bool _built;
};

void create(const std::string& name, std::unordered_map<std::string, Package*>& packages, const std::unordered_map<std::string, PackageConfiguration>& package_configurations);
