#pragma once


#include "engine/gfx/camera/Camera.h"
class  PerspectiveCamera : public Camera {

public:
	PerspectiveCamera(const glm::vec3& pos, const float fov = 45.0f, const float nearPlane = 1.0f , const float farPlane = 100.0f) : Camera(pos), m_Fov(fov), m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_Up(glm::vec3(0.0f, 1.0f, 0.0f)) {
		m_Near = nearPlane;
		m_Far = farPlane;
	};

	void updateProj(const Shader& shader);

	void updateView(const Shader& shader);
	glm::vec3 getFront() {
		return m_Front;
	}

	glm::vec3 getUp() {
		return m_Up;
	}

	void setFront(glm::vec3& front) { m_Front = front; }
	void setUp(glm::vec3& up) { m_Up = up; }

private:
	float m_Fov;
	float m_Near;
	float m_Far;
	glm::vec3 m_Front, m_Up;
};