#include <string>
#include <vector>

#include "git.hpp"
#include "package.hpp"

namespace package {
	Package::Package(std::string&& name, const std::string& repository_url, const std::string& build_command, const std::string& post_build_command, std::vector<Package>&& dependencies, std::vector<Package>&& build_dependencies, std::string&& commit)
		: _name(name), _post_build_command(post_build_command), _dependencies(dependencies), _build_dependencies(build_dependencies), _commit(commit), _repository(_name, repository_url) {
		_build_command = "cd " + _repository.get_local_path() + "&& " + build_command;
		_post_build_command = "cd " + _repository.get_local_path() + "&& " + post_build_command;
	}

	void Package::build() {
		system(_build_command.c_str());
	}
}
