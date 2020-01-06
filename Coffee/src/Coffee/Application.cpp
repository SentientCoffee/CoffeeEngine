#include "CoffeePCH.h"
#include "Coffee/Application.h"

#include <glad/glad.h>

using namespace Coffee;

Application* Application::_instance = nullptr;

Application::Application() {
	CF_CORE_ASSERT(!_instance, "Application already exists!");
	_instance = this;
	
	_window = scope<Window>(Window::create());
	_window->setEventCallbackFunc(CF_BIND_FN(Application::onEvent));

	_imguiLayer = new ImguiLayer;
	pushOverlay(_imguiLayer);
}

void Application::run() {

	while(_isRunning) {
		glClearColor(0.1f, 0.2f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		for(auto layer : _layerStack) {
			layer->update();
		}

		_imguiLayer->begin();
		for(auto layer : _layerStack) {
			layer->drawImgui();
		}
		_imguiLayer->end();
		
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
