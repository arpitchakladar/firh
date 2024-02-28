#include <string>
#include <vector>
#include <unordered_map>
#include <ctime>
#include <iostream>
#include <fstream>

#include "git.hpp"
#include "package.hpp"
#include "package/package-information.hpp"
#include "package/package-configuration.hpp"
#include "command.hpp"
#include "path.hpp"
#include "file-system.hpp"
/*
Package::Package(
	const std::string& name,
	const std::string& git_repository_remote_url,
	std::string&& branch,
	std::vector<Package*>&& dependencies,
	std::string&& commit
)
	: _name(name),
		_dependencies(dependencies),
		_git_repository(_name, std::move(git_repository_remote_url), std::move(branch), std::move(commit)),
		_built(false),
		_success(false)
{}
*/
Package::Package(
	PackageConfiguration&& package_configuration,
	PackageInformation&& package_information
)
	: _package_configuration(std::move(package_configuration)),
		_package_information(std::move(package_information))
{}
/*
void Package::build(std::unordered_map<std::string, PackageInformation>& package_informations) {
	if (!_built) {
		std::string build_script_path = Path::configuration_directory + _name + "/build.sh";
		std::cout << build_script_path << std::endl;
		if (FileSystem::file_exists(build_script_path)) {
			PackageInformation package_information;
			std::unordered_map<std::string, PackageInformation>::iterator package_information_entry = package_informations.find(_name);
			if (package_information_entry != package_informations.end())
				package_information = package_information_entry->second;

			std::string current_commit = _git_repository.get_commit();

			if (package_information.commit != current_commit) {
				_success = true;

				for (size_t i = 0; i < _dependencies.size() && _success; i++) {
					Package* package = _dependencies[i];
					package->build(package_informations);
					_success = package->_success;
				}

				if (_success) {
					_built = true;
					_success = Command::run(_name, build_script_path, Command::Build);
					if (_success) {
						package_information.commit = std::move(current_commit);
						time_t _current_time = time(NULL);
						tm* current_time = localtime(&_current_time);
						std::string last_updated = asctime(current_time);
						last_updated.resize(last_updated.size() - 1);
						package_information.last_updated = std::move(last_updated);
						package_informations[_name] = package_information;
					}
				}
			} else {
				_success = true;
				std::cout << "Commits matched for \033[32;1m" << _name << " \033[33m[Skipping]\033[m" << std::endl;
			}
		} else
			_success = true;
	}
}
*/
void Package::post_build() {
	std::string post_build_script_path = Path::configuration_directory + _package_configuration.name + "/post-build.sh";
	if (FileSystem::file_exists(post_build_script_path)) {
		if (_built && _success)
			Command::run(_package_configuration.name, post_build_script_path, Command::PostBuild);

		else
			std::cout << "Build skipped \033[32;1m" << _package_configuration.name << " \033[33m[Skipping]\033[m" << std::endl;
	}
}

std::vector<Package> Package::load_packages() {
	std::vector<std::string> package_directories = FileSystem::list_subdirectories(Path::configuration_directory);
	std::vector<std::string> loaded;
	for(const std::string& package_name : package_directories) {
		std::string package_directory = Path::configuration_directory + package_name + "/";
		PackageConfiguration package_configuration = YAML::LoadFile(package_directory + "config.yml")
			.as<PackageConfiguration>();
		if (package_configuration.name.empty())
			package_configuration.name = package_name;
	}
	return std::vector<Package>();
}
