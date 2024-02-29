#include <string>
#include <iostream>

#include "logger.hpp"

void Logger::job(std::string message) {
	std::cout << "\033[36;1m" << message << "\033[m" << std::endl;
}

void Logger::error(std::string message) {
	std::cout << "\033[31;1m" << "[ERROR]" << "\033[m" << " " << message << std::endl;
}

void Logger::separator() {
	std::cout << std::endl;
}
