// Sandbox.cpp : Defines the entry point for the application.
//

#include "Sandbox.h"
#include <Engine.h>
#include "TestLayer.h"

int main()
{	
	SandboxApp app = SandboxApp();
	TestLayer layer = TestLayer(app.getAssetManager());
	app.pushLayer(&layer);
	app.run();
}
