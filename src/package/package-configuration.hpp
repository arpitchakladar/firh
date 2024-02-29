#include <string>
#include <vector>

#pragma once

class PackageConfiguration {
public:
	std::string url;
	std::string branch;
	std::vector<std::string> dependencies;
	std::string commit;
	static PackageConfiguration from_file(const std::string& path);
};
