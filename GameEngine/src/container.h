#pragma once

//Libraries
#include "Window.h"
#include <atomic>
#include <time.h>
#include <thread>

class Container {

public:
	int run();

private:
	static constexpr float UPDATE_FREQ = 1000.0f / 60.0f; // milliseconds
	void render();
	void update(float dt);
	void init();
	std::atomic<bool> isRender = false;
};
