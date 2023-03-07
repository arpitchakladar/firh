#include <ftw.h>
#include <unistd.h>
#include <string>
#include <cstdio>
#include <fstream>
#include <iostream>

#include "filesystem.hpp"

static int _unlink_cb(const char* fpath, const struct stat* _sb, int _typeflag, struct FTW* _ftwbuf) {
	return remove(fpath);
}

namespace filesystem {
	void remove_directory(const std::string& path) {
		nftw(path.c_str(), _unlink_cb, 64, FTW_DEPTH | FTW_PHYS);
	}

	std::fstream open_file(const std::string& path) {
		std::fstream file_stream;
		file_stream.open(path, std::ios_base::out);
		return file_stream;
	}
}
