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

static void _list_directory(const std::string& path, std::vector<std::string>& contents, const std::string& prefix = "") {
	DIR* directory = opendir((path + prefix).c_str());
	struct dirent* dir;
	if (directory) {
		while ((dir = readdir(directory)) != NULL) {
			if (dir->d_type == DT_REG) {
				contents.push_back(prefix + dir->d_name);
			} else if (std::string(dir->d_name) != "." && std::string(dir->d_name) != "..") {
				_list_directory(path, contents, prefix + dir->d_name + "/");
			}
		}

		closedir(directory);
	}
}

std::vector<std::string> FileSystem::list_directory(const std::string& path) {
	std::vector<std::string> contents;
	_list_directory(path, contents);
	return contents;
}

std::fstream FileSystem::open_file(const std::string& path) {
	std::fstream file_stream;
	file_stream.open(path, std::ios::in | std::ios::out);

	if (!file_stream)
		file_stream.open(path, std::ios::in | std::ios::out | std::ios::trunc);

	return file_stream;
}

std::fstream FileSystem::open_empty_file(const std::string& path) {
	std::fstream file_stream;
	file_stream.open(path, std::ios::in | std::ios::out | std::ios::trunc);

	return file_stream;
}



void FileSystem::create_file(const std::string& path) {
	open_file(path).close();
}
