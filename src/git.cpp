#include <string>

#include "libgit2/git2.h"

#include "git.hpp"
#include "file-system.hpp"
#include "path.hpp"
#include "loader/bar.hpp"

#include <iostream>

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
	std::string&& branch,
	std::string&& commit
)
	: _local_path(Path::git_repository_cache_directory + name),
		_branch(std::move(branch)),
		_commit(std::move(commit))
{
	FileSystem::remove_directory(_local_path);
	git_clone_options clone_options = GIT_CLONE_OPTIONS_INIT;

	if (!_branch.empty())
		clone_options.checkout_branch = branch.c_str();

	BarLoader loader("Cloning repository \033[32;1m" + name + "\033[m");
	clone_options.fetch_opts.callbacks.payload = &loader;
	clone_options.fetch_opts.callbacks.transfer_progress = _fetch_progress;
	git_clone(&_git_repository, remote_url.c_str(), _local_path.c_str(), &clone_options);
	loader.finish(true);

	if (_commit.empty()) {
		git_oid oid_parent_commit;
		git_reference_name_to_id(&oid_parent_commit, _git_repository, "HEAD");
		git_oid_nfmt(const_cast<char*>(_commit.c_str()), GIT_OID_SHA1_HEXSIZE, &oid_parent_commit);
	} else {
		git_oid oid_parent_commit;
		git_oid_fromstrn(&oid_parent_commit, _commit.c_str(), GIT_OID_SHA1_HEXSIZE);
		git_object* current_commit_object;
		git_object_lookup(&current_commit_object, _git_repository, &oid_parent_commit, GIT_OBJECT_COMMIT);
		git_checkout_options checkout_options = GIT_CHECKOUT_OPTIONS_INIT;
		checkout_options.checkout_strategy = GIT_CHECKOUT_FORCE;
		git_reset(_git_repository, static_cast<git_object*>(current_commit_object), GIT_RESET_HARD, &checkout_options);
	}
}

void GitRepository::initialize() {
	git_libgit2_init();
}
