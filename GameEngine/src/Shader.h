#pragma once
#include <string>
#include <GL/glew.h>

class Shader {
	
public:
	Shader() {};
	~Shader() {
		glDeleteProgram(programId);
	}
	void create(const std::string path);
	void enable() const;
	void disable() const;
private:
	GLuint vertexId = 0, fragmentId = 0;
	GLuint programId = 0;
};

/* Static methods the ShaderData struct. */



