#include <iostream>
#include <string>

#include "loader/bar.hpp"
#include "loader/utils.hpp"

#define BAR_LOADER_LENGTH 20

BarLoader::BarLoader(const std::string& message)
	: _message(message),
		_previous_percentage(0)
{
	std::cout << _message << " [";
	for (size_t i = 0; i < BAR_LOADER_LENGTH; i++) {
		std::cout << " ";
	}
	std::cout << "]\r";
}

void BarLoader::update_loader(size_t percentage) {
	if (_previous_percentage < percentage) {
		std::cout << _message << " \033[33m[";
		size_t filled_length = (percentage * BAR_LOADER_LENGTH)/100;
		for (size_t i = 0; i < filled_length; i++) {
			std::cout << "█";
		}
		for (size_t i = filled_length; i < BAR_LOADER_LENGTH; i++) {
			std::cout << " ";
		}
		std::cout << "] " << percentage << "%\033[m\r";
		std::cout.flush();
		_previous_percentage = percentage;
	}
}

void BarLoader::finish(bool success) {
	std::cout << _message << " ";
	_print_loader_status(success, BAR_LOADER_LENGTH + 9);
}
