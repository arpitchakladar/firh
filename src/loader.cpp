#include <iostream>
#include <string>
#include <unistd.h>
#include <thread>

#include "loader.hpp"

InfiniteLoader::InfiniteLoader(std::string message)
	: _continue(true),
		_message(message),
		_loader_thread(&InfiniteLoader::_show_loader, this)
{}

void InfiniteLoader::finish(bool success) {
	_continue = false;
	_success = success;
	_loader_thread.join();
}

static const std::string _loading_icons[] = { "/", "-", "\\" };

void InfiniteLoader::_show_loader() {
	for (size_t i = 0; _continue; i++) {
		std::cout << _message << " " << _loading_icons[i % 3] << "\r";
		usleep(500);
	}
	std::cout << _message << " " << (_success ? "[Finished]" : "[Failed]") << std::endl;
}
