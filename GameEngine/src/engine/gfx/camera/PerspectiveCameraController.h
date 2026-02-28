#pragma once

#include "engine/gfx/camera/PerspectiveCamera.h"
#include <glm/glm.hpp>
#include "engine/helpers/TimeStep.h"
#include "engine/events/Event.h"
#include "engine/events/MouseEvent.h"
#include "engine/events/Input.h"
#include "engine/events/KeyCode.h"
#include "engine/gfx/Shader.h"
#include "engine/helpers/Core.h"

/*
This class is a standard PerspectiveCameraController that can be used right away.
If you need something changed, you'll need to override this class. 
A note: In the future, keybinds and properties should be easy to change, but key features will still need to be implemented if needed.
*/

class PerspectiveCameraController {

public:
	PerspectiveCameraController(const glm::vec3 pos) : m_Camera(pos) {
		m_Camera.updateProj(); 
	}

	glm::mat4 getViewMatrix() const {
		return m_Camera.getViewMatrix();
	}

	glm::mat4 getProjectionMatrix() const {
		return m_Camera.getProjectionMatrix();
	}

	virtual void onUpdate(const TimeStep dt);
	virtual void onEvent(Event& event);
	virtual bool onMouseMovedEvent(MouseMovedEvent& event);
private:
	float m_Zoom = 1.0f;
	float m_Yaw = 0, m_Pitch = 0;
	float m_LastY = 320, m_LastX = 320;
	float m_MouseSensitivity = 0.4f, m_Speed = 0.1f;
	PerspectiveCamera m_Camera;
	
};