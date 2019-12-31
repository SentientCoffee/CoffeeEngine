#include "CoffeePCH.h"
#include "Coffee/Events/Event.h"

using namespace Coffee;

#if CF_DEBUG || CF_RELEASE

bool Event::isHandled() const { return _isHandled; }
std::string Event::toString() const { return getName(); }
inline bool Event::hasCategoryFlag(const EventCategory flag) const { return getCategoryFlags() & flag; }

#endif

EventDispatcher::EventDispatcher(Event& event) : _event(event) {}
