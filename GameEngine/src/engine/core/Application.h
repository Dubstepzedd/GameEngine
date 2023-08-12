#pragma once

#include "engine/helpers/Core.h"
#include "engine/core/Window.h"
#include "engine/events/Event.h"
#include "engine/core/LayerStack.h"
#include "engine/helpers/GLManager.h"
#include "engine/events/Input.h"
#include <spdlog/spdlog.h>
#include "engine/helpers/TimeStep.h"
#include <functional>
#include "engine/gfx/Renderer.h"

class Application {

public:
	Application();
	virtual ~Application() = default;
	int run();
	void onEvent(Event& e);
	void pushLayer(Layer* layer) { m_LayerStack.pushLayer(layer); }
	void removeLayer(Layer* layer) { m_LayerStack.popLayer(layer); }
private:
	float m_LastFrameTime = 0;
	LayerStack m_LayerStack;
};
