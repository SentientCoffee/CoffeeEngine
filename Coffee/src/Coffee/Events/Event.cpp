#include "CoffeePCH.h"
#include "Coffee/Events/Event.h"

using namespace Coffee;

#if CF_DEBUG || CF_RELEASE

std::string Event::toString() const { return getName(); }
inline bool Event::hasCategoryFlag(const EventCategory flag) const { return getCategoryFlags() & flag; }

#endif

EventDispatcher::EventDispatcher(Event& event) : _event(event) {}

template <class T>
bool EventDispatcher::dispatch(EventFunc<T> func) {
	
	if(_event.getEventType() == T::getStaticType()) {
		_event._isHandled = func(*static_cast<T*>(&_event));
		return true;
	}

	return false;
}
