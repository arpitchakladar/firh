#include <string>

#pragma once

class Logger {
public:
	static void job(std::string message);
	static void error(std::string message);
	static void separator();
};
