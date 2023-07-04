#ifndef WINDOW_H
#define WINDOW_H

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

	Window(const std::string name, const int width, const int height);

	int start(const bool vSync, const bool isResizable);
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

	
private:
	glm::ivec2 wSize{};
	glm::ivec2 pos{};
	std::string name;
	GLFWwindow* window;
	bool vSync;
	const  GLFWvidmode* videoMode;
	Color clearColor;
	bool fullscreen = false;
};


#endif