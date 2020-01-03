#pragma once

#include "Layer.h"

#include "Events/MouseEvents.h"
#include "Events/KeyEvents.h"
#include "Events/AppEvents.h"

namespace Coffee {

	class COFFEE_API ImguiLayer : public Layer {
	public:

		ImguiLayer();
		~ImguiLayer() = default;


		void onPush() override;
		void onPop() override;
		void update() override;
		void onEvent(Event& e) override;

	private:

		bool onMouseButtonPressed(MouseButtonPressedEvent& e);
		bool onMouseButtonReleased(MouseButtonReleasedEvent& e);
		bool onMouseMoved(MouseMovedEvent& e);
		bool onMouseScrolled(MouseScrolledEvent& e);
		
		bool onKeyPressed(KeyPressedEvent& e);
		bool onKeyReleased(KeyReleasedEvent &e);
		bool onKeyTyped(KeyTypedEvent& e);
		
		bool onWindowResized(WindowResizedEvent& e);
		
		float _currentTime;
		
	};
	
}
