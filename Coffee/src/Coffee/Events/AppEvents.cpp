#include "CoffeePCH.h"
#include "Coffee/Events/AppEvents.h"

using namespace Coffee;

WindowResizedEvent::WindowResizedEvent(unsigned width, unsigned height) :
	_width(width), _height(height) {}

unsigned WindowResizedEvent::getWidth() const { return _width; }
unsigned WindowResizedEvent::getHeight() const { return _height; }

#if CF_DEBUG || CF_RELEASE

std::string WindowResizedEvent::toString() const {
	std::string buffer = "WindowResizedEvent: " + std::to_string(_width) + ", " + std::to_string(_height);
	return buffer;
}

#endif
