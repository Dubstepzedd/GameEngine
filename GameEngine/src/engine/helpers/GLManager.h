#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include "engine/core/Window.h"

class  GLManager {

public:
    inline static void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
        if (type == GL_DEBUG_TYPE_ERROR)
            spdlog::error("[OpenGL ERROR]({}) {}", message, type);
        else {
            spdlog::debug("[OpenGL DEBUG]({}) {}", message, type);
        }
    }

    static bool initialize() {
        spdlog::info("Initializing OpenGL.");
        Window::getInstance().makeContext();

        int version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        if (version == 0) {
            spdlog::error("Failed to initialize GLEW.");
            return false;
        }

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(GLManager::MessageCallback, 0);
        glEnable(GL_DEPTH_TEST);
        return true;
    }
};