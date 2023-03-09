#include <cstdlib>
#include <string>
#include <ctime>
#include <unordered_map>
#include <iostream>

#include "yaml-cpp/yaml.h"

#include "filesystem.hpp"
#include "git.hpp"
#include "package.hpp"
#include "package_information.hpp"
#include "package_configuration.hpp"

int main(int argc, char* argv[]) {
	git_libgit2_init();
	std::unordered_map<std::string, PackageConfiguration> package_configurations = get_package_configurations();
	std::unordered_map<std::string, Package> packages = Package::from_configurations(package_configurations);
	std::unordered_map<std::string, PackageInformation> package_informations = get_package_informations();
	for (std::pair<const std::string, Package>& package : packages) {
		package.second.build(package_informations);
	}
	write_package_informations(std::move(package_informations));
	return EXIT_SUCCESS;
}
