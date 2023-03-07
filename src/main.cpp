#include <cstdlib>
#include <iostream>
#include <fstream>

#include "yaml-cpp/yaml.h"

#include "filesystem.hpp"
#include "git.hpp"

int main(int argc, char* argv[]) {
	git_libgit2_init();
	git::Repository repository("i3kbar", "https://github.com/arpitchakladar/i3kbar");
	std::string last_commit = repository.get_head_commit();
	std::cout << "Last commit = " << last_commit << std::endl;
	std::string firh_package_list_path = std::string(std::getenv("HOME")) + "/.local/share/firh/package-info.yml";
	std::fstream firh_package_list_file = filesystem::open_file(firh_package_list_path);
	YAML::Node firh_package_list = YAML::LoadFile(firh_package_list_path);
	YAML::Node current_package_info;
	current_package_info["commit"] = last_commit;
	firh_package_list["i3kbar"] = current_package_info;
	firh_package_list_file << firh_package_list;
	//std::string build_command = "cd " + local_path + "&& make config=release";
	//system(build_command.c_str());
	return EXIT_SUCCESS;
}
