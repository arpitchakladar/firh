#include <thread>
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

class InfiniteLoader {
public:
	InfiniteLoader(const std::string& message);
	void finish(bool success);

private:
	std::thread _loader_thread;
	std::string _message;
	bool _continue;
	bool _success;
	void _show_loader();
};
