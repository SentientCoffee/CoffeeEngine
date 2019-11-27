#pragma once

#include "Core.h"

namespace Coffee {
	
	class COFFEE_API Application {
	public:
		Application();
		virtual ~Application();

		void run();
	};

	// To be defined in CLIENT
	Application* createApp();

}
