#include "CoffeePCH.h"
#include "Coffee/Events/KeyEvents.h"

using namespace Coffee;

KeyEvent::KeyEvent(const int keyCode) : _keyCode(keyCode) {}

int KeyEvent::getKeyCode() const { return _keyCode; }

KeyPressedEvent::KeyPressedEvent(const int keyCode, const int repeatCount) :
	KeyEvent(keyCode), _repeatCount(repeatCount) {}

int KeyPressedEvent::getRepeatCount() const { return _repeatCount; }

KeyReleasedEvent::KeyReleasedEvent(const int keyCode) : KeyEvent(keyCode) {}

KeyTypedEvent::KeyTypedEvent(const int keyCode) : KeyEvent(keyCode) {}

#if CF_DEBUG || CF_RELEASE

std::string KeyPressedEvent::toString() const {
	std::string buffer = "KeyPressed: " + std::to_string(_keyCode) + " (" + std::to_string(_repeatCount) + " repeat(s))";
	return buffer;
}

std::string KeyReleasedEvent::toString() const {
	std::string buffer = "KeyReleased: " + std::to_string(_keyCode);
	return buffer;
}

std::string KeyTypedEvent::toString() const {
	std::string buffer = "KeyTyped: " + std::to_string(_keyCode);
	return buffer;
}

#endif