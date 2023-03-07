#include <ftw.h>
#include <unistd.h>
#include <cstdio>

int unlink_cb(const char* fpath, const struct stat* _sb, int _typeflag, struct FTW* _ftwbuf) {
	return remove(fpath);
}

void remove_directory(const char* path) {
	nftw(path, unlink_cb, 64, FTW_DEPTH | FTW_PHYS);
}
