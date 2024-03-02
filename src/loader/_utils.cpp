#include <iostream>

#include "loader/_utils.hpp"
#include "logger.hpp"

void _LoaderUtils::finish(size_t length, std::string message, bool success) {
	for (size_t i = 0; i < length; i++) {
		std::cout << " ";
	}
	std::cout << "\r";
	std::cout.flush();
	Logger::finish(message, success);
}
