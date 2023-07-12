#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <GL/glew.h>

struct ShaderData {
	GLuint vertexId, fragmentId;
	GLuint programId;
};

/* Static methods the ShaderData struct. */

ShaderData createShader(const std::string path);

#endif