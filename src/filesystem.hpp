#include <string>

#pragma once

void remove_directory(const std::string& path);
void create_directory(const std::string& path);
std::fstream open_file(const std::string& path);
void create_file(const std::string& path);
