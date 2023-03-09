#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <unistd.h>
#include <cstdio>
#include <sys/stat.h>

#include "yaml-cpp/yaml.h"

#include "filesystem.hpp"
#include "git.hpp"
#include "package_information.hpp"
#include "package_configuration.hpp"

static std::string _data_folder = std::string(std::getenv("HOME")) + "/.local/share/firh/";
static std::string _package_list_path = _data_folder + "package-control.yml";

int main(int argc, char* argv[]) {
	git_libgit2_init();
	create_directory(_data_folder);
	GitRepository repository("bazl", "https://github.com/arpitchakladar/bazl");
	std::string last_commit = repository.get_head_commit();
	std::cout << "Last commit = " << last_commit << std::endl;
	std::fstream package_list_file = open_file(_package_list_path);
	YAML::Node package_list = YAML::LoadFile(_package_list_path);
	YAML::Node current_package_control;
	package_list["bazl"] = PackageInformation {
		.commit = last_commit
	};
	package_list_file << package_list << std::endl;
	return EXIT_SUCCESS;
}
