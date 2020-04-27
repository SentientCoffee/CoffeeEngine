#pragma once
#include "Debug/Instrumentation.h"

#ifdef CF_PLATFORM_WINDOWS

extern "C" {
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x01;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 0x01;
}

int main(int argc, char** argv) {
	Coffee::Logger::init();

	CF_PROFILE_BEGIN_SESSION("Startup", "CoffeeProfile-Startup.json");
	auto* app = Coffee::createApp();
	CF_PROFILE_END_SESSION();

	CF_PROFILE_BEGIN_SESSION("Runtime", "CoffeeProfile-Runtime.json");
	app->run();
	CF_PROFILE_END_SESSION();

	CF_PROFILE_BEGIN_SESSION("Shutdown", "CoffeeProfile-Shutdown.json");
	delete app;
	CF_PROFILE_END_SESSION();
}

#endif
