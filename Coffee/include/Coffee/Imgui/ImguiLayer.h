#pragma once

#include "Coffee/Layer.h"

#include "Coffee/Events/MouseEvents.h"
#include "Coffee/Events/KeyEvents.h"
#include "Coffee/Events/AppEvents.h"

namespace Coffee {

	class ImguiLayer : public Layer {
	public:

		ImguiLayer();
		~ImguiLayer() = default;

		void onPush() override;
		void onPop() override;
		void drawImgui() override;

		void begin();
		void end();

	private:
		
		float _currentTime = 0.0f;
		
	};
	
}
