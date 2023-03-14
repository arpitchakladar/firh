#include <string>

#include "libgit2/git2.h"

#include "git.hpp"
#include "file-system.hpp"
#include "path.hpp"
#include "loader.hpp"

static int _fetch_progress(
	const git_indexer_progress *stats,
	void *bar_loader_payload
) {
	BarLoader& loader = *((BarLoader*) bar_loader_payload);
	loader.update_loader((stats->indexed_objects * 100) / stats->total_objects);
	return 0;
}

GitRepository::GitRepository(
	const std::string& name,
	const std::string& remote_url,
	const std::string& branch,
	const std::string& head_commit
)
	: _local_path(Path::git_repository_cache_directory + name),
		_branch(branch),
		_head_commit(head_commit)
{
	FileSystem::remove_directory(_local_path);
	git_clone_options clone_options = GIT_CLONE_OPTIONS_INIT;
	if (!_branch.empty()) {
		clone_options.checkout_branch = branch.c_str();
	}
	BarLoader loader("Cloning repository \033[32;1m" + name + "\033[m");
	clone_options.fetch_opts.callbacks.payload = &loader;
	clone_options.fetch_opts.callbacks.transfer_progress = _fetch_progress;
	git_clone(&_git_repository, remote_url.c_str(), _local_path.c_str(), &clone_options);
	loader.finish(true);
	if (_head_commit.empty()) {
		git_oid oid_parent_commit;
		git_reference_name_to_id(&oid_parent_commit, _git_repository, "HEAD");
		_head_commit = std::string(GIT_OID_SHA1_HEXSIZE, '\0');
		git_oid_nfmt(&_head_commit[0], GIT_OID_SHA1_HEXSIZE, &oid_parent_commit);
	}
}

void GitRepository::init() {
	git_libgit2_init();
}
