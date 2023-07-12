#include "shader.h"
#include "resources.h"
#include <iostream>

ShaderData createShader(const std::string path) {
	std::string shaderCode;
	/* Try/Catch block to catch eventual parsing file errors */
	try {
		shaderCode = Resources::readFile(path);
	}
	catch (const std::invalid_argument& e) {
		//TODO Do shit if it fails
		fprintf(stderr, "Error occured when parsing .glsl file.");
		throw e;
	}

	/* Get the code for the fragment and the vertex shader using markers "#shader <type>" */
	size_t vertexIndex = shaderCode.find("#shader vertex");
	size_t fragmentIndex = shaderCode.find("#shader fragment");

	if (vertexIndex == std::string::npos || fragmentIndex == std::string::npos) {
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

	/* Create the actual Shader and put it in a ShaderData struct. */
	const char* src;
	ShaderData data;
	//Vertex Shader
	data.vertexId = glCreateShader(GL_VERTEX_SHADER);
	std::cout << "Test" << std::endl;
	src = vertex.c_str();
	glShaderSource(data.vertexId, 1,&src ,NULL);
	glCompileShader(data.vertexId);

	GLint status;
	glGetShaderiv(data.vertexId, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetShaderiv(data.vertexId, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(data.vertexId, infoLogLength, NULL, strInfoLog);

		//Temporary print that shall be replaced with logging
		fprintf(stderr, "Compile failure in vertex shader:\n%s\n", strInfoLog);
		delete[] strInfoLog;
	}

	//Fragment Shader
	data.fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
	src = fragment.c_str();
	glShaderSource(data.fragmentId, 1, &src, NULL);
	glCompileShader(data.fragmentId);

	glGetShaderiv(data.fragmentId, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetShaderiv(data.fragmentId, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(data.fragmentId, infoLogLength, NULL, strInfoLog);
		//Temporary print that shall be replaced with logging
		fprintf(stderr, "Compile failure in fragment shader:\n%s\n", strInfoLog);
		delete[] strInfoLog;
	}

	data.programId = glCreateProgram();
	glAttachShader(data.programId, data.vertexId);
	glAttachShader(data.programId, data.fragmentId);
	glLinkProgram(data.programId);

	glGetProgramiv(data.programId, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(data.programId, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(data.programId, infoLogLength, NULL, strInfoLog);
		//Temporary print that shall be replaced with logging
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}

	/* Detach the shaders from the program, this does not affect the program's linking status */
	glDetachShader(data.programId, data.vertexId);
	glDetachShader(data.programId, data.fragmentId);
	
	return data;
}