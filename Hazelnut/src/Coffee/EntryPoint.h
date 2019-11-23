#pragma once

#ifdef CF_PLATFORM_WINDOWS

int main(int argc, char** argv) {
	Coffee::Logger::init();
	
	auto app = Coffee::createApp();
	app->run();
	delete app;
}

#endif
