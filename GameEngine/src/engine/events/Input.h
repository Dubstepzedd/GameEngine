#pragma once
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include "engine/events/KeyEvent.h"

class Input {

public:
    static Input& getInstance()
    {
        static Input instance;
        
        return instance;
    }
    Input(const Input&) = delete;
    void operator=(const Input&) = delete;
    void onEvent(KeyEvent& e);
    bool isKeyPressed(int key);

private:
    Input() {}
    bool keys[350]{};
    glm::vec2 mPos{};
    

};
