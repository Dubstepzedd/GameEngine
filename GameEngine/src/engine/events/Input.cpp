#include "engine/events/Input.h"

/* Keyboard callback */
void Input::onEvent(KeyEvent& e) {
	if (e.getEventType() == KeyPressedEvent::getStaticType()) {
		keys[e.getKeyCode()] = true;
	}
	else if (e.getEventType() == KeyReleasedEvent::getStaticType()) {
		keys[e.getKeyCode()] = false;
	}
}

/* Helpers, can be getters/setters */
bool Input::isKeyPressed(int key) {
	return keys[key];
}
