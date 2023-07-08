#include "container.h"
#include "listener.h"
#include "shader.h"

int Container::run() {


	int code = Window::getInstance().start("Test", 520, 480, false, true);
	if (code == 1)
		return 1;

	Window::getInstance().setClearColor(1, 0, 1, 1);
	/* We should probably make this multithreaded. When moving the window the updates stop.
	But we do not want the render thread to render before updates. We need to move glfwMakeContext to the render thread as well.*/
	
	std::thread renderThread(&Container::render, this);
	Shader shader("res/shaders/shader.glsl");
	float cd = 0;

	time_t start = clock();
	while (Window::getInstance().isRunning()) {
		time_t end = clock();
		double diff = difftime(end, start);

		while (diff >= UPDATE_FREQ) {
			start = end;

			/* We poll the events (has to be on main thread) */
			glfwPollEvents();

			/* Handle F11 keybind for fullscreen */
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

	}

	/* Wait for renderThread to exit. */
	renderThread.join();

	/* Destroy objects and so fourth. */
	Window::getInstance().destroy();
	glfwTerminate();
	return 0;

}

void Container::render() {
	/* Make the window's context current */
	Window::getInstance().makeContext();

	while (Window::getInstance().isRunning()) {

		if (this->isRender) {
			//Render stuff
			Window::getInstance().update();
			this->isRender = false;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

}


void Container::update(float dt) {
}