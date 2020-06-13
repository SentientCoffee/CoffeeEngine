#pragma once

#include "Coffee/Events/Event.h"

namespace Coffee {

	struct WindowProperties {
		std::string title;
		uint32_t width, height;

		WindowProperties(const std::string& title  = "Coffee Engine",
			uint32_t width  = 1280,
			uint32_t height = 720);
	};
	
	class Window {
	public:
		
		using EventCallbackFunc = std::function<void(Event&)>;

		Window() = default;
		virtual ~Window() = default;
		
		static Window* create(const WindowProperties& properties = WindowProperties());

		virtual void update() = 0;

		virtual uint32_t getWidth() const = 0;
		virtual uint32_t getHeight() const = 0;

		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSync() const = 0;

		virtual void* getNativeWindow() const = 0;

		virtual void setEventCallbackFunc(const EventCallbackFunc& callback) = 0;
	};
	
}