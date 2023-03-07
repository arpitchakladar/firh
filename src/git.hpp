#include <string>

#include "libgit2/git2.h"

#pragma once

namespace git {
	class Repository {
	public:
		Repository(std::string&& name, const std::string& remote_url);
		std::string get_head_commit() const;

	private:
		git_repository *_repository;
	};
}
