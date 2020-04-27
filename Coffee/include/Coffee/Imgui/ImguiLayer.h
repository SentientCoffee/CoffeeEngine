#pragma once

#include "Coffee/Core/Layer.h"

namespace Coffee {

	class ImguiLayer : public Layer {
	public:

		ImguiLayer();
		~ImguiLayer() = default;

		void onPush() override;
		void onPop() override;
		void drawImgui() override {}

		void begin();
		void end();

	private:
		
		float _currentTime = 0.0f;
		
	};
	
}
