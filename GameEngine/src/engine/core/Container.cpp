#include "GL/glew.h"
#include "engine/core/Container.h"
#include "engine/io/Listener.h"
#include <spdlog/spdlog.h>
//TEMP
#include "engine/gfx/Renderer.h"
#include "engine/gfx/Shader.h"
#include "engine/gfx/Buffer.h"
#include <cmath>

int Container::run() {

	spdlog::set_level(spdlog::level::debug); //Displays debug messages
	spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
	spdlog::info("[OpenGL Version] {}", glfwGetVersionString());


	int code = Window::getInstance().start("Test", 640, 640, false, true);
	if (code == 1) {
		spdlog::error("Failed to start Window instance.");
		return 1;
	}

	//!!!!
	/* We should probably make this multithreaded. When moving the window the updates stop.
	But we do not want the render thread to render before updates. We need to move glfwMakeContext to the render thread as well.*/


	VertexArray vArr = VertexArray();
	BufferLayout layout = { 
		{ShaderDataType::FLOAT3, "aPos"},
		{ShaderDataType::FLOAT3, "aColor"}
	};

	VertexBuffer buff = {
		 1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // top right
		 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
		-1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
		-1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f, // top left 
	};
	vArr.setBuffer(buff, layout);

	IndexBuffer iBuff = { 
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	Shader shader = Shader("res/shaders/shader.glsl");

	// TEMP CODE END
	float cd = 0;
	time_t start = clock();
	while (Window::getInstance().isRunning()) {
		time_t end = clock();
		double diff = difftime(end, start);

		while (diff >= UPDATE_FREQ) {
			start = end;
			
			/* We poll the events (has to be on main thread) */
			glfwPollEvents();

			/* Handle F11 keybind for fullscreen [Move outside this .cpp file]*/
			cd += UPDATE_FREQ;
			if (Listener::getInstance().isKeyPressed(GLFW_KEY_F11) && cd >= 500) {
				Window::getInstance().setFullscreen(!Window::getInstance().isFullscreen());
				cd = 0;
			}


			update((float)diff);
			diff -= UPDATE_FREQ;
			/* We set isUpdate to true, that thread will tell us when to render. */
			this->isRender = true;


		}

		if (this->isRender) {
			//Render stuff
			//TEMP CODE
			shader.bind();
			render();
			Renderer::draw(vArr, iBuff);
			shader.unbind();
			//
			this->isRender = false;
		}
		else {
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}

	}

	/* Destroy objects and so fourth. */
	Window::getInstance().destroy();
	glfwTerminate();
	return 0;

}

void Container::render() {
	Window::getInstance().swapBuffers();
	Renderer::clear();
}

void Container::update(const float dt) {
}
