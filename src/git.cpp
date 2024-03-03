#include <string>

#include "git2.h"

#include "git.hpp"
#include "file-system.hpp"
#include "path.hpp"
#include "loader/progress-loader.hpp"
#include "logger.hpp"

static int _fetch_progress(
	const git_indexer_progress *stats,
	void *bar_loader_payload
) {
	ProgressLoader& loader = *((ProgressLoader*) bar_loader_payload);
	loader.update_loader((stats->indexed_objects * 100) / stats->total_objects);
	return 0;
}

Git::Git(
	const std::string& name,
	const std::string& url,
	const std::string& branch,
	const std::string& commit
)
	: _local_path(Path::configuration_directory + name + "/repository"),
		_branch(branch),
		_commit(commit),
		_url(url),
		_name(name)
{}

void Git::clone() {
	bool reset_commit = true;

	// CLONING
	int open_status = git_repository_open_ext(
		&_git_repository,
		(_local_path + "/.git").c_str(),
		GIT_REPOSITORY_OPEN_NO_SEARCH,
		NULL
	);
	if (open_status == GIT_ENOTFOUND) {
		git_clone_options clone_options = GIT_CLONE_OPTIONS_INIT;

		if (!_branch.empty())
			clone_options.checkout_branch = _branch.c_str();

		ProgressLoader loader("Cloning repository \033[32;1m" + _name + "\033[m");
		clone_options.fetch_opts.callbacks.payload = &loader;
		clone_options.fetch_opts.callbacks.transfer_progress = _fetch_progress;
		clone_options.fetch_opts.depth = 1;
		git_clone(&_git_repository, _url.c_str(), _local_path.c_str(), &clone_options);
		loader.finish(true);
		reset_commit = false;
	} else {
		git_remote* remote;
		git_fetch_options opts = GIT_FETCH_OPTIONS_INIT;
		opts.depth = 1;
		git_remote_lookup(&remote, _git_repository, "origin");
		git_remote_fetch(remote, NULL, &opts, NULL);
		Logger::skipping("Found git repository for \033[32;1m" + _name + "\033[m");
	}

	// COMMITS
	git_oid oid_parent_commit;

	if (_commit.empty()) {
		git_reference_name_to_id(&oid_parent_commit, _git_repository, "HEAD");
		_commit = std::string(GIT_OID_SHA1_HEXSIZE, '\0');
		git_oid_nfmt(const_cast<char*>(_commit.c_str()), GIT_OID_SHA1_HEXSIZE, &oid_parent_commit);
	} else {
		git_oid_fromstrn(&oid_parent_commit, _commit.c_str(), GIT_OID_SHA1_HEXSIZE);
		reset_commit = true;
	}

	if (reset_commit) {
		git_object* current_commit_object;
		git_object_lookup(&current_commit_object, _git_repository, &oid_parent_commit, GIT_OBJECT_COMMIT);
		git_checkout_options checkout_options = GIT_CHECKOUT_OPTIONS_INIT;
		checkout_options.checkout_strategy = GIT_CHECKOUT_FORCE;
		git_reset(_git_repository, static_cast<git_object*>(current_commit_object), GIT_RESET_HARD, &checkout_options);
	}
}

void Git::initialize() {
	git_libgit2_init();
}

void Git::clear() {
	git_libgit2_shutdown();
}
