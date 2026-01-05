#include "engine/io/geometry/MeshLoader.h"
#include <sstream>
#include <iostream>
#include <vector>

std::map<const std::string, ObjElementType> MeshLoader::valueToType = {
	{"v", ObjElementType::POSITION},
	{"vt", ObjElementType::TEXCOORD},
	{"vn", ObjElementType::NORMAL},
	{"f", ObjElementType::FACE}
};

// istringstream is the standard for all the parse methods. It is perfect for the .obj use case as it allows us to extract until whitespace is reached. 

glm::vec3 MeshLoader::parsePos(const std::string& data) {
	std::istringstream iss(data);
	float x, y, z;
	
	if (iss >> x >> y >> z) {
		return glm::vec3(x, y, z);
	}
	else {
		throw std::invalid_argument("Failed to parse position data from .obj file: " + data);
	}
}

glm::vec2 MeshLoader::parseTexCoord(const std::string& data) {
	std::istringstream iss(data);
	float x, y;

	if (iss >> x >> y) {
		return glm::vec2(x, y);
	}
	else {
		throw std::invalid_argument("Failed to parse texture data from .obj file: " + data);
	}
}

glm::vec3 MeshLoader::parseNormal(const std::string& data) {
	std::istringstream iss(data);
	float x, y, z;

	if (iss >> x >> y >> z) {
		return glm::vec3(x, y, z);
	}
	else {
		throw std::invalid_argument("Failed to parse normal data from .obj file: " + data);
	}
}

ObjFace MeshLoader::parseFace(const std::string& data) {
	ObjFace face;
	std::istringstream iss(data);
	std::string segment;

	while (iss >> segment) {
		ObjIndex objIndex = ObjIndex();
		std::istringstream segmentStream(segment);
		std::string val;

		if (std::getline(segmentStream, val, '/')) {
			objIndex.posIndex = std::stoi(val) - 1;
		}

		if (std::getline(segmentStream, val, '/')) {
			if (!val.empty()) {
				objIndex.uvIndex = std::stoi(val) - 1;
			}

			if (std::getline(segmentStream, val, '/')) {
				if (!val.empty()) {
					objIndex.normIndex = std::stoi(val) - 1;
				}
			}
		}

		face.vertices.push_back(objIndex);
	}

	return face;
}

RawModelData MeshLoader::loadMesh(const std::string& path) {
	RawModelData modelData;
	std::ifstream reader(path, std::ifstream::in);

	if (reader.fail()) {
		throw std::invalid_argument("Path to .obj model is incorrect. No such file was found.");
	}

	std::string line;
	while (std::getline(reader, line)) {
		size_t spacePos = line.find(' ');

		if (spacePos == std::string::npos || line.empty()) {
			continue;
		}

		const std::string value = line.substr(0, spacePos);
		auto it = valueToType.find(value);

		if (it == valueToType.end()) {
			continue;
		}

		const ObjElementType type = it->second;
		const std::string data = line.substr(spacePos + 1);

		switch (type) {
		case ObjElementType::POSITION: {
			glm::vec3 pos = parsePos(data);
			modelData.positions.push_back(pos);
			break;
		}
		case ObjElementType::TEXCOORD: {
			glm::vec2 texCoord = parseTexCoord(data);
			modelData.texCoords.push_back(texCoord);
			break;
		}
		case ObjElementType::NORMAL: {
			glm::vec3 normal = parseNormal(data);
			modelData.normals.push_back(normal);
			break;
		}
		case ObjElementType::FACE: {
			ObjFace face = parseFace(data);
			modelData.faces.push_back(face);
			break;
		}
		default: {
			spdlog::error("Case missing for element type {}. ", value);
			break;
		}
		}
	}

	spdlog::info("File {} was read and loaded successfully.", path);
	reader.close();
	return modelData;
}