#pragma once

#include "engine/helpers/Core.h"
#include "engine/core/Window.h"
#include "engine/events/Event.h"
#include "engine/core/LayerStack.h"


class Application {

public:
	Application();
	virtual ~Application() = default;
	int run();
	void onEvent(Event& e);
private:
	float m_LastFrameTime = 0;
	LayerStack m_LayerStack;
};
