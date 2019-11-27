#include "CoffeePCH.h"
#include "Coffee/Events/KeyEvents.h"

using namespace Coffee;

KeyEvent::KeyEvent(const int keyCode) : _keyCode(keyCode) {}
inline int KeyEvent::getKeyCode() const { return _keyCode; }

KeyPressedEvent::KeyPressedEvent(const int keyCode, const int repeatCount) :
	KeyEvent(keyCode), _repeatCount(repeatCount) {}

int KeyPressedEvent::getRepeatCount() const { return _repeatCount; }

#if CF_DEBUG || CF_RELEASE

std::string KeyPressedEvent::toString() const {
	std::string buffer = "KeyPressedEvent: " + std::to_string(_keyCode) + " (" + std::to_string(_repeatCount) + " repeat(s))";
	return buffer;
}

KeyReleasedEvent::KeyReleasedEvent(const int keyCode) :
	KeyEvent(keyCode) {}

std::string KeyReleasedEvent::toString() const {
	std::string buffer = "KeyReleasedEvent: " + std::to_string(_keyCode);
	return buffer;
}

#endif