#include "shader.h"
#include "container.h"
#include "listener.h"

//TEMP
#include "model.h"
#include "shader.h"
#include "GL/glew.h"

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

	//TEMP CODE START

	init();
	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.5f,  0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	0.5f,  0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f,

	};

	Model model = Model();
	model.create(vertices, sizeof(vertices), 3);
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
			model.draw();
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
}

void Container::update(float dt) {
}

void Container::init() {
	//??

	
}