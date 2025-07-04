#include "engine/gfx/camera/PerspectiveCamera.h"


void PerspectiveCamera::updateProj()  {
	m_Proj = glm::perspective(glm::radians(m_Fov), Window::getInstance().getAspectRatio(), m_Near, m_Far);
}

void PerspectiveCamera::updateView() {
	m_View = glm::lookAt(m_Pos, m_Pos + m_Front , m_Up);
}

void PerspectiveCamera::onEvent(Event& event) {
	if (event.getEventType() == EventType::FrameBufferChanged) {
		updateProj();
	}
}