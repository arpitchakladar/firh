#include <cstdlib>
#include <string>
#include <unordered_map>

#include "git.hpp"
#include "package.hpp"
#include "package-information.hpp"
#include "package-configuration.hpp"
#include "path.hpp"

int main(int argc, char* argv[]) {
	Path::init();
	GitRepository::init();
	std::unordered_map<std::string, PackageConfiguration> package_configurations = get_package_configurations();
	std::unordered_map<std::string, Package> packages = Package::from_configurations(package_configurations);
	std::unordered_map<std::string, PackageInformation> package_informations = get_package_informations();
	for (std::pair<const std::string, Package>& package : packages) {
		package.second.build(package_informations);
	}
	write_package_informations(std::move(package_informations));
	return EXIT_SUCCESS;
}
