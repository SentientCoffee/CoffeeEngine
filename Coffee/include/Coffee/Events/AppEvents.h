#pragma once

#include "Event.h"

namespace Coffee {

	class WindowResizedEvent : public Event {
	public:

		WindowResizedEvent(uint32_t width, uint32_t height);

		EVENT_CLASS_TYPE(WindowResized)
		EVENT_CLASS_CATEGORY(CategoryApp)
		
		uint32_t getWidth() const;
		uint32_t getHeight() const;

		#if CF_DEBUG || CF_RELEASE
		std::string toString() const override;
		#endif

	private:

		uint32_t _width, _height;
	};


	class WindowClosedEvent : public Event {
	public:

		WindowClosedEvent() = default;

		EVENT_CLASS_TYPE(WindowClosed)
		EVENT_CLASS_CATEGORY(CategoryApp)
	};

	class AppTickEvent : public Event {
	public:

		AppTickEvent() = default;

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(CategoryApp)
	};

	class AppUpdateEvent : public Event {
	public:

		AppUpdateEvent() = default;

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(CategoryApp)
	};

	class AppRenderEvent : public Event {
	public:

		AppRenderEvent() = default;

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(CategoryApp)
	};
}