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

void Renderer::bindShader(Shader* shader) {
	m_Shader = shader;
	glUseProgram(m_Shader->getProgramId());
}

void Renderer::unbindShader() {
	m_Shader = nullptr;
	glUseProgram(0);
}

void Renderer::onEvent(Event& event) {
	if (event.getEventType() == EventType::WindowResize) {
		FrameBufferChangedEvent& ev = (FrameBufferChangedEvent&)event;
		glViewport(0, 0, ev.getWidth(), ev.getHeight());
	}
}