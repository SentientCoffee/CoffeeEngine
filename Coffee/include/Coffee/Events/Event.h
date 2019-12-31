#pragma once

#include "CoffeePCH.h"
#include "Coffee/Core.h"

namespace Coffee {

	enum class EventType : unsigned int {
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

		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseScrolled
	};

	enum EventCategory {
		None			= 0,
		App				= BIT_SHIFT(0),
		Input			= BIT_SHIFT(1),
		Keyboard		= BIT_SHIFT(2),
		Mouse			= BIT_SHIFT(3),
		MouseButton		= BIT_SHIFT(4)
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



	

	class COFFEE_API Event {

		friend class EventDispatcher;

	public:

		virtual EventType getEventType() const = 0;

		bool isHandled() const;
		
		#if CF_DEBUG || CF_RELEASE
		
		virtual const char* getName() const = 0;
		virtual int getCategoryFlags() const = 0;
		
		virtual std::string toString() const;
		inline bool hasCategoryFlag(EventCategory flag) const;
		
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