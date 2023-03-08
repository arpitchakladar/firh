#include <string>
#include <vector>

#include "git.hpp"

#pragma once

namespace package {
	class Package {
	public:
		Package(std::string&& name, const std::string& repository_url, const std::string& build_command, const std::string& post_build_command, std::vector<Package>&& dependencies, std::vector<Package>&& build_dependencies, std::string&& commit);
		void build();

	private:
		std::string _name;
		git::Repository _repository;
		std::string _build_command;
		std::string _post_build_command;
		std::vector<Package> _dependencies;
		std::vector<Package> _build_dependencies;
		std::string _commit;
	};
}
