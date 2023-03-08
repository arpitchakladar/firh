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
#include "package_control.hpp"
#include "package_configuration.hpp"

int main(int argc, char* argv[]) {
	git_libgit2_init();
	std::string firh_data_folder = std::string(std::getenv("HOME")) + "/.local/share/firh";
	mkdir(firh_data_folder.c_str(), 0777);
	git::Repository repository("bazl", "https://github.com/arpitchakladar/bazl");
	std::string last_commit = repository.get_head_commit();
	std::cout << "Last commit = " << last_commit << std::endl;
	std::string firh_package_list_path = firh_data_folder + "/package-control.yml";
	std::fstream firh_package_list_file = filesystem::open_file(firh_package_list_path);
	YAML::Node firh_package_list = YAML::LoadFile(firh_package_list_path);
	YAML::Node current_package_control;
	firh_package_list["bazl"] = package_control::PackageControlInformation {
		.commit = last_commit
	};
	firh_package_list_file << firh_package_list << std::endl;
	std::cout << YAML::Node(package_configuration::get_package_configuration()) << std::endl;
	return EXIT_SUCCESS;
}
