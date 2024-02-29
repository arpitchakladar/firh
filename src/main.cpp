#include <cstdlib>
#include <string>
#include <unordered_map>
#include <iostream>
#include <unistd.h>
#include <stdexcept>

#include "git.hpp"
#include "package/package-manager.hpp"
#include "path.hpp"
#include "loader/infinite.hpp"
#include "logger.hpp"

int main(int argc, char* argv[]) {
#ifndef DEBUG
	if (geteuid() != 0) {
		Logger::error("You need to run firh with root priviledges");
		return EXIT_FAILURE;
	}
#endif

	Path::initialize();
	Git::initialize();

	PackageManager package_manager;

	Logger::job("Loading packages.");
	package_manager.load_packages();

	/*
	Logger::separator();

	Logger::job("Building packages.");
	try {
		Package::build_packages(packages);
	} catch (const std::exception& exception) {
		Logger::separator();
		Logger::error(exception.what());
	}*/

/*
	std::cout << "\033[36;4m\033[m";
	std::unordered_map<std::string, PackageConfiguration> package_configurations = PackageConfiguration::get();
	std::unordered_map<std::string, PackageInformation> package_informations = PackageInformation::get();
	std::cout << " \033[34m[Finished]\033[m" << std::endl << "\033[36;4mCloning repositories\033[m" << std::endl;
	std::unordered_map<std::string, Package> packages = Package::from_configurations(package_configurations);

	std::cout << "\033[36;4mBuilding\033[m" << std::endl;
	for (std::pair<const std::string, Package>& package : packages)
		package.second.build(package_informations);

	std::cout << "\033[36;4mRunning post build\033[m" << std::endl;
	for (std::pair<const std::string, Package>& package : packages)
		package.second.post_build();

	std::cout << "\033[36;4mWriting updates\033[m" ;
	PackageInformation::write(std::move(package_informations));
	std::cout << " \033[34m[Finished]\033[m" << std::endl;
*/
	return EXIT_SUCCESS;
}
