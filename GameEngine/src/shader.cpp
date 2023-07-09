#include "shader.h"
#include "resources.h"
#include <iostream>


void Shader::create(const std::string path) {
	std::string shaderCode;
	try {
		shaderCode = Resources::readFile(path);
	}
	catch (const std::invalid_argument& e) {
		//TODO Do shit if it fails
		return;
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
	



}