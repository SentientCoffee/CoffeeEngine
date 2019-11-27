#include "CoffeePCH.h"
#include "Coffee/Application.h"

#include "Coffee/Logging.h"
#include "Coffee/Events/AppEvents.h"

using namespace Coffee;

Application::Application() {}

Application::~Application() {}

void Application::run() {

	WindowResizedEvent e(1280, 720);
	CF_TRACE(e);
	
	while(true);
}