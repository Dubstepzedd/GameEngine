#ifndef CONTAINER_H
#define CONTAINER_H

//Libraries
#include "window.h"
#include <atomic>
#include <time.h>
#include <thread>

class Container {

public:
	int run();
	
private:
	static constexpr float UPDATE_FREQ = 1000.0f / 60.0f; // milliseconds
	void render(Window& window);
	void update(Window& window);
	std::atomic<bool> isRender = false;
};

#endif