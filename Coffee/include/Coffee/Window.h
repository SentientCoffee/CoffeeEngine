#pragma once

#include "Coffee/Core.h"
#include "Coffee/Events/Event.h"

namespace Coffee {

	struct WindowProperties {
		std::string title;
		unsigned width, height;

		WindowProperties(const std::string& title  = "Coffee Engine",
		                 unsigned int       width  = 1280,
		                 unsigned int       height = 720);
	};
	
	class Window {
	public:
		
		using EventCallbackFunc = std::function<void(Event&)>;

		Window() = default;
		virtual ~Window() = default;
		
		static Window* create(const WindowProperties& properties = WindowProperties());

		virtual void update() = 0;

		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;

		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSync() const = 0;

		virtual void* getNativeWindow() const = 0;

		virtual void setEventCallbackFunc(const EventCallbackFunc& callback) = 0;
	};
	
}