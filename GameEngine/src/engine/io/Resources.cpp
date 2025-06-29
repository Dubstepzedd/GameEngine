#pragma once
#include "engine/io/Resources.h"
#include <fstream>      // std::ifstream
#include <iostream>
#include <spdlog/spdlog.h>
#include <filesystem>

std::string Resources::readFile(const std::string path) {
	std::string content;

	std::ifstream reader(path, std::ifstream::in);

	if (reader.fail()) {
		throw std::invalid_argument("Path to file is incorrect. No file was found.");
	}

	std::string line;
	while(std::getline(reader, line)){
		content.append(line + '\n');
	}

	spdlog::info("File {} was read successfully.", path);
	reader.close();

	return content;
}

std::string Resources::getRelativePath(const std::string& relativePath) {
	std::filesystem::path assetRoot = std::filesystem::current_path();
	std::filesystem::path fullPath = assetRoot / relativePath;
	return fullPath.string(); // returns full absolute path as string
}