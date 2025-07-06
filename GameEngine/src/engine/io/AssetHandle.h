#include <string>
#pragma once
enum class AssetType {
	Unknown = 0,  // MUST be 0
	Texture = 1,
	Mesh = 2,
	Shader = 3,
};

struct AssetHandle {
    int id;
    AssetType type;

    AssetHandle(int id = -1, AssetType type = AssetType::Unknown)
        : id(id), type(type) {
    }

    bool isValid() const {
        return id >= 0 && type != AssetType::Unknown;
    }

    std::string toString() const {
        return "AssetHandle { id = " + std::to_string(id) + ", type = " + std::to_string(static_cast<int>(type)) + " }";
    }
};