#pragma once
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>

class Listener {

public:
    static Listener& getInstance()
    {
        static Listener instance; 
        
        return instance;
    }

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void cursor_position_callback(GLFWwindow* window, double xPos, double yPos);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    bool isKeyPressed(int key);
    bool isButtonPressed(int btn);
    glm::vec2 getMousePos();

private:
    Listener() {}
    bool buttons[10]{};
    bool keys[300]{};
    glm::vec2 mPos{};
  
public:

    Listener(const Listener&) = delete;
    void operator=(const Listener&) = delete;

};
