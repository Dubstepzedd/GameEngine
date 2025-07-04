#pragma once
#include "engine/gfx/Shader.h"
#include <unordered_map>
#include <memory>

class Material {
public:
	void bind() const {
		glUseProgram(m_Shader->getProgramId());

		for (const auto& [name, value] : m_Uniforms) {
			std::visit([&](auto&& val) {
				m_Shader->setUniform(name, val); // This is overloaded
				}, value);
		}
	}

	void unbind() const {
		glUseProgram(0);
	}

	void setUniform(const std::string& name, const UniformValue& value) {
		m_Uniforms[name] = value;
	}

	Material(std::shared_ptr<Shader> shader)
		: m_Shader(shader) {
	}

protected:
	std::shared_ptr<Shader> m_Shader;
	std::unordered_map<std::string, UniformValue> m_Uniforms;
};
