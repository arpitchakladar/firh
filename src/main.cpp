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

	try {
		Logger::job("Loading packages.");
		package_manager.load_packages();
		package_manager.initialize_packages();
		Logger::job("Building packages.");
		package_manager.build_packages();
	} catch (const std::exception& exception) {
		Logger::error(exception.what());
	}

	return EXIT_SUCCESS;
}
