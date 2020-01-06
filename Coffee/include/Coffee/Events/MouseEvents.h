#pragma once

#include "Event.h"

namespace Coffee {

	// -------------------------------------
	// ----- Mouse Moved Event -------------
	// -------------------------------------
	
	class MouseMovedEvent : public Event {
	public:

		MouseMovedEvent(float x, float y);

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(CategoryMouse | CategoryInput)

		float getMouseX() const;
		float getMouseY() const;

		#if CF_DEBUG || CF_RELEASE
		std::string toString() const override;
		#endif
		
	private:

		float _mouseX, _mouseY;
	};

	// -------------------------------------
	// ----- Mouse Button Events -----------
	// -------------------------------------
	
	class MouseButtonEvent : public Event {
	public:

		int getMouseButton() const;

		EVENT_CLASS_CATEGORY(CategoryMouseButton | CategoryInput)

	protected:

		explicit MouseButtonEvent(int button);

		int _mouseButton;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent {
	public:

		MouseButtonPressedEvent(int button);

		EVENT_CLASS_TYPE(MouseButtonPressed)
		
		#if CF_DEBUG || CF_RELEASE
		std::string toString() const override;
		#endif
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent {
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
	
	class MouseScrolledEvent : public Event {
	public:

		MouseScrolledEvent(float xOffset, float yOffset);

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(CategoryMouse | CategoryInput)

		float getXOffset() const;
		float getYOffset() const;

		#if CF_DEBUG || CF_RELEASE
		std::string toString() const override;
		#endif

	private:

		float _xOffset, _yOffset;
	};
}
