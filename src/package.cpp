#include <string>
#include <vector>
#include <unordered_map>

#include "git.hpp"
#include "package.hpp"
#include "package_configuration.hpp"

Package::Package(const std::string& name, const std::string& repository_url, const std::string& branch, const std::string& build_command, const std::string& post_build_command, std::vector<Package*>&& dependencies, std::vector<Package*>&& build_dependencies, const std::string& commit)
	: _name(name), _branch(branch), _post_build_command(post_build_command), _dependencies(dependencies), _build_dependencies(build_dependencies), _commit(commit), _repository(_name, repository_url), _built(false) {
	_build_command = "cd " + _repository.get_local_path() + "&& " + build_command;
	_post_build_command = "cd " + _repository.get_local_path() + "&& " + post_build_command;
}

void Package::build() {
	if (!_built) {
		for (Package* package : _dependencies) {
			package->build();
		}
		for (Package* package : _build_dependencies) {
			package->build();
		}
		system(_build_command.c_str());
		_built = true;
	}
}

void add_package(const std::string& name, std::unordered_map<std::string, Package>& packages, const std::unordered_map<std::string, PackageConfiguration>& package_configurations) {
	if (packages.find(name) == packages.end()) {
		const PackageConfiguration& package_configuration = package_configurations.at(name);
		std::vector<Package*> dependencies;
		for (const std::string& dependency_name : package_configuration.dependencies) {
			add_package(dependency_name, packages, package_configurations);
			dependencies.push_back(&packages.at(dependency_name));
		}
		std::vector<Package*> build_dependencies;
		for (const std::string& dependency_name : package_configuration.build_dependencies) {
			add_package(dependency_name, packages, package_configurations);
			dependencies.push_back(&packages.at(dependency_name));
		}
		packages.insert({ name, Package(name, package_configuration.url, package_configuration.branch, package_configuration.build_command, package_configuration.post_build_command, std::move(dependencies), std::move(build_dependencies), package_configuration.commit) });
	}
}
