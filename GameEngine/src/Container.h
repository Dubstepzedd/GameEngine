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
	void update(const float dt);
	std::atomic<bool> isRender = false;
};
