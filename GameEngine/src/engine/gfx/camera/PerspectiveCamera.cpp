#include "engine/gfx/camera/PerspectiveCamera.h"


void PerspectiveCamera::updateProj()  {

	if (Renderer::getInstance().getBoundShader() == nullptr) {
		ENGINE_ASSERT("No bound shader.");
		spdlog::error("No bound shader, can't update projection matrix.");
	}
	m_Proj = glm::perspective(glm::radians(m_Fov), Window::getInstance().getAspectRatio(), m_Near, m_Far);
	Renderer::getInstance().getBoundShader()->setMat4Uniform(m_ProjName, m_Proj, false);
}

void PerspectiveCamera::updateView() {
	if (Renderer::getInstance().getBoundShader() == nullptr) {
		ENGINE_ASSERT("No bound shader.");
		spdlog::error("No bound shader, can't update view matrix.");
	}

	m_View = glm::lookAt(m_Pos, m_Pos + m_Front , m_Up);
	Renderer::getInstance().getBoundShader()->setMat4Uniform(m_ViewName, m_View, false);
}

void PerspectiveCamera::onEvent(Event& event) {
	if (event.getEventType() == EventType::FrameBufferChanged) {
		updateProj();
	}
}