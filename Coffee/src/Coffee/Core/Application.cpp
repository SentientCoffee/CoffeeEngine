#include "CoffeePCH.h"
#include "Coffee/Core/Application.h"

#include "Coffee/Renderer/Renderer.h"
#include "Coffee/Core/Timestep.h"

#include <glfw/glfw3.h>

using namespace Coffee;

Application* Application::_instance = nullptr;

Application::Application() {
	
	CF_CORE_ASSERT(!_instance, "Application already exists!");
	_instance = this;
	
	_window = Scope<Window>(Window::create());
	_window->setEventCallbackFunc(CF_BIND_FN(Application::onEvent));

	Renderer::init();
	
	_imguiLayer = new ImguiLayer;
	pushOverlay(_imguiLayer);
	
}

void Application::run() {

	while(_isRunning) {

		const auto time = static_cast<float>(glfwGetTime());
		Timestep timestep = _lastFrameTime > 0 ? time - _lastFrameTime : 1.0f / 60.0f;
		_lastFrameTime = time;
		
		RenderCommand::clearScreen();

		if(!_isMinimized) {
			for(auto layer : _layerStack) {
				layer->update(timestep);
			}
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

bool Application::onWindowResized(WindowResizedEvent& e) {
	if(e.getWidth() == 0 || e.getHeight() == 0) {
		_isMinimized = true;
		return false;
	}

	_isMinimized = false;

	Renderer::onWindowResized(e.getWidth(), e.getHeight());
	
	return false;
}
