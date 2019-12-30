#include "CoffeePCH.h"
#include "Coffee/Application.h"

using namespace Coffee;

Application::Application() {
	_window = scope<Window>(Window::create());
	_window->setEventCallbackFunc(CF_BIND_FN(Application::onEvent));
}

Application::~Application() {}

void Application::run() {

	while(_isRunning) {
		_window->onUpdate();
	}
}

void Application::onEvent(Event& e) {
	EventDispatcher dispatcher(e);
	dispatcher.dispatch<WindowClosedEvent>(CF_BIND_FN(Application::onWindowClosed));
	
	CF_CORE_TRACE("{0}", e);
}

bool Application::onWindowClosed(WindowClosedEvent& e) {
	_isRunning = false;
	return true;
}
