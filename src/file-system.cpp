#include <ftw.h>
#include <sys/stat.h>
#include <string>
#include <cstdio>
#include <dirent.h>
#include <fstream>
#include <fcntl.h>
#include <filesystem>

#include <iostream>

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

bool FileSystem::is_directory(const std::string& path) {
	struct stat info;

	return (stat(path.c_str(), &info) == 0) && ((info.st_mode & S_IFDIR) != 0);
}

std::vector<std::string> FileSystem::list_subdirectories(const std::string& path) {
	const std::filesystem::path _path(path);
	std::vector<std::string> contents;
	for (const std::filesystem::directory_entry& dir_entry : std::filesystem::directory_iterator(_path))
		if (dir_entry.is_directory())
			contents.push_back(dir_entry.path().filename());
	return contents;
}

std::fstream FileSystem::open_file(const std::string& path) {
	std::fstream file_stream;
	file_stream.open(path, std::ios::in | std::ios::out);

	if (!file_stream)
		file_stream.open(path, std::ios::in | std::ios::out | std::ios::trunc);

	return file_stream;
}

bool FileSystem::file_exists(const std::string& path) {
	return std::filesystem::exists(path);
}

std::fstream FileSystem::open_empty_file(const std::string& path) {
	std::fstream file_stream;
	file_stream.open(path, std::ios::in | std::ios::out | std::ios::trunc);

	return file_stream;
}

void FileSystem::create_file(const std::string& path) {
	open_file(path).close();
}
