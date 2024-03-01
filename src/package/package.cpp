#include <string>
#include <vector>
#include <unordered_map>
#include <ctime>
#include <iostream>
#include <fstream>
#include <stdexcept>

#include "git.hpp"
#include "package.hpp"
#include "package/package-configuration.hpp"
#include "command.hpp"
#include "path.hpp"
#include "file-system.hpp"
#include "loader/infinite.hpp"

Package::Package(
	const std::string& name,
	std::vector<Package*>&& dependencies,
	PackageConfiguration&& configuration
)
	: _git(
			name,
			configuration.url,
			configuration.branch,
			configuration.commit
		),
		_name(std::move(name)),
		_built(false),
		_success(false),
		_dependencies(std::move(dependencies))
{}

void Package::initialize() {
	_git.clone();
}

void Package::build() {
	if (!_built) {
		std::string build_script_path = Path::configuration_directory + _name + "/build.sh";
		InfiniteLoader loader("Building \033[32;1m" + _name + "\033[m");
		_success = Command::run(_name, build_script_path, "build.log");
		loader.finish(_success);
		_built = _success;
	}
}
