#include <ftw.h>
#include <sys/stat.h>
#include <string>
#include <cstdio>
#include <fstream>
#include <fcntl.h>

#include "file-system.hpp"

static int _unlink_cb(const char* fpath, const struct stat* _sb, int _typeflag, struct FTW* _ftwbuf) {
	return remove(fpath);
}

void FileSystem::remove_directory(const std::string& path) {
	nftw(path.c_str(), _unlink_cb, 64, FTW_DEPTH | FTW_PHYS);
}

void FileSystem::create_directory(const std::string& path) {
	for (size_t i = 0; i < path.size(); i++)
		if (path[i] == '/')
			mkdir(path.substr(0, i).c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	if (path[path.size() - 1] != '/')
		mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}

std::fstream FileSystem::open_file(const std::string& path) {
	std::fstream file_stream;
	file_stream.open(path, std::ios::in | std::ios::out);

	if (!file_stream)
		file_stream.open(path, std::ios::in | std::ios::out | std::ios::trunc);

	return file_stream;
}

void FileSystem::create_file(const std::string& path) {
	open_file(path).close();
}
