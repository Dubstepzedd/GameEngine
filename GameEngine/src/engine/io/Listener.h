#pragma once
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>

class Listener {

public:
    static Listener& getInstance()
    {
        static Listener instance; // Guaranteed to be destroyed (stack).
        // Instantiated on first use.
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
    // C++ 11
    // =======
    // We can use the better technique of deleting the methods
    // we don't want.
    Listener(const Listener&) = delete;
    void operator=(const Listener&) = delete;

    // Note: Scott Meyers mentions in his Effective Modern
    //       C++ book, that deleted functions should generally
    //       be public as it results in better error messages
    //       due to the compilers behavior to check accessibility
    //       before deleted status
};
