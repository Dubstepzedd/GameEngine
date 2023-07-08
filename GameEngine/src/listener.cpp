#include "listener.h"

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

/* Mouse listener */
void Listener::cursor_position_callback(GLFWwindow* window, double xPos, double yPos) {
	Listener::getInstance().mPos.x = (float)xPos;
	Listener::getInstance().mPos.y = (float)yPos;
}

void Listener::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {

	if (action == GLFW_PRESS) {
		Listener::getInstance().buttons[button] = true;
	}
	else if (action == GLFW_RELEASE) {
		Listener::getInstance().buttons[button] = false;
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