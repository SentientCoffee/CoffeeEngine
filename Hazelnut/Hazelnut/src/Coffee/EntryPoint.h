#pragma once

#ifdef CF_PLATFORM_WINDOWS

//extern Coffee::Application* Coffee::createApp();

int main(int argc, char** argv) {
	auto app = Coffee::createApp();
	app->run();
	delete app;
}

#endif
