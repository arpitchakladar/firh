#include <cstdlib>
#include <string>
#include <unordered_map>
#include <iostream>
#include <unistd.h>

#include "git.hpp"
#include "package.hpp"
#include "package-information.hpp"
#include "package-configuration.hpp"
#include "path.hpp"
#include "loader/infinite.hpp"

int main(int argc, char* argv[]) {
#ifndef DEBUG
	if (geteuid() != 0) {
		std::cout << "\033[31;1mYou need to run firh with root priviledges\033[m" << std::endl;
		return EXIT_FAILURE;
	}
#endif

	Path::initialize();
	GitRepository::initialize();

	std::cout << "\033[36;4mLoading configurations\033[m";
	std::unordered_map<std::string, PackageConfiguration> package_configurations = PackageConfiguration::get();
	std::unordered_map<std::string, PackageInformation> package_informations = PackageInformation::get();
	std::cout << " \033[34m[Finished]\033[m" << std::endl << "\033[36;4mCloning repositories\033[m" << std::endl;
	std::unordered_map<std::string, Package> packages = Package::from_configurations(package_configurations);

	InfiniteLoader loader("\033[36;4mAdding patches\033[m");
	for (std::pair<const std::string, Package>& package : packages)
		package.second.patch();
	loader.finish(true);

	std::cout << "\033[36;4mBuilding\033[m" << std::endl;
	for (std::pair<const std::string, Package>& package : packages)
		package.second.build(package_informations);

	std::cout << "\033[36;4mRunning post build\033[m" << std::endl;
	for (std::pair<const std::string, Package>& package : packages)
		package.second.post_build();

	std::cout << "\033[36;4mWriting updates\033[m" ;
	PackageInformation::write(std::move(package_informations));
	std::cout << " \033[34m[Finished]\033[m" << std::endl;

	return EXIT_SUCCESS;
}
