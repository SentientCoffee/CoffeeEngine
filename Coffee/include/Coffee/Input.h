#pragma once

#include "Core.h"
#include "KeyCodes.h"
#include "MouseButtonCodes.h"

namespace Coffee {

	class Input {
	public:

		static bool isKeyPressed(const int keyCode) { return _instance->isKeyPressedImpl(keyCode); }
		static bool isKeyPressed(const KeyCode keyCode) { return _instance->isKeyPressedImpl(static_cast<int>(keyCode)); }
		static bool isMouseButtonPressed(const int button) { return _instance->isMouseButtonPressedImpl(button); }
		static bool isMouseButtonPressed(const MouseButton button) { return _instance->isMouseButtonPressedImpl(static_cast<int>(button)); }

		static std::pair<float, float> getMousePosition() { return _instance->getMousePosImpl(); }
		static float getMouseX() { return _instance->getMouseXImpl(); }
		static float getMouseY() { return _instance->getMouseYImpl(); }
		
	protected:

		virtual bool isKeyPressedImpl(int keyCode) = 0;
		virtual bool isMouseButtonPressedImpl(int button) = 0;
		
		virtual std::pair<float, float> getMousePosImpl() = 0;
		virtual float getMouseXImpl() = 0;
		virtual float getMouseYImpl() = 0;
		
	private:

		static Input* _instance;
		
	};
	
}
