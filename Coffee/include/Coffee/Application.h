#pragma once

#include "Core.h"
#include "Window.h"
#include "Layer.h"

#include "Events/Event.h"
#include "Events/AppEvents.h"
#include "Imgui/ImguiLayer.h"

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
		
		scope<Window> _window;
		bool _isRunning = true;

		LayerStack _layerStack;
		ImguiLayer* _imguiLayer;

		
		static Application* _instance;
		
	};

	// To be defined in CLIENT
	Application* createApp();

}
