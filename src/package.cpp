#include <string>
#include <vector>
#include <unordered_map>
#include <ctime>
#include <iostream>

#include "git.hpp"
#include "package.hpp"
#include "package-information.hpp"
#include "package-configuration.hpp"
#include "command.hpp"

Package::Package(
	const std::string& name,
	const std::string& git_repository_remote_url,
	std::string&& branch,
	std::string&& build_command,
	std::string&& post_build_command,
	std::vector<Package*>&& dependencies,
	std::string&& commit
)
	: _name(name),
		_build_command(build_command),
		_post_build_command(post_build_command),
		_dependencies(dependencies),
		_git_repository(_name, std::move(git_repository_remote_url), std::move(branch), std::move(commit)),
		_built(false),
		_success(false)
{}

void Package::build(std::unordered_map<std::string, PackageInformation>& package_informations) {
	if (!_built) {
		if (_build_command.empty())
			_success = true;
		else {
			PackageInformation package_information;
			std::unordered_map<std::string, PackageInformation>::iterator package_information_entry = package_informations.find(_name);
			if (package_information_entry != package_informations.end())
				package_information = package_information_entry->second;

			std::string current_commit = _git_repository.get_commit();

			if (package_information.commit != current_commit) {
				for (size_t i = 0; i < _dependencies.size() && _success; i++) {
					Package* package = _dependencies[i];
					package->build(package_informations);
					_success = package->_success;
				}

				if (_success) {
					_built = true;
					_success = Command::run(_name, _build_command, CommandType::Build);
					if (_success) {
						package_information.commit = std::move(current_commit);
						time_t _current_time = time(NULL);
						struct tm* current_time = localtime(&_current_time);
						std::string last_updated = asctime(current_time);
						last_updated.resize(last_updated.size() - 1);
						package_information.last_updated = std::move(last_updated);
						package_informations[_name] = package_information;
					}
				}
			} else {
				_success = true;
				std::cout << "Commits matched for \033[32;1m" << _name << "\033[m, no need to build \033[33m[Skipping]\033[m" << std::endl;
			}
		}
	}
}

void Package::post_build() {
	if (_built && _success && !_post_build_command.empty())
		Command::run(_name, _post_build_command, CommandType::PostBuild);
}

std::unordered_map<std::string, Package> Package::from_configurations(
	std::unordered_map<std::string, PackageConfiguration>& package_configurations
) {
	std::unordered_map<std::string, Package> packages;

	for (const std::pair<const std::string, PackageConfiguration>& package_configuration : package_configurations)
		_from_configurations(package_configuration.first, packages, package_configurations);

	return packages;
}

Package* Package::_from_configurations(
	const std::string& name,
	std::unordered_map<std::string, Package>& packages,
	std::unordered_map<std::string, PackageConfiguration>& package_configurations
) {
	std::unordered_map<std::string, Package>::iterator package = packages.find(name);
	if (package == packages.end()) {
		PackageConfiguration& package_configuration = package_configurations.at(name);
		std::vector<Package*> dependencies;

		for (const std::string& dependency_name : package_configuration.dependencies)
			dependencies.push_back(_from_configurations(dependency_name, packages, package_configurations));

		return &packages.insert({
			name,
			Package(
				name,
				package_configuration.git_repository_remote_url,
				std::move(package_configuration.branch),
				std::move(package_configuration.build_command),
				std::move(package_configuration.post_build_command),
				std::move(dependencies),
				std::move(package_configuration.commit)
			)
		}).first->second;
	} else
		return &package->second;
}
