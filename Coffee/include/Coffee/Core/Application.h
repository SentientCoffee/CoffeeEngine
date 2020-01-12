#pragma once

#include "Coffee/Core/Core.h"
#include "Coffee/Core/Layer.h"
#include "Coffee/Core/Window.h"

#include "Coffee/Events/Event.h"
#include "Coffee/Events/AppEvents.h"

#include "Coffee/Imgui/ImguiLayer.h"

namespace Coffee {
	
	class Application {
	public:
		Application();
		virtual ~Application() = default;

		void run();

		void onEvent(Event& e);

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);

		Window& getWindow() const;
		
		static Application& getInstance();
		
	private:

		bool onWindowClosed(WindowClosedEvent& e);
		bool onWindowResized(WindowResizedEvent& e);
		
		Scope<Window> _window;
		bool _isRunning = true;
		bool _isMinimized = false;

		LayerStack _layerStack;
		ImguiLayer* _imguiLayer;

		float _lastFrameTime = 0.0f;
		
		static Application* _instance;
		
	};

	// To be defined in CLIENT
	Application* createApp();

}
