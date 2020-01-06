#include "CoffeePCH.h"
#include "Coffee/Events/Event.h"

using namespace Coffee;

bool Event::isHandled() const { return _isHandled; }

#if CF_DEBUG || CF_RELEASE

std::string Event::toString() const { return getName(); }
bool Event::hasCategoryFlag(const EventCategory flag) const { return getCategoryFlags() & flag; }

#endif

EventDispatcher::EventDispatcher(Event& event) : _event(event) {}
