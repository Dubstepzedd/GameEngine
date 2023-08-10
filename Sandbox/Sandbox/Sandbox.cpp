// Sandbox.cpp : Defines the entry point for the application.
//

#include "Sandbox.h"
#include <Engine.h>
#include "TestLayer.h"

int main()
{
	TestLayer* layer = new TestLayer();
	SandboxApp* app = new SandboxApp();
	app->pushLayer((Layer*)layer); //OpenGL is not initilized and this causes a crash i believe
	app->run();
	delete app;
}
