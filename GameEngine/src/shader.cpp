#include "shader.h"
#include "resources.h"
#include <iostream>

void Shader::create(const std::string path) {
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

	/* Create the actual Shader and put it in a Shaderthis struct. */
	//Vertex Shader
	this->vertexId = glCreateShader(GL_VERTEX_SHADER);
	const char* src = vertex.c_str();
	glShaderSource(this->vertexId, 1,&src ,NULL);
	glCompileShader(this->vertexId);

	GLint status;
	glGetShaderiv(this->vertexId, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetShaderiv(this->vertexId, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(this->vertexId, infoLogLength, NULL, strInfoLog);

		//Temporary print that shall be replaced with logging
		fprintf(stderr, "Compile failure in vertex shader:\n%s\n", strInfoLog);
		delete[] strInfoLog;
	}

	//Fragment Shader
	this->fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
	src = fragment.c_str();
	glShaderSource(this->fragmentId, 1, &src, NULL);
	glCompileShader(this->fragmentId);

	glGetShaderiv(this->fragmentId, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetShaderiv(this->fragmentId, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(this->fragmentId, infoLogLength, NULL, strInfoLog);
		//Temporary print that shall be replaced with logging
		fprintf(stderr, "Compile failure in fragment shader:\n%s\n", strInfoLog);
		delete[] strInfoLog;
	}
	

	this->programId = glCreateProgram();
	glAttachShader(this->programId, this->vertexId);
	glAttachShader(this->programId, this->fragmentId);
	glLinkProgram(this->programId);


	glGetProgramiv(this->programId, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(this->programId, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(this->programId, infoLogLength, NULL, strInfoLog);
		//Temporary print that shall be replaced with logging
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}

	/* Detach the shaders from the program, this does not affect the program's linking status */
	glDetachShader(this->programId, this->vertexId);
	glDetachShader(this->programId, this->fragmentId);

}


void Shader::disable() {
	glUseProgram(0);
}

void Shader::enable() {
	glUseProgram(this->programId);
}

//TODO Add uniforms