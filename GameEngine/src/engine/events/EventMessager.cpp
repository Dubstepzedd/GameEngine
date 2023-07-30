#include "engine/events/EventMessager.h"

void EventMessager::setOnEvent(GLFWwindow* window, std::function<void(Event&)> func) {
	m_OnEvent = func;
	
	//Mouse related
	glfwSetMouseButtonCallback(window, &EventMessager::mouse_button_callback);
	glfwSetCursorPosCallback(window, &EventMessager::cursor_position_callback);
	glfwSetScrollCallback(window, &EventMessager::scroll_callback);

	//Keyboard related
	glfwSetKeyCallback(window, &EventMessager::key_callback);

	//Window related
	glfwSetFramebufferSizeCallback(window, &EventMessager::framebuffer_size_callback);
	glfwSetWindowSizeCallback(window, &EventMessager::window_resize_callback);
	glfwSetWindowFocusCallback(window, &EventMessager::window_focus_callback);
	glfwSetWindowPosCallback(window, &EventMessager::window_pos_callback);
	glfwSetWindowCloseCallback(window, &EventMessager::window_close_callback);
}

void EventMessager::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	FrameBufferChangedEvent e = FrameBufferChangedEvent(width, height);

	getInstance().m_OnEvent((Event&)e);
}

/* Mouse listener */
void EventMessager::cursor_position_callback(GLFWwindow* window, double xPos, double yPos) {
	MouseMovedEvent e = MouseMovedEvent(xPos, yPos);

	getInstance().m_OnEvent((Event&)e);
}

void EventMessager::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {

	if (action == GLFW_PRESS) {
		MouseButtonPressedEvent e = MouseButtonPressedEvent(button);
		getInstance().m_OnEvent((Event&)e);

	}
	else if (action == GLFW_RELEASE) {
		MouseButtonReleasedEvent e = MouseButtonReleasedEvent(button);
		getInstance().m_OnEvent((Event&)e);
	}
}

void EventMessager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	if (action == GLFW_PRESS) {
		KeyPressedEvent e = KeyPressedEvent(key, false);
		getInstance().m_OnEvent((Event&)e);
	}
	else if (action == GLFW_RELEASE) {
		KeyReleasedEvent e = KeyReleasedEvent(key);
		getInstance().m_OnEvent((Event&)e);
	}
	else if (action == GLFW_REPEAT) {
		KeyPressedEvent e = KeyPressedEvent(key, true);
		getInstance().m_OnEvent((Event&)e);
	}
}

//Does not support x scroll atm, but it is barely used anywhere.
void EventMessager::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	MouseScrolledEvent e = MouseScrolledEvent(yoffset);

	getInstance().m_OnEvent((Event&)e);
}

void EventMessager::window_resize_callback(GLFWwindow* window, int width, int height) {
	WindowResizeEvent e = WindowResizeEvent(width,height);

	getInstance().m_OnEvent((Event&)e);
}

void EventMessager::window_pos_callback(GLFWwindow* window, int xpos, int ypos) {
	WindowMovedEvent e = WindowMovedEvent(xpos, ypos);

	getInstance().m_OnEvent((Event&)e);
}

void EventMessager::window_close_callback(GLFWwindow* window) {
	WindowCloseEvent e = WindowCloseEvent();

	getInstance().m_OnEvent((Event&)e);
}

void EventMessager::window_focus_callback(GLFWwindow* window, int focused) {
	WindowFocusEvent e = WindowFocusEvent(focused);

	getInstance().m_OnEvent((Event&)e);
}