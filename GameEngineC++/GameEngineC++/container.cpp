#include "container.h"


void Container::run() {

	Window window("Test", 600, 400);
	window.init();

	/* We should probably make this multithreaded. When moving the window the updates stop.
	But we do not want the render thread to render before updates. We need to move glfwMakeContext to the render thread as well.*/
	
	std::thread renderThread(&Container::render, this, std::ref(window));

	time_t start = clock();
	while (window.isRunning()) {
		time_t end = clock();
		double diff = difftime(end, start);
	
		while (diff >= UPDATE_FREQ) {
			start = end;
			diff -= UPDATE_FREQ;
			//Update here
			//TODO Maybe.. maybe add another thread here if it gets too complex.
			glfwPollEvents();

			//When this flag is true we render!
			this->active = true;
			
		}
		
	}

}

void Container::render(Window& window) {
	/* Make the window's context current */
	window.makeContext();
	
	while (window.isRunning()) {
		//std::cout << this->active << std::endl;
		if (this->active.load()) {
			//Render stuff
			window.update();
			this->active = false;
		}
	}
}


