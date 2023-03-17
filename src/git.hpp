#include <string>

#include "libgit2/git2.h"

#pragma once

class GitRepository {
public:
	GitRepository(
		const std::string& name,
		const std::string& remote_url,
		std::string&& branch,
		std::string&& commit
	);
	static void initialize();
	const std::string& get_local_path() const { return _local_path; }
	const std::string& get_branch() const { return _branch; }
	const std::string& get_commit() const { return _commit; }

private:
	git_repository* _git_repository;
	std::string _local_path;
	std::string _branch;
	std::string _commit;
};
