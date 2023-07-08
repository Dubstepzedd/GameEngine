#include "shader.h"
#include "resources.h"
#include <iostream>

Shader::Shader(const std::string path) {
	std::cout << Resources::readFile(path) << std::endl; //Temporary of course.
}


void Shader::create() {

}