#include <string>
#include <iostream>

#include "loader/utils.hpp"

void _print_loader_status(bool success, size_t truncate) {
	std::string status_message = success ? "\033[34m[Finished]" : "\033[32m[Failed]";
	std::cout << status_message;

	for (size_t i = status_message.size() - 5; i < truncate; i++)
		std::cout << " ";

	std::cout << "\033[m" << std::endl;
}
