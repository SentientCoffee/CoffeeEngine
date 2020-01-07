#pragma once

#include "Coffee/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Coffee {

	class OpenGLContext : public GraphicsContext {
	public:

		OpenGLContext(GLFWwindow* windowHandle);
		~OpenGLContext() = default;

		void init() override;
		void swapBuffers() override;
		
	private:

		GLFWwindow* _windowHandle;
		
	};
	
}