#include <GL/glew.h>
#include <iostream>
#include "engine/core/Window.h"
#include "engine/io/Listener.h"
#include <spdlog/spdlog.h>
#include "engine/core/GLManager.h"


int Window::start(const std::string name, const int w, const int h, bool vSync, bool isResizable) {


    // 1 = EXIT_FAILURE. 0 = EXIT_SUCCESS. Exit as in from the function.

    // This will not allow for multiple windows. We might want this in the future, but right now it will cause issues.
    if (m_Window != nullptr && isRunning()) {
        spdlog::error("The Window instance is already started.");
        return 1;
    }

    if (!glfwInit()) {
        spdlog::error("Failed to initialize GLFW.");
        return 1; 
    }

    setHints(isResizable);

    // Create a windowed mode window and its OpenGL context 
    m_Window = glfwCreateWindow(w, h, name.c_str(), NULL, NULL);

    if (!m_Window) {
        spdlog::error("Failed to create GLFWWindow.");
        glfwTerminate();
        return 1;
    }

    if (!GLManager::initialize()) {
        return 1;
    }

    /* Set variables */
    this->setVSync(vSync);
    m_WSize.x = w;
    m_WSize.y = h;
    this->setSize(this->m_WSize.x, this->m_WSize.y);
    this->m_VideoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    int fWidth, fHeight;
    glfwGetFramebufferSize(m_Window, &fWidth, &fHeight);
    glViewport(0, 0, fWidth, fHeight);
    /* Store the position for fullscreen toggle */
    glfwGetWindowPos(m_Window, &this->m_Pos.x, &this->m_Pos.y);

    setCallbacks();

    return 0;
}

void Window::setHints(const bool isResizable) {
    spdlog::debug("Setting Window hints.");
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, isResizable);
}

void Window::setCallbacks() {
    spdlog::debug("Setting Window callbacks.");
    glfwSetFramebufferSizeCallback(m_Window, Window::onBufferUpdate);
    glfwSetKeyCallback(m_Window, Listener::key_callback);
    glfwSetMouseButtonCallback(m_Window, Listener::mouse_button_callback);
    glfwSetCursorPosCallback(m_Window, Listener::cursor_position_callback);
}

void Window::swapBuffers() {
    glfwSwapBuffers(this->m_Window);
}


void Window::setClearColor(const float r, const float g, const float b, const float a) {
    m_ClearColor = { r,g,b,a };
    glClearColor(this->m_ClearColor.r, this->m_ClearColor.g, this->m_ClearColor.b, this->m_ClearColor.a);
}

glm::dvec2 Window::getSize() {
    glm::ivec2 size;
    glfwGetWindowSize(this->m_Window, &size.x, &size.y);
    return size;
}
void Window::setSize(const int width, const int height) {
    glfwSetWindowSize(this->m_Window, width, height);
}

bool Window::isRunning() {
    return !glfwWindowShouldClose(this->m_Window);
}

void Window::close() {
    glfwSetWindowShouldClose(this->m_Window, 1);
}

void Window::destroy() {
    glfwDestroyWindow(m_Window);
}
void Window::makeContext() {
    glfwMakeContextCurrent(this->m_Window);
}

void Window::setVSync(const bool vSync) {
    // If true, set 1, else 0.
    glfwSwapInterval(vSync ? 1 : 0);
    this->m_VSync = vSync;
}

void Window::setFullscreen(const bool value) {
    m_Fullscreen = value;
    if (value) {
        glfwGetWindowPos(m_Window, &this->m_Pos.x, &this->m_Pos.y);
        glfwGetWindowSize(m_Window, &this->m_WSize.x, &this->m_WSize.y);

        glfwSetWindowMonitor(m_Window, glfwGetPrimaryMonitor(), 0, 0, this->m_VideoMode->width, this->m_VideoMode->height, this->m_VideoMode->refreshRate);
    }
    else {
        glfwSetWindowMonitor(m_Window, NULL, this->m_Pos.x, this->m_Pos.y, this->m_WSize.x, this->m_WSize.y, this->m_VideoMode->refreshRate);
    }
}

int Window::getRefreshRate() {
    return this->m_VideoMode->refreshRate;
}


int Window::getResolutionY() {
    return this->m_VideoMode->height;
}

int Window::getResolutionX() {
    return this->m_VideoMode->width;
}

bool Window::isFullscreen() {
    return m_Fullscreen;
}

bool Window::isVSync() {
    return m_VSync;
}
