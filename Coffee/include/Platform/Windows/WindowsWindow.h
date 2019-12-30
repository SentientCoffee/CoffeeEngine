#pragma once

#include "Coffee/Window.h"

#include <glfw/glfw3.h>

namespace Coffee {
	
	class WindowsWindow : public Window {
	public:

		WindowsWindow(const WindowProperties& properties);
		~WindowsWindow() override;

		void onUpdate() override;

		unsigned getWidth() const override;
		unsigned getHeight() const override;
		
		void setVSync(bool enabled) override;
		bool isVSync() const override;

		inline void setEventCallbackFunc(const EventCallbackFunc& callback) override;
	private:

		virtual void init(const WindowProperties& properties);
		virtual void shutdown();

		virtual void setCallbacks();
		static void glfwErrorCallback(int errorCode, const char* log);
		
		GLFWwindow* _window;

		struct WindowData {
			std::string title;
			unsigned width, height;
			bool isVSync;

			EventCallbackFunc eventFunc;
		};

		WindowData _data;
	};
}