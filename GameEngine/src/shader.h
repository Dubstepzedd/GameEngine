#pragma once
#include <string>
#include <GL/glew.h>

class Shader {
	
public:
	Shader() {};
	void create(const std::string path);
	void enable();
	void disable();
private:
	GLuint vertexId = 0, fragmentId = 0;
	GLuint programId = 0;
};

/* Static methods the ShaderData struct. */



