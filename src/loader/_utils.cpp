#include <string>
#include <iostream>

#include "loader/_utils.hpp"

void _print_loader_status(bool success, size_t truncate) {
	std::string status_message = success ? "\033[34m[Finished]" : "\033[31m[Failed]";
	std::cout << status_message << "\033[m";

	for (size_t i = status_message.size() - 5; i < truncate; i++)
		std::cout << " ";

	std::cout << std::endl;
}
