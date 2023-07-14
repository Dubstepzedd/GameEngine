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
	GLuint vertexId, fragmentId;
	GLuint programId;
};

/* Static methods the ShaderData struct. */



