#include "engine/gfx/camera/PerspectiveCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include "engine/core/Window.h"


void PerspectiveCamera::updateProj(const Shader& shader)  {
	m_Proj = glm::perspective(glm::radians(m_Fov), Window::getInstance().getAspectRatio(), m_Near, m_Far);
	shader.setMat4Uniform(m_ProjName, m_Proj, false);
}

void PerspectiveCamera::updateView(const Shader& shader) {
	m_View = glm::lookAt(m_Pos, m_Pos + m_Front , m_Up);
	shader.setMat4Uniform(m_ViewName, m_View, false);
}

