#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <GLFW/glfw3.h>


struct Vector {
	int x;
	int y;
};

struct Color {
	float r;
	float g;
	float b;
	float a;
};

class Window {

public:

	Window(const std::string name, const int width, const int height);

	void start(const bool vSync, const bool isResizable);
	void update();
	void setSize(const int width, const int height);
	bool isRunning();
	void setClearColor(const float r, const float g, const float b, const float a);
	Vector getSize();
	void makeContext();
	void destroy();
	void setVSync(const bool vSync);
	int getRefreshRate();
	int getResolutionY();
	int getResolutionX();
	void setFullscreen(const bool value);

	Vector getDimensions() {
		return this->size;
	}

	
private:
	Vector size;
	Vector pos;
	std::string name;
	GLFWwindow* window;
	bool vSync;
	const  GLFWvidmode* videoMode;
	Color clearColor;

};


#endif