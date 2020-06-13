#include "CoffeePCH.h"
#include "Coffee/Events/AppEvents.h"

using namespace Coffee;

WindowResizedEvent::WindowResizedEvent(const uint32_t width, const uint32_t height) :
	_width(width), _height(height) {}

uint32_t WindowResizedEvent::getWidth() const { return _width; }
uint32_t WindowResizedEvent::getHeight() const { return _height; }

#if CF_DEBUG || CF_RELEASE

std::string WindowResizedEvent::toString() const {
	std::string buffer = "WindowResized: " + std::to_string(_width) + ", " + std::to_string(_height);
	return buffer;
}

#endif
