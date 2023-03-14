#include <thread>
#include <string>

#pragma once

class InfiniteLoader {
public:
	InfiniteLoader(std::string message);
	void finish(bool success);

private:
	std::thread _loader_thread;
	std::string _message;
	bool _continue;
	bool _success;
	void _show_loader();
};
