#pragma once

#include "Coffee/Input.h"

namespace Coffee {

	class WindowsInput : public Input {
		
	protected:

		bool isKeyPressedImpl(int keyCode) override;
		bool isMouseButtonPressedImpl(int button) override;
		
		std::pair<float, float> getMousePosImpl() override;
		float getMouseXImpl() override;
		float getMouseYImpl() override;
	};
	
}