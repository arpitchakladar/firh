#include <string>
#include <thread>
#include <iostream>
#include <unistd.h>

#include "loader/infinite-loader.hpp"
#include "loader/_utils.hpp"

#define INFINITE_LOADER_LENGTH 8

InfiniteLoader::InfiniteLoader(const std::string& message)
	: _continue(true),
		_success(false),
		_message(message),
		_loader_thread(&InfiniteLoader::_show_loader, this)
{}

void InfiniteLoader::finish(bool success) {
	_continue = false;
	_success = success;
	_loader_thread.join();
}

void InfiniteLoader::_show_loader() {
	bool reverse = true;

	for (size_t i = 0; _continue; i++) {
		size_t pos = i % INFINITE_LOADER_LENGTH;

		if (pos == 0)
			reverse = !reverse;

		if (reverse)
			pos = INFINITE_LOADER_LENGTH - pos - 1;

		std::cout << _message << " \033[33m[";

		for (size_t j = 0; j < INFINITE_LOADER_LENGTH; j++)
			std::cout << (j == pos ? "●" : " ");

		std::cout << "]\033[m\r";
		std::cout.flush();
		usleep(100000);
	}

	std::cout << _message << " ";
	_print_loader_status(_success, INFINITE_LOADER_LENGTH + 3);
}
