#pragma once

#include "Event.h"

namespace Coffee {

	class COFFEE_API WindowResizedEvent : public Event {
	public:

		WindowResizedEvent(unsigned width, unsigned height);

		EVENT_CLASS_TYPE(WindowResized)
		EVENT_CLASS_CATEGORY(Application)
		
		inline unsigned getWidth() const;
		inline unsigned getHeight() const;

		#if CF_DEBUG || CF_RELEASE
		std::string toString() const override;
		#endif

	private:

		unsigned _width, _height;
	};


	class COFFEE_API WindowClosedEvent : public Event {
	public:

		WindowClosedEvent() = default;

		EVENT_CLASS_TYPE(WindowClosed)
		EVENT_CLASS_CATEGORY(Application)
	};

	class COFFEE_API AppTickEvent : public Event {
	public:

		AppTickEvent() = default;

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(Application)
	};

	class COFFEE_API AppUpdateEvent : public Event {
	public:

		AppUpdateEvent() = default;

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(Application)
	};

	class COFFEE_API AppRenderEvent : public Event {
	public:

		AppRenderEvent() = default;

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(Application)
	};
}