#include <cstdlib>
#include <iostream>
#include <fstream>

#include "libgit2/git2.h"
#include "yaml-cpp/yaml.h"

#include "utils.hpp"

int main(int argc, char* argv[]) {
	git_libgit2_init();
	const char* local_path = "/tmp/firh/repositories/arpitchakladar@i3kbar";
	remove_directory(local_path);
	git_repository *repository = NULL;
	git_clone(&repository, "https://github.com/arpitchakladar/i3kbar", local_path, NULL);
	git_oid oid_parent_commit;
	git_reference_name_to_id(&oid_parent_commit, repository, "HEAD");
	char commit_hex[GIT_OID_SHA1_HEXSIZE];
	git_oid_nfmt(commit_hex, GIT_OID_SHA1_HEXSIZE, &oid_parent_commit);
	std::cout << "Last commit = " << commit_hex << std::endl;
	std::string firh_package_list_path = std::string(std::getenv("HOME")) + "/.local/share/firh/package-info.yml";
	std::fstream firh_package_list_file;
	firh_package_list_file.open(firh_package_list_path, std::ios_base::out);
	YAML::Node firh_package_list = YAML::LoadFile(firh_package_list_path);
	YAML::Node current_package_info;
	current_package_info["commit"] = std::string(commit_hex);
	firh_package_list["i3kbar"] = current_package_info;
	firh_package_list_file << firh_package_list;
	return EXIT_SUCCESS;
}
