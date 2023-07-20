#include "engine/gfx/Shader.h"
#include "engine/io/Resources.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <spdlog/spdlog.h>

Shader::Shader(const std::string& path) {
	ShaderProgramSource src = parseShader(path);
	createShader(src.vertexSrc, src.fragmentSrc);
}

ShaderProgramSource Shader::parseShader(const std::string& path) {
	std::string shaderCode;
	/* Try/Catch block to catch eventual parsing file errors */
	try {
		shaderCode = Resources::readFile(path);
	}
	catch (const std::invalid_argument& e) {
		//Improve
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
		spdlog::error("Compile failure in vertex shader:\n{}", strInfoLog);
		delete[] strInfoLog;
	}

	return id;
}
void Shader::unbind() const{
	glUseProgram(0);
}

void Shader::bind() const {
	glUseProgram(this->m_ProgramId);
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
