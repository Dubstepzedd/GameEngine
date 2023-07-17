#pragma once
#include "Buffer.h"
#include "Shader.h"

class Renderer {

public:
	static void draw(const VertexArray& vArr, const IndexBuffer& iBuff);
	static void clear();
	static void bindShader(const Shader& shader);
	static void unbindShader(const Shader& shader);

private:


};