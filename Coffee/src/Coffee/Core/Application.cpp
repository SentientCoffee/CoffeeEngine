#include "CoffeePCH.h"
#include "Coffee/Core/Application.h"

#include "Coffee/Renderer/Renderer.h"
#include "Coffee/Core/Timestep.h"

#include <glfw/glfw3.h>

using namespace Coffee;

Application* Application::_instance = nullptr;

Application::Application() {
	CF_PROFILE_FUNCTION();
	
	CF_CORE_ASSERT(!_instance, "Application already exists!");
	_instance = this;
	
	_window = Scope<Window>(Window::create());
	_window->setEventCallbackFunc(CF_BIND_FN(Application::onEvent));

	Renderer::init();
	
	_imguiLayer = new ImguiLayer;
	pushOverlay(_imguiLayer);
}

Application::~Application() {
	CF_PROFILE_FUNCTION();
	
	Renderer::shutdown();
}

void Application::run() {
	CF_PROFILE_FUNCTION();
	
	while(_isRunning) {

		CF_PROFILE_SCOPE("[while(_isRunning)] - Application::run()");
		const auto time = static_cast<float>(glfwGetTime());
		const Timestep timestep = _lastFrameTime > 0 ? time - _lastFrameTime : 1.0f / 60.0f;
		_lastFrameTime = time;
		
		RenderCommand::clearScreen();

		if(!_isMinimized) {
			{
				CF_PROFILE_SCOPE("[layer->update] - Application::run()");
				for(auto layer : _layerStack) {
					layer->update(timestep);
				}
			}
			
		}

		_imguiLayer->begin();
		{
			CF_PROFILE_SCOPE("[drawImgui] - Application::run()");
			for(auto layer : _layerStack) {
				layer->drawImgui();
			}
		}
		_imguiLayer->end();

		_window->update();
	}
}

void Application::onEvent(Event& e) {
	CF_PROFILE_FUNCTION();
	
	EventDispatcher dispatcher(e);
	dispatcher.dispatch<WindowClosedEvent>(CF_BIND_FN(Application::onWindowClosed));
	dispatcher.dispatch<WindowResizedEvent>(CF_BIND_FN(Application::onWindowResized));

	for(auto it = _layerStack.end(); it != _layerStack.begin(); ) {
		(*--it)->onEvent(e);
		if(e.isHandled()) { break; }
	}
	
}

void Application::pushLayer(Layer* layer) {
	CF_PROFILE_FUNCTION();
	
	_layerStack.pushLayer(layer);
	layer->onPush();
}
void Application::pushOverlay(Layer* overlay) {
	CF_PROFILE_FUNCTION();

	_layerStack.pushOverlay(overlay);
	overlay->onPush();
}

Window& Application::getWindow() const { return *_window; }
Application& Application::getInstance() { return *_instance; }

bool Application::onWindowClosed(WindowClosedEvent& e) {
	_isRunning = false;
	return true;
}

bool Application::onWindowResized(WindowResizedEvent& e) {
	CF_PROFILE_FUNCTION();
	
	if(e.getWidth() == 0 || e.getHeight() == 0) {
		_isMinimized = true;
		return false;
	}

	_isMinimized = false;

	Renderer::onWindowResized(e.getWidth(), e.getHeight());
	
	return false;
}
