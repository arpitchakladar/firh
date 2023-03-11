#include <string>

#include "libgit2/git2.h"

#pragma once

class GitRepository {
public:
	GitRepository(const std::string& name, const std::string& remote_url);
	std::string get_head_commit() const;
	static void init();
	const std::string& get_local_path() const { return _local_path; }

private:
	git_repository* _git_repository;
	std::string _local_path;
};
