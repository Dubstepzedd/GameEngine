#include "engine/gfx/Renderer.h"

void Renderer::draw(const Mesh& mesh, const glm::mat4& view, const glm::mat4& proj, AssetManager& manager) {
	mesh.bind();
	mesh.getMaterial()->setUniform("uView", view);
	mesh.getMaterial()->setUniform("uProj", proj);
	mesh.getMaterial()->bind(manager);

	glDrawElements(GL_TRIANGLES, mesh.getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);

	mesh.getMaterial()->unbind();
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