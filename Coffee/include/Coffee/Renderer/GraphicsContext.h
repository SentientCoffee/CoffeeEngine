#pragma once

namespace Coffee {

	class GraphicsContext {
	public:

		GraphicsContext() = default;
		virtual ~GraphicsContext() = default;
		
		virtual void init() = 0;
		virtual void swapBuffers() = 0;
	};
	
}