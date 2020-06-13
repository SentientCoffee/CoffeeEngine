#pragma once

#include "Coffee/Core/Core.h"

#include <functional>
#include <string>

namespace Coffee {

	enum class EventType : uint32_t {
		None = 0,
		
		WindowClosed,
		WindowResized,
		WindowFocused,
		WindowLostFocus,
		WindowMoved,

		AppTick,
		AppUpdate,
		AppRender,

		KeyPressed,
		KeyReleased,
		KeyTyped,

		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseScrolled
	};

	enum EventCategory {
		CategoryNone		= 0,
		CategoryApp			= BIT_SHIFT(0),
		CategoryInput		= BIT_SHIFT(1),
		CategoryKeyboard	= BIT_SHIFT(2),
		CategoryMouse		= BIT_SHIFT(3),
		CategoryMouseButton	= BIT_SHIFT(4)
	};




	
	#if CF_DEBUG || CF_RELEASE

	#define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::##type; }\
	                               virtual EventType getEventType() const override { return getStaticType(); }\
	                               virtual const char* getName() const override { return #type; }

	#define EVENT_CLASS_CATEGORY(flag) virtual int getCategoryFlags() const override { return flag; }

	#else

	#define EVENT_CLASS_TYPE(type)			static EventType getStaticType() { return EventType::##type; }\
											virtual EventType getEventType() const override { return getStaticType(); }\

	#define EVENT_CLASS_CATEGORY(flag)

	#endif



	

	class Event {

		friend class EventDispatcher;

	public:

		virtual EventType getEventType() const = 0;

		bool isHandled() const;
		
		#if CF_DEBUG || CF_RELEASE
		
		virtual const char* getName() const = 0;
		virtual int getCategoryFlags() const = 0;
		
		virtual std::string toString() const;
		bool hasCategoryFlag(EventCategory flag) const;
		
		#endif

	protected:

		Event() = default;
		virtual ~Event() = default;
		
		bool _isHandled = false;
	};

	class EventDispatcher {

		template<class T>
		using EventFunc = std::function<bool(T&)>;

	public:

		EventDispatcher(Event& event);

		template<class T>
		bool dispatch(EventFunc<T> func);

	private:

		Event& _event;
	};

	inline std::ostream& operator<<(std::ostream& out, const Event& e) { return out << e.toString(); }


	template <class T>
	bool EventDispatcher::dispatch(EventFunc<T> func) {

		if(_event.getEventType() == T::getStaticType()) {
			_event._isHandled = func(*static_cast<T*>(&_event));
			return true;
		}

		return false;
	}

}
