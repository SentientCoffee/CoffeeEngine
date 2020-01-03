#pragma once

#include "Event.h"

namespace Coffee {

	// -------------------------------------
	// ----- Mouse Moved Event -------------
	// -------------------------------------
	
	class COFFEE_API MouseMovedEvent : public Event {
	public:

		MouseMovedEvent(float x, float y);

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(CategoryMouse | CategoryInput)

		inline float getMouseX() const;
		inline float getMouseY() const;

		#if CF_DEBUG || CF_RELEASE
		std::string toString() const override;
		#endif
		
	private:

		float _mouseX, _mouseY;
	};

	// -------------------------------------
	// ----- Mouse Button Events -----------
	// -------------------------------------
	
	class COFFEE_API MouseButtonEvent : public Event {
	public:

		inline int getMouseButton() const;

		EVENT_CLASS_CATEGORY(CategoryMouseButton | CategoryInput)

	protected:

		explicit MouseButtonEvent(int button);

		int _mouseButton;
	};

	class COFFEE_API MouseButtonPressedEvent : public MouseButtonEvent {
	public:

		MouseButtonPressedEvent(int button);

		EVENT_CLASS_TYPE(MouseButtonPressed)
		
		#if CF_DEBUG || CF_RELEASE
		std::string toString() const override;
		#endif
	};

	class COFFEE_API MouseButtonReleasedEvent : public MouseButtonEvent {
	public:

		MouseButtonReleasedEvent(int button);

		EVENT_CLASS_TYPE(MouseButtonReleased)
		
		#if CF_DEBUG || CF_RELEASE
		std::string toString() const override;
		#endif
	};

	// -------------------------------------
	// ----- Mouse Scrolled Event ----------
	// -------------------------------------
	
	class COFFEE_API MouseScrolledEvent : public Event {
	public:

		MouseScrolledEvent(float xOffset, float yOffset);

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(CategoryMouse | CategoryInput)

		inline float getXOffset() const;
		inline float getYOffset() const;

		#if CF_DEBUG || CF_RELEASE
		std::string toString() const override;
		#endif

	private:

		float _xOffset, _yOffset;
	};
}
