#include <string>

#pragma once

class BarLoader {
public:
	BarLoader(const std::string& message);
	void update_loader(size_t percentage);
	void finish(bool success);

private:
	std::string _message;
	size_t _previous_percentage;
};
