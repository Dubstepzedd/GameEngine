#pragma once
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include "engine/events/KeyEvent.h"
#include "engine/events/MouseEvent.h"

class Input {

public:
    static Input& getInstance()
    {
        static Input instance;
        
        return instance;
    }
    Input(const Input&) = delete;
    void operator=(const Input&) = delete;
    void onEvent(Event& e);
    bool isKeyPressed(int key) const;
    bool isButtonPressed(int button) const;
private:
    Input() {}
    bool m_Keys[350]{};
    bool m_Buttons[10]{};
    glm::vec2 mPos{};
    

};
