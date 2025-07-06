#pragma once
#include "engine/gfx/Shader.h"
#include <unordered_map>
#include <memory>
#include "engine/io/AssetManager.h"
#include "spdlog/spdlog.h"

class Material {
public:
    void bind(AssetManager& manager) const {
        std::shared_ptr<Shader> shader = manager.getAsset<Shader>(m_Handle);
        if (!shader) {
            spdlog::error("Shader not found or invalid handle in Material::bind");
            return;
        }

        glUseProgram(shader->getProgramId());

        // Bind regular uniforms
        for (const auto& [name, value] : m_Uniforms) {
            shader->setUniform(name, value); // uses your Shader::setUniform(...)
        }

        // Bind textures
        int textureUnit = 0; // Texture unit counter
        for (const auto& [name, handle] : m_Textures) {
            if (handle.type != AssetType::Texture) {
                spdlog::warn("Uniform '{}' has non-texture AssetHandle in m_TextureUniforms", name);
                continue;
            }

            std::shared_ptr<Texture> texture = manager.getAsset<Texture>(handle);
            if (!texture) {
                spdlog::error("Failed to load texture for uniform '{}'", name);
                continue;
            }

            texture->bind(textureUnit);               // binds texture to GL_TEXTURE0 + textureUnit
            shader->setSamplerUniform(name, textureUnit);    // pass the unit as sampler2D uniform
            textureUnit++;
        }
    }

	void unbind() const {
		glUseProgram(0);
	}

	void setTexture(const std::string& name, const AssetHandle& textureHandle) {
		if (textureHandle.type != AssetType::Texture) {
			spdlog::error("Material can only set textures with Texture asset handles");
			return;
		}
		m_Textures[name] = textureHandle;
	}

	void setUniform(const std::string& name, const UniformValue& value) {
		m_Uniforms[name] = value;
	}

	Material(AssetHandle shaderHandle)
		: m_Handle(shaderHandle) {
		if (shaderHandle.type != AssetType::Shader) {
			spdlog::error("Material must be initialized with a Shader asset handle");
			m_Handle = AssetHandle(); // Invalid handle
        }
	}

protected:
	AssetHandle m_Handle;
	std::unordered_map<std::string, UniformValue> m_Uniforms;
	std::unordered_map<std::string, AssetHandle> m_Textures;
};
