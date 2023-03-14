#include <iostream>
#include <string>
#include <unistd.h>
#include <thread>
#include <array>

#include "loader.hpp"

static inline std::string _loader_finish_status(bool success) {
	return success ? "\033[34m[Finished]\033[m" : "\033[31m[Failed]\033[m  ";
}

#define BAR_LOADER_LENGTH 20

BarLoader::BarLoader(const std::string& message)
	: _message(message),
		_previous_percentage(0)
{
	std::cout << _message << std::endl << "[";
	for (size_t i = 0; i < BAR_LOADER_LENGTH; i++) {
		std::cout << "░";
	}
	std::cout << "]\r\033[33m";
}

void BarLoader::update_loader(size_t percentage) {
	if (_previous_percentage < percentage) {
		std::cout << "[";
		size_t filled_length = (percentage * BAR_LOADER_LENGTH)/100;
		for (size_t i = 0; i < filled_length; i++) {
			std::cout << "█";
		}
		for (size_t i = filled_length; i < BAR_LOADER_LENGTH; i++) {
			std::cout << "░";
		}
		std::cout << "] " << percentage << "%\r";
		std::cout.flush();
		_previous_percentage = percentage;
	}
}

void BarLoader::finish(bool success) {
	for (size_t i = 0; i < BAR_LOADER_LENGTH + 7; i++) {
		std::cout << " ";
	}
	std::cout << "\033[m\033[1A\r" << _message << " " << _loader_finish_status(success) << std::endl;
}

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
		if (pos == 0) {
			reverse = !reverse;
		}
		if (reverse) {
			pos = INFINITE_LOADER_LENGTH - pos - 1;
		}
		std::cout << _message << " \033[33m[";
		for (size_t j = 0; j < INFINITE_LOADER_LENGTH; j++) {
			std::cout << (j == pos ? "●" : " ");
		}
		std::cout << "]\033[m\r";
		std::cout.flush();
		usleep(100000);
	}
	std::cout << _message << " " << _loader_finish_status(_success) << std::endl;
}
