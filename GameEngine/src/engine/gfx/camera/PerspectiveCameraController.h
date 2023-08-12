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
class  PerspectiveCameraController {

public:
	PerspectiveCameraController(const glm::vec3 pos, const Shader& shader) : m_Camera(pos), m_Shader(shader) {
		m_Camera.updateProj(shader); 
	}

	virtual void onUpdate(const TimeStep dt);
	virtual void onEvent(Event& event);
	virtual bool onMouseMovedEvent(MouseMovedEvent& event);
private:
	float m_Zoom = 1.0f;
	float m_Yaw = 0, m_Pitch = 0;
	float m_LastY = 320, m_LastX = 320;
	PerspectiveCamera m_Camera;
	const Shader& m_Shader;
	

};