#include "engine/events/Input.h"
#include <iostream>

/* Keyboard callback */
void Input::onEvent(Event& e) {
	if (e.getCategory() == EventCategory::Keyboard) {
		KeyEvent& keyEvent = (KeyEvent&)e;

		if (keyEvent.getEventType() == KeyPressedEvent::getStaticType()) {
			m_Keys[keyEvent.getKeyCode()] = true;
		}
		else if (keyEvent.getEventType() == KeyReleasedEvent::getStaticType()) {
			m_Keys[keyEvent.getKeyCode()] = false;
		}
	}
	else if (e.getCategory() == EventCategory::MouseInput) {
		MouseButtonEvent& buttonEvent = (MouseButtonEvent&)e;
		if (buttonEvent.getEventType() == MouseButtonPressedEvent::getStaticType()) {
			m_Buttons[buttonEvent.getMouseButton()] = true;
		}
		else if (buttonEvent.getEventType() == MouseButtonReleasedEvent::getStaticType()) {
			m_Buttons[buttonEvent.getMouseButton()] = false;
		}
	}
}

bool Input::isKeyPressed(int key) const {
	return m_Keys[key];
}

bool Input::isButtonPressed(int button) const {
	return m_Buttons[button];
}