#include <string>

#include "libgit2/git2.h"

#include "git.hpp"
#include "filesystem.hpp"

namespace git {
	Repository::Repository(std::string&& name, const std::string& remote_url)
		: _name(std::move(name)) {
		std::string local_path = "/tmp/firh/repositories/" + name;
		filesystem::remove_directory(local_path);
		git_clone(&_repository, remote_url.c_str(), local_path.c_str(), NULL);
	}

	std::string Repository::get_head_commit() const {
		git_oid oid_parent_commit;
		git_reference_name_to_id(&oid_parent_commit, _repository, "HEAD");
		std::string commit_hex(GIT_OID_SHA1_HEXSIZE + 1, '\0');
		git_oid_nfmt(&commit_hex[0], GIT_OID_SHA1_HEXSIZE + 1, &oid_parent_commit);
		return commit_hex;
	}
}
