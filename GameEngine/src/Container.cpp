#include "GL/glew.h"
#include "Container.h"
#include "Listener.h"

//TEMP
#include "Renderer.h"
#include "Model.h"
#include "Shader.h"
#include "Buffer.h"

int Container::run() {

	int code = Window::getInstance().start("Test", 640, 640, false, true);
	if (code == 1)
		return 1;

	//!!!!
	/* We should probably make this multithreaded. When moving the window the updates stop.
	But we do not want the render thread to render before updates. We need to move glfwMakeContext to the render thread as well.*/

	//TODO FIX
	Window::getInstance().makeContext();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/* Initialzie glew */
	if (glewInit() != GLEW_OK) {
		return 1;
	}

	Window::getInstance().setClearColor(1, 1, 1, 1);

	VertexArray vArr = VertexArray();
	BufferLayout layout = { 
		{ShaderType::FLOAT3, "aPos"},
		{ShaderType::FLOAT3, "aColor"}
	};

	VertexBuffer buff = {
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left
		-0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 0.0f, // top left 
	};
	vArr.setBuffer(buff, layout);

	IndexBuffer iBuff = { 
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};


	Shader shader = Shader();
	shader.create("res/shaders/shader.glsl");

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
			render();
			//TEMP CODE
			shader.enable();
			Renderer::draw(vArr,iBuff);
			shader.disable();
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
	Window::getInstance().update();
	Renderer::clear();
}

void Container::update(const float dt) {
}
