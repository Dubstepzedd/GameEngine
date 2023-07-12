#include "window.h"
#include "listener.h"

/* Callback methods */

void onBufferUpdate(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int Window::start(const std::string name, const int w, const int h, bool vSync, bool isResizable) {

    /* This will not allow for multiple windows. We might want this in the future, but right now it will cause issues.*/
    if (window != nullptr && isRunning()) {
        return 1;
    }

    /* 1 = EXIT_FAILURE. 0 = EXIT_SUCCESS. Exit as in from the function. */
    wSize.x = w;
    wSize.y = h;

    /* Initialize GLFW */
    if (!glfwInit()) {
        return 1; 
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(this->wSize.x, this->wSize.y, name.c_str(), NULL, NULL);

    /* If something went wrong, terminate GLFW. */
    if (!window) {
        glfwTerminate();
        return 1;
    }

    //Configure GLFW
    glfwWindowHint(GLFW_RESIZABLE, isResizable);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /* Set variables */
    this->setVSync(vSync);
    this->setSize(this->wSize.x, this->wSize.y);
    this->videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    int fWidth, fHeight;
    glfwGetFramebufferSize(window, &fWidth, &fHeight);
    glViewport(0, 0, fWidth, fHeight);

    /* Store the position for fullscreen toggle */
    glfwGetWindowPos(window, &this->pos.x, &this->pos.y);
    /* Standard Callbacks - shall not be changed! */
    glfwSetFramebufferSizeCallback(window, onBufferUpdate);

    glfwSetKeyCallback(window, Listener::key_callback);
    glfwSetMouseButtonCallback(window, Listener::mouse_button_callback);
    glfwSetCursorPosCallback(window, Listener::cursor_position_callback);

    return 0;
}

void Window::setClearColor(const float r, const float g, const float b, const float a) {
    this->clearColor.r = r;
    this->clearColor.g = g;
    this->clearColor.b = b;
    this->clearColor.a = a;
}

void Window::update() {
    glClearColor(this->clearColor.r, this->clearColor.g, this->clearColor.b, this->clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(this->window);

}

glm::dvec2 Window::getSize() {
    glm::ivec2 size;
    glfwGetWindowSize(this->window, &size.x, &size.y);
    return size;
}
void Window::setSize(const int width, const int height) {
    glfwSetWindowSize(this->window, width, height);
}

bool Window::isRunning() {
    return !glfwWindowShouldClose(this->window);
}

void Window::close() {
    glfwSetWindowShouldClose(this->window, 0);
}

void Window::destroy() {
    glfwDestroyWindow(window);
}
void Window::makeContext() {
    glfwMakeContextCurrent(this->window);
}

void Window::setVSync(const bool vSync) {
    // If true, set 1, else 0.
    glfwSwapInterval(vSync ? 1 : 0);
    this->vSync = vSync;
}

void Window::setFullscreen(const bool value) {
    fullscreen = value;
    if (value) {
        glfwGetWindowPos(window, &this->pos.x, &this->pos.y);
        glfwGetWindowSize(window, &this->wSize.x, &this->wSize.y);

        glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, this->videoMode->width, this->videoMode->height, this->videoMode->refreshRate);
    }
    else {
        glfwSetWindowMonitor(window, NULL, this->pos.x, this->pos.y, this->wSize.x, this->wSize.y, this->videoMode->refreshRate);
    }
}

int Window::getRefreshRate() {
    return this->videoMode->refreshRate;
}


int Window::getResolutionY() {
    return this->videoMode->height;
}

int Window::getResolutionX() {
    return this->videoMode->width;
}

bool Window::isFullscreen() {
    return fullscreen;
}

bool Window::isVSync() {
    return vSync;
}
