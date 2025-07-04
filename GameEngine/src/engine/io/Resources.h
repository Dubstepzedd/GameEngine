#pragma once

#include <string>

class Resources {

public:
	static std::string readFile(const std::string path);
	static std::string getFullPath(const std::string& relativePath);
};

