#include "container.h"
#include "listeners.h"

int Container::run() {


	Window window("Test", 520, 480);

	int code = window.start(false, true);

	if (code == 1)
		return 1;

	window.setClearColor(1, 0, 1, 1);
	/* We should probably make this multithreaded. When moving the window the updates stop.
	But we do not want the render thread to render before updates. We need to move glfwMakeContext to the render thread as well.*/
	
	std::thread renderThread(&Container::render, this, std::ref(window));

	std::cout << "Resoultion: " << window.getResolutionX() << ":" << window.getResolutionY() << std::endl;
	std::cout << "Refresh rate: " << window.getRefreshRate() << std::endl;
	float cd = 0;

	time_t start = clock();
	while (window.isRunning()) {
		time_t end = clock();
		double diff = difftime(end, start);
		
		while (diff >= UPDATE_FREQ) {
			start = end;
			diff -= UPDATE_FREQ;

			/* We poll the events (has to be on main thread) */
			glfwPollEvents();

			/* Handle F11 keybind for fullscreen */
			cd += UPDATE_FREQ;
			if (Listener::getInstance().isKeyPressed(GLFW_KEY_F11) && cd >= 500) {
				window.setFullscreen(!window.isFullscreen());
				cd = 0;
			}


			update(window);
			/* We set isUpdate to true, that thread will tell us when to render. */
			this->isRender = true;
		}
		
	}

	/* Wait for renderThread to exit. */
	renderThread.join();

	/* Destroy objects and so fourth. */
	window.destroy();
	glfwTerminate();
	return 0;

}

void Container::render(Window& window) {
	/* Make the window's context current */
	window.makeContext();

	while (window.isRunning()) {

		if (this->isRender) {
			//Render stuff
			window.update();
			this->isRender = false;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

}


void Container::update(Window& window) {
	std::cout << Listener::getInstance().getMousePos().x << std::endl;
}
