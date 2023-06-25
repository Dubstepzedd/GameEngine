#include "window.h"
/* Callback methods */

void onBufferUpdate(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void onResize(GLFWwindow* window, int width, int height) {
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
}

void Window::init() {

    /* Initialize GLFW */
    if (!glfwInit()) {
        //TODO Do something here, like log and save return code.
        exit(EXIT_FAILURE);
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(this->size.width, this->size.height, this->name.c_str(), NULL, NULL);
    
    /* If something went wrong, terminate GLFW. */
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    /* Standard Callbacks - shall not be changed! */
    glfwSetFramebufferSizeCallback(window, onBufferUpdate);
    glfwSetWindowSizeCallback(window, onResize);
}

void Window::setClearColor(const float r, const float g, const float b, const float a) {
    glClearColor(r, g, b, a);
}

void Window::update() {
 
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(this->window);
    glfwPollEvents();

}

Dimension Window::getSize() {
    Dimension size;
    glfwGetWindowSize(this->window, &size.width, &size.height);
    return size;
}
void Window::setSize(const int width, const int height) {
    glfwSetWindowSize(this->window, width, height);
}

bool Window::isRunning() {
    return !glfwWindowShouldClose(this->window);
}

void Window::makeContext() {
    glfwMakeContextCurrent(this->window);
    /* Set the viewport (render area) */
    glViewport(0, 0, this->size.width, this->size.height);
}