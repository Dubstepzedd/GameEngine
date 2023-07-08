#include "resources.h"
#include <fstream>      // std::ifstream
#include <iostream>
std::string Resources::readFile(const std::string path) {
	std::string content;

	std::ifstream reader(path, std::ifstream::in);

	if (reader.fail()) {
		std::cout << "File did not exist" << std::endl; // Temporary.
	}

	while(std::getline(reader, content)){}

	reader.close();

	return content;
}