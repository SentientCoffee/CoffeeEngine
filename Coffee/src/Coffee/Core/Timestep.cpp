#include "CoffeePCH.h"
#include "Coffee/Core/Timestep.h"

using namespace Coffee;

Timestep::Timestep(const float time) :
	_time(time) {}

Timestep::operator float() const { return _time; }

float Timestep::getSeconds() const { return _time; }
float Timestep::getMilliseconds() const { return _time * 1000.0f; }
