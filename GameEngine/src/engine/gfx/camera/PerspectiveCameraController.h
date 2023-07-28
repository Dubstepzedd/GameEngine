#pragma once
#include "engine/gfx/camera/PerspectiveCamera.h"
#include <glm/glm.hpp>
#include "engine/helpers/TimeStep.h"

class PerspectiveCameraController {

public:
	PerspectiveCameraController(const glm::vec3 pos) : m_Camera(pos) {}
	void onUpdate(const TimeStep dt);
private:
	float m_Zoom = 1.0f;
	PerspectiveCamera m_Camera;
	

};