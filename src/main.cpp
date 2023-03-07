#include <cstdlib>
#include <iostream>

#include "git2/git2.h"

#include "utils.hpp"

int main(int argc, char* argv[]) {
	git_libgit2_init();
	const char* local_path = "/tmp/i3kbar";
	remove_directory(local_path);
	git_repository *repository = NULL;
	int clone_status = git_clone(&repository, "https://github.com/arpitchakladar/i3kbar", local_path, NULL);
	return clone_status;
}
