#include "container.h"

void Container::run() {

	Window window("Test", 1920, 1080);
	
	window.start(false, true);
	window.setClearColor(1, 1, 1, 1);

	/* We should probably make this multithreaded. When moving the window the updates stop.
	But we do not want the render thread to render before updates. We need to move glfwMakeContext to the render thread as well.*/
	
	std::thread renderThread(&Container::render, this, std::ref(window));

	std::cout << "Resoultion: " << window.getResolutionX() << ":" << window.getResolutionY() << std::endl;
	std::cout << "Refresh rate: " << window.getRefreshRate() << std::endl;

	time_t start = clock();
	while (window.isRunning()) {
		time_t end = clock();
		double diff = difftime(end, start);
		
		while (diff >= UPDATE_FREQ) {
			start = end;
			diff -= UPDATE_FREQ;
			/* We poll the events (has to be on main thread) */
			glfwPollEvents();
			update(window);
			/* We set isUpdate to true, that thread will tell us when to render. */
			this->isRender = true;
		}
		
	}

	window.destroy();
	glfwTerminate();

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
	

}
