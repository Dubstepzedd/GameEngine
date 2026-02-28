#pragma once
#include "engine/gfx/Shader.h"
#include <unordered_map>
#include <memory>
#include "engine/io/AssetManager.h"
#include "spdlog/spdlog.h"

class Material {
public:
    Material(AssetHandle shaderHandle, std::shared_ptr<AssetManager> manager) {
        if (shaderHandle.type != AssetType::Shader) {
            throw std::invalid_argument("Invalid AssetHandle type for Material constructor");
        }

        m_Manager = manager;
        m_Shader = m_Manager->getAsset<Shader>(shaderHandle);

    }

    void bind() const {

        glUseProgram(m_Shader->getProgramId());
        std::vector<ShaderUniform> uniforms = m_Shader->getActiveUniforms();

        // Check for uniforms declared in shader but not set in m_Uniforms or m_Textures
        for (const auto& uniform : uniforms) {
            const std::string& name = uniform.name;

            // Check if uniform is missing from both maps
            bool isSet = (m_Uniforms.find(name) != m_Uniforms.end()) || (m_Textures.find(name) != m_Textures.end());

            if (!isSet) {
                spdlog::warn("Uniform '{}' declared in shader but not set in Material", name);
            }
        }

        // Bind regular uniforms
        for (const auto& [name, value] : m_Uniforms) {
            m_Shader->setUniform(name, value);
        }

        // Bind textures
        int textureUnit = 0;
        for (const auto& [name, handle] : m_Textures) {
            if (handle.type != AssetType::Texture) {
                spdlog::warn("Uniform '{}' has non-texture AssetHandle in m_TextureUniforms", name);
                continue;
            }

            std::shared_ptr<Texture> texture = m_Manager->getAsset<Texture>(handle);
            if (!texture) {
                spdlog::error("Failed to load texture for uniform '{}'", name);
                continue;
            }

            texture->bind(textureUnit);
            m_Shader->setSamplerUniform(name, textureUnit);
            textureUnit++;
        }
    }

	void unbind() const {
		glUseProgram(0);
	}

    BufferLayout getLayout() const {
        return m_Shader->getLayout();
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

protected:
	std::shared_ptr<AssetManager> m_Manager;
    std::shared_ptr<Shader> m_Shader;
	std::unordered_map<std::string, UniformValue> m_Uniforms;
	std::unordered_map<std::string, AssetHandle> m_Textures;
};
