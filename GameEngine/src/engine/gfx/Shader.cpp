#include "engine/gfx/Shader.h"
#include "engine/io/Resources.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <spdlog/spdlog.h>

Shader::Shader(const std::string& path) : Asset(path) {}

bool Shader::load() {
	std::string absolutePath = Resources::getFullPath(m_Path);
	ShaderProgramSource src = parseShader(absolutePath);
	createShader(src.vertexSrc, src.fragmentSrc);
	m_ActiveUniforms = getActiveUniforms();
	return true;
}

ShaderProgramSource Shader::parseShader(const std::string& path) {
	std::string shaderCode;
	/* Try/Catch block to catch parsing file errors */
	try {
		shaderCode = Resources::readFile(path);
	}
	catch (const std::invalid_argument& e) {
		spdlog::error("Error occured when parsing the file at {}.", path);
		throw e;
	}

	/* Get the code for the fragment and the vertex shader using markers "#shader <type>" */
	size_t vertexIndex = shaderCode.find("#shader vertex");
	size_t fragmentIndex = shaderCode.find("#shader fragment");

	if (vertexIndex == std::string::npos || fragmentIndex == std::string::npos) {
		spdlog::error("Shader at {} does not contain the required tags '#shader vertex' and '#shader fragment'.", path);
		throw std::invalid_argument("Shader does not contain the required markers for the vertex and fragment shader code.");
	}

	std::string vertex, fragment;

	if (vertexIndex < fragmentIndex) {
		vertex = shaderCode.substr(vertexIndex + 14, fragmentIndex - (vertexIndex + 14));
		fragment = shaderCode.substr(fragmentIndex + 16, shaderCode.length() - (fragmentIndex + 16));
	}
	else {
		vertex = shaderCode.substr(vertexIndex + 14, shaderCode.length() - (vertexIndex + 14));
		fragment = shaderCode.substr(fragmentIndex + 16, vertexIndex - (fragmentIndex + 16));
	}

	return { vertex, fragment };
}

bool Shader::hasUniform(const std::string& name) const {
	if (m_ActiveUniforms.empty()) {
		spdlog::warn("Shader uniforms have not been populated yet!");
		return false;
	}

	auto it = std::find_if(m_ActiveUniforms.begin(), m_ActiveUniforms.end(), [&](const ShaderUniform& item) {
		return item.name == name;
	});

	if (it == m_ActiveUniforms.end()) {
		spdlog::warn("Uniform {} not found in shader program.", name);
		return false;
	}

	return true;
}

void Shader::setUniform(const std::string& name, const UniformValue& value) {
	if (!hasUniform(name)) {
		spdlog::error("Uniform {} does not exist in shader program.", name);
		return;
	}

	std::optional<GLenum> type = getUniformType(name);

	if (type.has_value() == false) {
		spdlog::error("Could not retrieve type for uniform {}.", name);
		return;
	}

	bool matched = false;

	std::visit([&](auto&& val) {
		using T = std::decay_t<decltype(val)>;
		switch (type.value()) {
		case GL_FLOAT:
			if constexpr (std::is_same_v<T, float>) {
				setFloatUniform(name, val);
				matched = true;
			}
			break;
		case GL_FLOAT_VEC2:
			if constexpr (std::is_same_v<T, glm::vec2>) {
				setFloat2Uniforms(name, val);
				matched = true;
			}
			break;
		case GL_FLOAT_VEC3:
			if constexpr (std::is_same_v<T, glm::vec3>) {
				setFloat3Uniform(name, val);
				matched = true;
			}
			break;
		case GL_FLOAT_VEC4:
			if constexpr (std::is_same_v<T, glm::vec4>) {
				setFloat4Uniform(name, val);
				matched = true;
			}
			break;
		case GL_SAMPLER_2D:
			if constexpr (std::is_same_v<T, int>) {
				setSamplerUniform(name, val);
				matched = true;
			}
			break;
		case GL_FLOAT_MAT3:
			if constexpr (std::is_same_v<T, glm::mat3>) {
				setMat3Uniform(name, val, false);
				matched = true;
			}
			break;
		case GL_FLOAT_MAT4:
			if constexpr (std::is_same_v<T, glm::mat4>) {
				setMat4Uniform(name, val, false);
				matched = true;
			}
			break;
		default:
			spdlog::error("Unsupported uniform type for {}", name);
		}
		}, value);

	if (!matched) {
		spdlog::error("Type mismatch for uniform {}", name);
	}
}


std::optional<GLenum> Shader::getUniformType(const std::string& name) const
{
    auto it = std::find_if(m_ActiveUniforms.begin(), m_ActiveUniforms.end(), [&](const ShaderUniform& item) {
        return item.name == name;
    });

    if (it == m_ActiveUniforms.end()) {
        spdlog::warn("Uniform '{}' not found in shader program.", name);
        return std::nullopt;  // signify "not found"
    }

    return it->type;
}

std::vector<ShaderUniform> Shader::getActiveUniforms() const {
   GLint uniformCount;
   glGetProgramiv(this->m_ProgramId, GL_ACTIVE_UNIFORMS, &uniformCount);

   char name[256];
   GLsizei length;
   GLint size;
   GLenum type;

   std::vector<ShaderUniform> uniforms;

   for (GLint i = 0; i < uniformCount; ++i) {
       glGetActiveUniform(this->m_ProgramId, i, sizeof(name), &length, &size, &type, name);
       GLint location = glGetUniformLocation(this->m_ProgramId, name);
       uniforms.push_back({ name, type, size, location });
   }

   return uniforms;
}

void Shader::createShader(const std::string& vertexSrc, const std::string& fragmentSrc) {
	unsigned int vertexId = compileShader(GL_VERTEX_SHADER, vertexSrc); 
	unsigned int fragmentId = compileShader(GL_FRAGMENT_SHADER, fragmentSrc);

	this->m_ProgramId = glCreateProgram();
	glAttachShader(this->m_ProgramId, vertexId);
	glAttachShader(this->m_ProgramId, fragmentId);
	glLinkProgram(this->m_ProgramId);

	GLint status;
	glGetProgramiv(this->m_ProgramId, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		//Improve
		GLint infoLogLength;
		glGetProgramiv(this->m_ProgramId, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(this->m_ProgramId, infoLogLength, NULL, strInfoLog);

		//Temporary print that shall be replaced with logging
		spdlog::error("Linker failure: {}", strInfoLog);
		delete[] strInfoLog;
	}

	/* Detach the shaders from the program, this does not affect the program's linking status */
	glDetachShader(this->m_ProgramId, vertexId);
	glDetachShader(this->m_ProgramId, fragmentId);
}

int Shader::compileShader(const unsigned int type, const std::string& src) {
	unsigned int id = glCreateShader(type);
	const char* source = src.c_str();
	glShaderSource(id, 1, &source, NULL);
	glCompileShader(id);

	GLint status;
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		//Improve
		GLint infoLogLength;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(id, infoLogLength, NULL, strInfoLog);

		//Temporary print that shall be replaced with logging
		spdlog::error("Compile failure in shader:\n{}", strInfoLog);
		delete[] strInfoLog;
	}

	return id;
}

/** Uniforms **/

bool Shader::isValidUniform(const int location, const std::string& name) const {
	//Improve, add assert.
	if (location == -1) {
		spdlog::error("Uniform {} is invalid. Shader program id: {} \n", name.c_str(), this->m_ProgramId);
		return false;
	}

	return true;
}

void Shader::setFloat4Uniform(const std::string& name, const glm::vec4 vector) const {
	int location = glGetUniformLocation(this->m_ProgramId, name.c_str());
	if (isValidUniform(location, name))
		glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
}


void Shader::setFloat3Uniform(const std::string& name, const glm::vec3 vector) const {
	int location = glGetUniformLocation(this->m_ProgramId, name.c_str());
	if(isValidUniform(location, name))
		glUniform3f(location, vector.x, vector.y, vector.z);
}

void Shader::setFloat2Uniforms(const std::string& name, const glm::vec2 vector) const {
	int location = glGetUniformLocation(this->m_ProgramId, name.c_str());
	if (isValidUniform(location, name))
		glUniform2f(location, vector.x, vector.y);
}

void Shader::setFloatUniform(const std::string& name, const GLfloat& number) const {
	int location = glGetUniformLocation(this->m_ProgramId, name.c_str());
	if (isValidUniform(location, name))
		glUniform1f(location, number);
}

void Shader::setMat4Uniform(const std::string& name, const glm::mat4 matrix, const bool transpose) const {
	int location = glGetUniformLocation(this->m_ProgramId, name.c_str());
	if (isValidUniform(location, name))
		glUniformMatrix4fv(location, 1, transpose, glm::value_ptr(matrix[0]));
}

void Shader::setMat3Uniform(const std::string& name, const glm::mat3 matrix, const bool transpose) const {
	int location = glGetUniformLocation(this->m_ProgramId, name.c_str());
	if (isValidUniform(location, name))
		glUniformMatrix3fv(location, 1, transpose, glm::value_ptr(matrix[0]));
}

void Shader::setSamplerUniform(const std::string& name, int textureUnit) const {
	GLint location = glGetUniformLocation(this->m_ProgramId, name.c_str());
	if (location == -1) {
		spdlog::error("Uniform '{}' not found in shader!", name);
		return;
	}
	glUniform1i(location, textureUnit);
}
