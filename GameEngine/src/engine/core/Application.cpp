#include "engine/core/Application.h"
#include "engine/events/Input.h"
#include <spdlog/spdlog.h>
#include "engine/helpers/TimeStep.h"
#include <functional>

//TEMP
#include "engine/gfx/Renderer.h"
#include "engine/gfx/Shader.h"
#include "engine/gfx/Buffer.h"
#include <cmath>
#include "engine/gfx/camera/PerspectiveCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include "engine/events/KeyCode.h"

//Memory leak if we don't remove this?
Application* m_Application = nullptr;

Application::Application() {
	if (m_Application != nullptr) {
		spdlog::error("Application instance already exists.");
		throw std::bad_function_call();
	}

	spdlog::set_level(spdlog::level::debug); //Displays debug messages
	spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
	spdlog::info("[OpenGL Version] {}", glfwGetVersionString());

	m_Application = this;
}

int Application::run() {

	int code = Window::getInstance().start("Test", 640, 640, false, true);
	if (code == 1) {
		spdlog::error("Failed to start Window instance.");
		return 1;
	}

	auto fp = std::bind(&Application::onEvent, this, std::placeholders::_1);
	Window::getInstance().setOnEvent(fp);

	VertexArray vArr = VertexArray();
	BufferLayout layout = { 
		{ShaderDataType::FLOAT3, "aPos"},
		{ShaderDataType::FLOAT3, "aColor"}
	};

	VertexBuffer buff = {
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f,0.0f, // top right
		 0.5f, -0.5f, 0.0f,   1.0f, 0.0f,0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   1.0f, 0.0f,0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 0.0f,0.0f  // top left 
	};
	vArr.setBuffer(buff, layout);

	IndexBuffer iBuff = { 
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	//TODO Improve Resources class to have relative paths.
	Shader shader = Shader("C:/Programming/GameEngine/GameEngine/res/shaders/shader.glsl");
	PerspectiveCamera camera = PerspectiveCamera(glm::vec3(0, 0, 3));
	shader.bind();
	camera.updateProj(shader);

	// TEMP CODE END
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

		const float cameraSpeed = 0.05f; // adjust accordingly
		if (Input::getInstance().isKeyPressed(Key::W))
			camera.setPos(camera.getPos() += cameraSpeed * camera.getFront());
		if (Input::getInstance().isKeyPressed(Key::S))
			camera.setPos(camera.getPos() -= cameraSpeed * camera.getFront());
		if (Input::getInstance().isKeyPressed(Key::A))
			camera.setPos(camera.getPos() - glm::normalize(glm::cross(camera.getFront(), camera.getUp())) * cameraSpeed);
		if (Input::getInstance().isKeyPressed(Key::D))
			camera.setPos(camera.getPos() + glm::normalize(glm::cross(camera.getFront(), camera.getUp())) * cameraSpeed);
	
		//Update
		Window::getInstance().swapBuffers();
		Renderer::clear();
		camera.updateView(shader);
		Renderer::draw(vArr, iBuff);
		
	
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		

	}
	//TEMP
	shader.unbind();

	/* Destroy objects and so fourth. */
	Window::getInstance().destroy();
	glfwTerminate();
	return 0;

}

void Application::onEvent(Event& event) {
	//Handle KeyBoard and Mouse button input.
	Input::getInstance().onEvent(event);

	for (Layer* layer : m_LayerStack) {
		layer->onEvent(event);
	}
	
}

