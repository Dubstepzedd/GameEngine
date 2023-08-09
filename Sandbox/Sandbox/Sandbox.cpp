// Sandbox.cpp : Defines the entry point for the application.
//

#include "Sandbox.h"
#include <Engine.h>
#include "TestLayer.h"

int main()
{
	TestLayer* layer = new TestLayer();
	SandboxApp* app = new SandboxApp();
	app->run();
	app->pushLayer((Layer*)layer);
	delete app;
}
