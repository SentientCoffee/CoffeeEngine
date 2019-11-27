#include "CoffeePCH.h"
#include "Coffee/Events/MouseEvents.h"

using namespace Coffee;

MouseMovedEvent::MouseMovedEvent(const float x, const float y) :
	_mouseX(x), _mouseY(y) {}

float MouseMovedEvent::getMouseX() const { return _mouseX; }
float MouseMovedEvent::getMouseY() const { return _mouseY; }

MouseButtonEvent::MouseButtonEvent(const int button) :
	_mouseButton(button) {}

int MouseButtonEvent::getMouseButton() const { return _mouseButton; }


MouseButtonPressedEvent::MouseButtonPressedEvent(const int button) :
	MouseButtonEvent(button) {}


MouseButtonReleasedEvent::MouseButtonReleasedEvent(const int button) :
	MouseButtonEvent(button) {}

MouseScrolledEvent::MouseScrolledEvent(const float xOffset, const float yOffset) :
	_xOffset(xOffset), _yOffset(yOffset) {}

float MouseScrolledEvent::getXOffset() const { return _xOffset; }
float MouseScrolledEvent::getYOffset() const { return _yOffset; }


#if CF_DEBUG || CF_RELEASE

std::string MouseMovedEvent::toString() const {
	std::string buffer = "MouseMovedEvent: " + std::to_string(_mouseX) + ", " + std::to_string(_mouseY);
	return buffer;
}

std::string MouseButtonPressedEvent::toString() const {
	std::string buffer = "MouseButtonPressedEvent: " + std::to_string(_mouseButton);
	return buffer;
}

std::string MouseButtonReleasedEvent::toString() const {
	std::string buffer = "MouseButtonReleasedEvent: " + std::to_string(_mouseButton);
	return buffer;
}

std::string MouseScrolledEvent::toString() const {
	std::string buffer = "MouseScrolledEvent: " + std::to_string(_xOffset) + ", " + std::to_string(_yOffset);
	return buffer;
}

#endif
