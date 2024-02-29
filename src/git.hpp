#include <string>

#include "libgit2/git2.h"

#pragma once

class Git {
public:
	Git(
		const std::string& name,
		const std::string& url,
		const std::string& branch,
		const std::string& commit
	);
	static void initialize();
	void clone();
	inline const std::string& get_local_path() const { return _local_path; }
	inline const std::string& get_branch() const { return _branch; }
	inline const std::string& get_commit() const { return _commit; }

private:
	git_repository* _git_repository;
	std::string _name;
	std::string _local_path;
	std::string _branch;
	std::string _commit;
	std::string _url;
};
