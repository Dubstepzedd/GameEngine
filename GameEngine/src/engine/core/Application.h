#pragma once

//Libraries
#include "engine/core/Window.h"
#include <atomic>
#include <time.h>
#include <thread>

class Application {

public:
	int run();

private:
	std::atomic<bool> isRender = false;
	float m_LastFrameTime = 0;
};
