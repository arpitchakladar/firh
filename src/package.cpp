#include <string>
#include <vector>
#include <unordered_map>
#include <ctime>
#include <iostream>

#include "git.hpp"
#include "package.hpp"
#include "package-information.hpp"
#include "package-configuration.hpp"

Package::Package(const std::string& name, const std::string& repository_url, const std::string& branch, const std::string& build_command, const std::string& post_build_command, std::vector<Package*>&& dependencies, std::vector<Package*>&& build_dependencies, const std::string& commit)
	: _name(name), _branch(branch), _post_build_command(post_build_command), _dependencies(dependencies), _build_dependencies(build_dependencies), _commit(commit), _git_repository(_name, repository_url), _built(false) {
	_build_command = "cd " + _git_repository.get_local_path() + " && " + build_command;
	_post_build_command = "cd " + _git_repository.get_local_path() + " && " + post_build_command;
}

void Package::build(std::unordered_map<std::string, PackageInformation>& package_informations) {
	PackageInformation package_information;
	std::unordered_map<std::string, PackageInformation>::iterator package_information_entry = package_informations.find(_name);
	if (package_information_entry != package_informations.end()) {
		package_information = package_information_entry->second;
	}
	std::string current_commit = _git_repository.get_head_commit();
	if (!_built && package_information.commit != current_commit) {
		for (Package* package : _dependencies) {
			package->build(package_informations);
		}
		for (Package* package : _build_dependencies) {
			package->build(package_informations);
		}
		system(_build_command.c_str());
		_built = true;
		package_information.commit = current_commit;
		time_t _current_time = time(NULL);
		struct tm* current_time = localtime(&_current_time);
		std::string last_updated = asctime(current_time);
		last_updated.resize(last_updated.size() - 1);
		package_information.last_updated = std::move(last_updated);
		package_informations[_name] = package_information;
	}
}

void Package::post_build() {
	if (_built && !_post_build_command.empty()) {
		system(_post_build_command.c_str());
	}
}

std::unordered_map<std::string, Package> Package::from_configurations(const std::unordered_map<std::string, PackageConfiguration>& package_configurations) {
	std::unordered_map<std::string, Package> packages;
	for (const std::pair<std::string, PackageConfiguration>& package_configuration : package_configurations) {
		_from_configurations(package_configuration.first, packages, package_configurations);
	}
	return packages;
}

void Package::_from_configurations(const std::string& name, std::unordered_map<std::string, Package>& packages, const std::unordered_map<std::string, PackageConfiguration>& package_configurations) {
	if (packages.find(name) == packages.end()) {
		const PackageConfiguration& package_configuration = package_configurations.at(name);
		std::vector<Package*> dependencies;
		for (const std::string& dependency_name : package_configuration.dependencies) {
			_from_configurations(dependency_name, packages, package_configurations);
			dependencies.push_back(&packages.at(dependency_name));
		}
		std::vector<Package*> build_dependencies;
		for (const std::string& build_dependency_name : package_configuration.build_dependencies) {
			_from_configurations(build_dependency_name, packages, package_configurations);
			dependencies.push_back(&packages.at(build_dependency_name));
		}
		packages.insert({ name, Package(name, package_configuration.url, package_configuration.branch, package_configuration.build_command, package_configuration.post_build_command, std::move(dependencies),  std::move(build_dependencies), package_configuration.commit) });
	}
}
