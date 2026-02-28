#include "engine/core/Application.h"

//Memory leak if we don't remove this?
Application* m_Application = nullptr;

Application::Application(const ApplicationConfig& config) {
	if (m_Application != nullptr) {
		spdlog::error("Application instance already exists.");
		throw std::bad_function_call();
	}

	spdlog::set_level(spdlog::level::debug); //Displays debug messages
	spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
	spdlog::info("[OpenGL Version] {}", glfwGetVersionString());

	m_AssetManager = std::make_shared<AssetManager>();
	m_Application = this;

	int code = Window::getInstance().create(config.title, config.width, config.height,
		config.vsync, config.isResizable);

	if (code == 1) {
		spdlog::error("Failed to start Window instance.");
		ENGINE_ASSERT("Failed to create Window instance.");
	}

}

int Application::run() {

	auto func = std::bind(&Application::onEvent, this, std::placeholders::_1);
	Window::getInstance().setOnEvent(func);

	
	float cd = 0;
	while (Window::getInstance().isRunning()) {
		float time = (float)glfwGetTime();
		TimeStep dt = time - m_LastFrameTime;
		m_LastFrameTime = time;
	
		/* We poll the events (has to be on main thread) */
		glfwPollEvents();

		/* Handle F11 keybind for fullscreen [Move outside this .cpp file]*/
		cd += dt.getMilliseconds();
		if (Input::getInstance().isKeyPressed(Key::F11) && cd >= 500) {
			Window::getInstance().setFullscreen(!Window::getInstance().isFullscreen());
			cd = 0;
		}
			
		for (Layer* layer : m_LayerStack) {
			layer->onUpdate(dt);
		}

	
		//Update
		Window::getInstance().swapBuffers();
		Renderer::getInstance().clear();
		
	
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		

	}

	/* Destroy objects and so fourth. */
	Window::getInstance().destroy();
	glfwTerminate();
	return 0;

}

void Application::onEvent(Event& event) {
	//Handle KeyBoard and Mouse button input.
	Renderer::getInstance().onEvent(event);
	Input::getInstance().onEvent(event);

	for (Layer* layer : m_LayerStack) {
		layer->onEvent(event);
	}
	
}

