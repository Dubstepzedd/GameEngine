// Sandbox.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include "Engine.h"

class SandboxApp : public Application {
public:
    SandboxApp() : Application({
        .width = 1920,
        .height = 1080,
        .title = "My Sandbox Game",
        .isResizable = false,
        .vsync = true
    }) {}
};