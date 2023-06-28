#include "window.h"
/* Callback methods */

void onBufferUpdate(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

/* Other */
/* TODO: Make class singleton? Should only be one. */
Window::Window(const std::string name, const int width, const int height) {
    this->size = Vector();
    this->size.x = width;
    this->size.y = height;
    this->name = name;
    this->clearColor = clearColor;
}

void Window::start(const bool vSync, const bool isResizeable) {

    /* Initialize GLFW */
    if (!glfwInit()) {
        //TODO Do something here, like log and save return code.
        exit(EXIT_FAILURE);
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(this->size.x, this->size.y, this->name.c_str(), NULL, NULL);
    
    /* If something went wrong, terminate GLFW. */
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    //Configure GLFW
    glfwWindowHint(GLFW_RESIZABLE, isResizeable);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /* Set variables */
    this->setVSync(vSync);
    this->setSize(this->size.x, this->size.y);
    this->videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    /* Store the position for fullscreen toggle */
    glfwGetWindowPos(window, &this->pos.x, &this->pos.y);
    /* Standard Callbacks - shall not be changed! */
    glfwSetFramebufferSizeCallback(window, onBufferUpdate);
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

Vector Window::getSize() {
    Vector size;
    glfwGetWindowSize(this->window, &size.x, &size.y);
    return size;
}
void Window::setSize(const int width, const int height) {
    glfwSetWindowSize(this->window, width, height);
}

bool Window::isRunning() {
    return !glfwWindowShouldClose(this->window);
}

void Window::destroy() {
    glfwDestroyWindow(window);
}
void Window::makeContext() {
    glfwMakeContextCurrent(this->window);
    /* Set the viewport (render area) */
    glViewport(0, 0, this->size.x, this->size.y);
}

void Window::setVSync(const bool vSync) {
    // If true, set 1, else 0.
    glfwSwapInterval(vSync ? 1 : 0);
    this->vSync = vSync;
}

void Window::setFullscreen(const bool value) {
    if (value) {
        glfwGetWindowPos(window, &this->pos.x, &this->pos.y);
        glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, this->videoMode->width, this->videoMode->height, this->videoMode->refreshRate);
    }
    else {
        glfwSetWindowMonitor(window, NULL, this->pos.x, this->pos.y, this->size.x, this->size.y, this->videoMode->refreshRate);
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
