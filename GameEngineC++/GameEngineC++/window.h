#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <GLFW/glfw3.h>

struct Dimension {
	int width;
	int height;
};

class Window {

public:

	Window(const std::string name, const int width, const int height) {
		size = Dimension();
		size.width = width;
		size.height = height;
		this->name = name;
	}

	void init();
	void update();
	void setSize(const int width, const int height);
	bool isRunning();
	void setClearColor(const float r, const float g, const float b, const float a);
	Dimension getSize();
	void makeContext();

	Dimension getDimensions() {
		return this->size;
	}

	
private:
	Dimension size;
	std::string name;
	GLFWwindow* window;

};


#endif