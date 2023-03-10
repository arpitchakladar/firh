#include <string>

#include "libgit2/git2.h"

#include "git.hpp"
#include "file-system.hpp"
#include "path.hpp"

GitRepository::GitRepository(const std::string& name, const std::string& remote_url) {
	_local_path = Path::git_repository_cache_directory + name;
	FileSystem::remove_directory(_local_path);
	git_clone(&_repository, remote_url.c_str(), _local_path.c_str(), NULL);
}

std::string GitRepository::get_head_commit() const {
	git_oid oid_parent_commit;
	git_reference_name_to_id(&oid_parent_commit, _repository, "HEAD");
	std::string commit_hex(GIT_OID_SHA1_HEXSIZE, '\0');
	git_oid_nfmt(&commit_hex[0], GIT_OID_SHA1_HEXSIZE, &oid_parent_commit);
	return commit_hex;
}

void GitRepository::init() {
	git_libgit2_init();
}
