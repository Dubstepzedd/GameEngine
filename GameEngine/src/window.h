#pragma once

#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

struct Color {
	float r;
	float g;
	float b;
	float a;
};

class Window {

public:

	static Window& getInstance() {
		static Window window;

		return window;
	}

	Window(const Window&) = delete;
	void operator=(const Window&) = delete;
	int start(const std::string name, const int w, const int h,  bool vSync, bool isResizable);
	void update();
	void setSize(const int width, const int height);
	bool isRunning();
	void setClearColor(const float r, const float g, const float b, const float a);
	glm::dvec2 getSize();
	void makeContext();
	void destroy();
	void setVSync(const bool vSync);
	int getRefreshRate();
	int getResolutionY();
	int getResolutionX();
	void setFullscreen(const bool value);
	bool isFullscreen();
	bool isVSync();
	void close();

	
private:
	Window() {};
	glm::ivec2 wSize{};
	glm::ivec2 pos{};
	GLFWwindow* window = nullptr;
	bool vSync = false;
	const  GLFWvidmode* videoMode = nullptr;
	Color clearColor{};
	bool fullscreen = false;

};

