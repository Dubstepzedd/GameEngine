#include "SandboxApp.h"

int main() {
	SandboxApp* app = new SandboxApp();
	app->run();
	delete app;
}