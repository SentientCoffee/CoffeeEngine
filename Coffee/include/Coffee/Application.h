#pragma once

#include "Core.h"
#include "Window.h"

#include "Events/Event.h"
#include "Events/AppEvents.h"

namespace Coffee {
	
	class COFFEE_API Application {
	public:
		Application();
		virtual ~Application();

		void run();

		void onEvent(Event& e);
		
	private:

		bool onWindowClosed(WindowClosedEvent& e);
		
		scope<Window> _window;
		bool _isRunning = true;
		
	};

	// To be defined in CLIENT
	Application* createApp();

}
