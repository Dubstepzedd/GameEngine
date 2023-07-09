#ifndef SHADER_H
#define SHADER_H
#include <string>

struct ShaderData {
	int vertexId, fragmentId;
	int programId;
};

/* Static class that manipulates the ShaderData struct. */
class Shader {

public:
	static void create(const std::string path);

private:

};
#endif