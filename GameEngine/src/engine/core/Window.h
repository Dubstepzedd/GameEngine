#pragma once

#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Window {

public:

	static Window& getInstance() {
		static Window window;

		return window;
	}

	Window(const Window&) = delete;
	void operator=(const Window&) = delete;

	int start(const std::string name, const int w, const int h,  bool vSync, bool isResizable);
	void makeContext();
	void destroy();
	void close();
	void swapBuffers();

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
	Window() {};
	glm::ivec2 m_WSize{};
	glm::ivec2 m_Pos{};
	GLFWwindow* m_Window = nullptr;
	bool m_VSync = false;
	const  GLFWvidmode* m_VideoMode = nullptr;
	glm::vec4 m_ClearColor{};
	bool m_Fullscreen = false;
	float m_AspectRatio = 0;

	void setHints(const bool isResizable);
	void setCallbacks();
	static void onBufferUpdate(GLFWwindow* window, int width, int height) {
		Window::getInstance().setAspectRatio(width, height);
		glViewport(0, 0, width, height);
	}

};

