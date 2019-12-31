#include "CoffeePCH.h"
#include "Coffee/Application.h"

using namespace Coffee;

Application::Application() {
	_window = scope<Window>(Window::create());
	_window->setEventCallbackFunc(CF_BIND_FN(Application::onEvent));
}

void Application::run() {

	while(_isRunning) {
		for(auto layer : _layerStack) {
			layer->update();
		}
		
		_window->update();
	}
}

void Application::onEvent(Event& e) {
	EventDispatcher dispatcher(e);
	dispatcher.dispatch<WindowClosedEvent>(CF_BIND_FN(Application::onWindowClosed));

	for(auto it = _layerStack.end(); it != _layerStack.begin(); ) {
		(*--it)->onEvent(e);
		if(e.isHandled()) { break; }
	}
}

void Application::pushLayer(Layer* layer) { _layerStack.pushLayer(layer); }
void Application::pushOverlay(Layer* overlay) { _layerStack.pushOverlay(overlay); }

bool Application::onWindowClosed(WindowClosedEvent& e) {
	_isRunning = false;
	return true;
}
