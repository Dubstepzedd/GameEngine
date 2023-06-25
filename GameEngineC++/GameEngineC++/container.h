#ifndef CONTAINER_H
#define CONTAINER_H

//Libraries
#include "window.h"
#include <atomic>
#include <time.h>
#include <cmath>
#include <thread>

class Container {

public:
	void run();
	
private:
	static constexpr float UPDATE_FREQ = 1000.0f / 60.0f; // seconds
	void render(Window& window);
	std::atomic<bool> active = false;
};

#endif