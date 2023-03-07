#include <cstdlib>
#include <iostream>
#include <fstream>

#include "libgit2/git2.h"
#include "yaml-cpp/yaml.h"

#include "filesystem.hpp"

int main(int argc, char* argv[]) {
	git_libgit2_init();
	std::string local_path = "/tmp/firh/repositories/arpitchakladar@i3kbar";
	remove_directory(local_path);
	git_repository *repository = NULL;
	git_clone(&repository, "https://github.com/arpitchakladar/i3kbar", local_path.c_str(), NULL);
	git_oid oid_parent_commit;
	git_reference_name_to_id(&oid_parent_commit, repository, "HEAD");
	std::string commit_hex(GIT_OID_SHA1_HEXSIZE + 1, '\0');
	git_oid_nfmt(&commit_hex[0], GIT_OID_SHA1_HEXSIZE + 1, &oid_parent_commit);
	std::cout << "Last commit = " << commit_hex << std::endl;
	std::string firh_package_list_path = std::string(std::getenv("HOME")) + "/.local/share/firh/package-info.yml";
	std::fstream firh_package_list_file;
	firh_package_list_file.open(firh_package_list_path, std::ios_base::out);
	YAML::Node firh_package_list = YAML::LoadFile(firh_package_list_path);
	YAML::Node current_package_info;
	current_package_info["commit"] = commit_hex;
	firh_package_list["i3kbar"] = current_package_info;
	firh_package_list_file << firh_package_list;
	std::string build_command = "cd " + local_path + "&& make config=release";
	system(build_command.c_str());
	return EXIT_SUCCESS;
}
