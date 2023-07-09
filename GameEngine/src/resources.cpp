#include "resources.h"
#include <fstream>      // std::ifstream
#include <iostream>

std::string Resources::readFile(const std::string path) {
	//TODO Fix logging here.

	std::string content;

	std::ifstream reader(path, std::ifstream::in);

	if (reader.fail()) {
		throw std::invalid_argument("Path to file is incorrect. No file was found.");
	}

	std::string line;
	while(std::getline(reader, line)){
		content.append(line + '\n');
	}

	reader.close();

	return content;
}