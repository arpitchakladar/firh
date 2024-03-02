#include <string>
#include <iostream>

#include "logger.hpp"

void Logger::job(std::string message) {
	std::cout << "\033[36;1m" << message << "\033[m" << std::endl;
}

void Logger::error(std::string message) {
	std::cout << "\033[31;1m" << "[ERROR]" << "\033[m" << " " << message << std::endl;
}

void Logger::finish(std::string message, bool success) {
	std::string status_message = success ? "\033[34m[Finished]" : "\033[31m[Failed]";
	std::cout << status_message << "\033[m " << message << std::endl;
}

void Logger::skipping(std::string message) {
	std::cout << "\033[33m[Skipping]\033[m " << message << std::endl;
}

void Logger::separator() {
	std::cout << std::endl;
}
