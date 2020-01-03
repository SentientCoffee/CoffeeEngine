#include "CoffeePCH.h"
#include "Coffee/Application.h"
#include "Coffee/Input.h"

using namespace Coffee;

Application* Application::_instance = nullptr;

Application::Application() {
	CF_CORE_ASSERT(!_instance, "Application already exists!");
	_instance = this;
	
	_window = scope<Window>(Window::create());
	_window->setEventCallbackFunc(CF_BIND_FN(Application::onEvent));
}

void Application::run() {

	while(_isRunning) {
		for(auto layer : _layerStack) {
			layer->update();
		}

		auto [mouseX, mouseY] = Input::getMousePosition();
		CF_CORE_TRACE("MOUSE POSITION: {0}, {1}", mouseX, mouseY);
		
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

void Application::pushLayer(Layer* layer) {_layerStack.pushLayer(layer); }
void Application::pushOverlay(Layer* overlay) { _layerStack.pushOverlay(overlay); }

Window& Application::getWindow() const { return *_window; }
Application& Application::getInstance() { return *_instance; }

bool Application::onWindowClosed(WindowClosedEvent& e) {
	_isRunning = false;
	return true;
}
