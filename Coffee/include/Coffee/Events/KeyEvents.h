#pragma once

#include "Event.h"

namespace Coffee {

	// -------------------------------------
	// ----- Keyboard Events ---------------
	// -------------------------------------
	
	class KeyEvent : public Event {
	public:

		EVENT_CLASS_CATEGORY(CategoryKeyboard | CategoryInput)

		int getKeyCode() const;
		
	protected:

		explicit KeyEvent(int keyCode);

		int _keyCode;
	};
	
	class KeyPressedEvent : public KeyEvent {
	public:

		KeyPressedEvent(int keyCode, int repeatCount);

		EVENT_CLASS_TYPE(KeyPressed)

		int getRepeatCount() const;

		#if CF_DEBUG || CF_RELEASE
		std::string toString() const override;
		#endif

	private:

		int _repeatCount;
	};


	class KeyReleasedEvent : public KeyEvent {
	public:

		KeyReleasedEvent(int keyCode);

		EVENT_CLASS_TYPE(KeyReleased)
		
		#if CF_DEBUG || CF_RELEASE
		std::string toString() const override;
		#endif
	};

	class KeyTypedEvent : public KeyEvent {
	public:

		KeyTypedEvent(int keyCode);

		EVENT_CLASS_TYPE(KeyTyped)

		#if CF_DEBUG || CF_RELEASE
		std::string toString() const override;
		#endif
	};
	
}

