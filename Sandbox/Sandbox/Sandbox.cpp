// Sandbox.cpp : Defines the entry point for the application.
//

#include "Sandbox.h"
#include <Engine.h>
#include "TestLayer.h"

int main()
{
	TestLayer layer = TestLayer();
	SandboxApp app = SandboxApp();
	app.pushLayer(&layer);
	app.run();
}
