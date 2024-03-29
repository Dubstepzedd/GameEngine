#include "engine/gfx/Renderer.h"

void Renderer::draw(const VertexArray& vArr, const IndexBuffer& iBuff) {
	vArr.bind();
	iBuff.bind();
	glDrawElements(GL_TRIANGLES, iBuff.getCount(), GL_UNSIGNED_INT, (const void*)0); 
	iBuff.unbind();
	vArr.unbind();
}

void Renderer::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::bindShader(const Shader& shader) {
	shader.bind();
}

void Renderer::unbindShader(const Shader& shader) {
	shader.unbind();
}