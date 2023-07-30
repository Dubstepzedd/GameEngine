#pragma once
#include "engine/events/Event.h"
#include "engine/events/ApplicationEvent.h"
#include "engine/events/MouseEvent.h"
#include "engine/events/KeyEvent.h"
#include <GLFW/glfw3.h>
#include <functional>

class EventMessager {

public:
	static EventMessager& getInstance() {
		static EventMessager e;

		return e;
	}

	EventMessager(const EventMessager&) = delete;
	void operator=(const EventMessager&) = delete;

	void setOnEvent(GLFWwindow* window, std::function<void(Event&)> func);
private:
	EventMessager() = default;
	std::function<void(Event&)> m_OnEvent;

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void cursor_position_callback(GLFWwindow* window, double xPos, double yPos);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void window_resize_callback(GLFWwindow* window, int width, int height);
	static void window_pos_callback(GLFWwindow* window, int xpos, int ypos);
	static void window_close_callback(GLFWwindow* window);
	static void window_focus_callback(GLFWwindow* window, int focused);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};