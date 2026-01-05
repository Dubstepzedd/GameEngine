#pragma once
#include <string>
#include "engine/io/AssetHandle.h"
#include <unordered_map>
#include <memory>
#include "engine/gfx/Texture.h"
#include "engine/gfx/Shader.h"
#include "spdlog/spdlog.h"
#include <concepts>

template<typename T>
concept DerivedFromAsset = std::derived_from<T, Asset>;

class AssetManager {

public:

    template<DerivedFromAsset T>
    std::shared_ptr<T> getAsset(const AssetHandle& handle) {
        
        if (!handle.isValid()) {
			spdlog::error("Invalid AssetHandle provided to AssetManager::getAsset");
            return nullptr;
        }

        auto it = assetStorage.find(handle.id);
        if (it != assetStorage.end()) {
            return std::static_pointer_cast<T>(it->second);
        }

        // Asset not found
        return nullptr;
    }

    template<DerivedFromAsset T>
    AssetHandle loadAsset(const std::string& path) {
        AssetHandle handle;
        std::shared_ptr<T> asset = std::make_shared<T>(path);
        bool success = asset->load();
        if (!success) {
            spdlog::error("Failed to load asset at path: {}", path);
            return handle; // invalid handle
        }
        handle.id = nextAssetId++;
        handle.type = asset->getType();
        assetStorage[handle.id] = asset;

        return handle;
    }

	
private:
    std::unordered_map<int, std::shared_ptr<Asset>> assetStorage;
	int nextAssetId = 0;
};