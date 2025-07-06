#pragma once
#include <concepts>
#include <string>
#include "engine/io/AssetHandle.h"

class Asset {
public:
    Asset(const std::string& path) : m_Path(path) {}
    virtual ~Asset() = default;

	virtual AssetType getType() const = 0;
    virtual bool load() = 0;

protected:
    std::string m_Path;
};
