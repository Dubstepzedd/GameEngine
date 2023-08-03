#pragma once
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>


struct  ShaderProgramSource {
	std::string vertexSrc;
	std::string fragmentSrc;
};

//TODO: Would be nice to parse two different .glsl files instead of just one. Some like it that way
class  Shader {
	
public:
	Shader(const std::string& path);

	~Shader() {
		glDeleteProgram(m_ProgramId);
	}

	void bind() const;
	void unbind() const;
	void setFloat4Uniform(const std::string& name, const glm::vec4 vector) const;
	void setFloat3Uniform(const std::string& name, const glm::vec3 vector) const;
	void setFloat2Uniforms(const std::string& name, const glm::vec2 vector) const;
	void setFloatUniform(const std::string& name, const GLfloat& number) const;
	void setMat4Uniform(const std::string& name, const glm::mat4 matrix, const bool transpose) const;
	void setMat3Uniform(const std::string& name, const glm::mat3 matrix, const bool transpose) const;
private:
	ShaderProgramSource parseShader(const std::string& path);
	int compileShader(const unsigned int type, const std::string& src);
	void createShader(const std::string& vertexSrc, const std::string& fragmentSrc);
	bool isValidUniform(const int location, const std::string& name) const;
	GLuint m_ProgramId = 0;
};




