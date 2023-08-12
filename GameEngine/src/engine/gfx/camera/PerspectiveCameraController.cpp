#include "engine/gfx/camera/PerspectiveCameraController.h"
#include <functional>
#include <iostream>
#include "engine/helpers/Core.h"
#include <spdlog/spdlog.h>
#include <math.h>

void PerspectiveCameraController::onUpdate(const TimeStep dt) {
	//Handles keyboard input
	const float cameraSpeed = 0.1f; // adjust accordingly
	if (Input::getInstance().isKeyPressed(Key::W))
		m_Camera.setPos(m_Camera.getPos() += cameraSpeed * m_Camera.getFront());
	if (Input::getInstance().isKeyPressed(Key::S))
		m_Camera.setPos(m_Camera.getPos() -= cameraSpeed * m_Camera.getFront());
	if (Input::getInstance().isKeyPressed(Key::A))
		m_Camera.setPos(m_Camera.getPos() - glm::normalize(glm::cross(m_Camera.getFront(), m_Camera.getUp())) * cameraSpeed);
	if (Input::getInstance().isKeyPressed(Key::D))
		m_Camera.setPos(m_Camera.getPos() + glm::normalize(glm::cross(m_Camera.getFront(), m_Camera.getUp())) * cameraSpeed);


	m_Camera.updateView(m_Shader);
}

void PerspectiveCameraController::onEvent(Event& event) {
	EventDispatcher dispatcher(event);
	auto func = ENGINE_FN_BIND_1(PerspectiveCameraController::onMouseMovedEvent);
	dispatcher.dispatch<MouseMovedEvent>(func);
}

bool PerspectiveCameraController::onMouseMovedEvent(MouseMovedEvent& event) {
	//This handles the pitch and yaw.
	if(m_LastX != 0 && m_LastY != 0) {
		float xOffset = event.getXPos() - m_LastX;
		float yOffset = event.getYPos() - m_LastY;

		m_Pitch += yOffset;
		m_Yaw += xOffset;

		float sensitivity = 0.05f;
		xOffset *= sensitivity;
		yOffset *= sensitivity;

	}

	m_LastX = event.getXPos();
	m_LastY = event.getYPos();

	glm::vec3 direction = glm::vec3();
	direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	direction.y = sin(glm::radians(-m_Pitch));
	direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));

	m_Camera.setFront(glm::normalize(direction));

	return true;
}