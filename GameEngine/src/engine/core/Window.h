#pragma once
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "engine/events/Event.h"
#include "engine/events/ApplicationEvent.h"
#include <functional>

class Window {

public:

	static Window& getInstance() {
		static Window window;

		return window;
	}

	Window(const Window&) = delete;
	void operator=(const Window&) = delete;

	int create(const std::string name, const int w, const int h,  bool vSync, bool isResizable);
	void makeContext();
	void destroy();
	void close();
	void swapBuffers();
	void setOnEvent(std::function<void(Event&)> func);

	void setSize(const int width, const int height);
	void setVSync(const bool vSync);
	void setFullscreen(const bool value);
	void setClearColor(const float r, const float g, const float b, const float a);
	void setAspectRatio(const int width, const int height);

	bool isFullscreen();
	bool isVSync();
	bool isRunning();
	float getAspectRatio();
	int getRefreshRate();
	int getResolutionY();
	int getResolutionX();
	glm::dvec2 getSize();
	
private:
	void setHints(const bool isResizable);

private:
	Window() = default;
	glm::ivec2 m_WSize{};
	glm::ivec2 m_Pos{};
	GLFWwindow* m_Window = nullptr;
	bool m_VSync = false;
	const  GLFWvidmode* m_VideoMode = nullptr;
	glm::vec4 m_ClearColor{};
	bool m_Fullscreen = false;
	float m_AspectRatio = 0;

};
