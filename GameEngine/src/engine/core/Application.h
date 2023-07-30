#pragma once

//Libraries
#include "engine/core/Window.h"
#include <atomic>
#include <time.h>
#include <thread>
#include "engine/events/Event.h"

class Application {

public:
	int run();
	void onEvent(Event& e);
private:
	std::atomic<bool> isRender = false;
	float m_LastFrameTime = 0;
};
