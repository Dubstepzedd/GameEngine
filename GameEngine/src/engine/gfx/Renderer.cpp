#include "engine/gfx/Renderer.h"

void Renderer::draw(const VertexArray& vArr, const IndexBuffer& iBuff, Material& material, const glm::mat4& view, const glm::mat4& proj) {
	vArr.bind();
	iBuff.bind();

	material.setUniform("uView", view);
	material.setUniform("uProj", proj);
	material.bind();
	glDrawElements(GL_TRIANGLES, iBuff.getCount(), GL_UNSIGNED_INT, (const void*)0); 
	iBuff.unbind();
	vArr.unbind();
}

void Renderer::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::onEvent(Event& event) {
	if (event.getEventType() == EventType::WindowResize) {
		FrameBufferChangedEvent& ev = (FrameBufferChangedEvent&)event;
		glViewport(0, 0, ev.getWidth(), ev.getHeight());
	}
}