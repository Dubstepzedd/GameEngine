#include "engine/events/listener.h"

/* Keyboard callback */
void Listener::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	if (key == GLFW_KEY_UNKNOWN)
		return;

	if (action == GLFW_PRESS) {
		Listener::getInstance().keys[key] = true;
	}
	else if (action == GLFW_RELEASE) {
		Listener::getInstance().keys[key] = false;
	}
}


/* Helpers, can be getters/setters */
bool Listener::isKeyPressed(int key) {
	return keys[key];
}

bool Listener::isButtonPressed(int btn) {
	return buttons[btn];
}

glm::vec2 Listener::getMousePos() {
	return mPos;
}