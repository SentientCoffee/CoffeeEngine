#include "CoffeePCH.h"
#include "Coffee/Debug/Instrumentation.h"

#include <iomanip>
#include <thread>

// ---------------------------------------------------------------------------------
// ----- Instrumentor --------------------------------------------------------------
// ---------------------------------------------------------------------------------

void Coffee::Instrumentor::beginSession(const std::string& name, const std::string& filepath) {
	std::lock_guard lock(_mutex);
	if(_currentSession) {
		if(Logger::getEngineLogger()) {
			CF_CORE_ERROR("Instrumentor::beginSession('{0}') when '{1}' already open!", name, _currentSession->name);
		}
		
		internalEndSession();
	}
	
	_outputStream.open(filepath);
	if(_outputStream.is_open()) {
		_currentSession = new InstrumentationSession({ name });
		writeHeader();
	}
	else {
		if(Logger::getEngineLogger()) {
			CF_CORE_ERROR("Instrumentor could not open results file '{0}'.", filepath);
		}
	}
}

void Coffee::Instrumentor::endSession() {
	std::lock_guard lock(_mutex);
	internalEndSession();
}

void Coffee::Instrumentor::internalEndSession() {
	if(_currentSession) {
		writeFooter();
		_outputStream.close();
		delete _currentSession;
		_currentSession = nullptr;
	}
}

void Coffee::Instrumentor::writeHeader() {
	_outputStream << R"({"otherData": {},"traceEvents":[{})";
	_outputStream.flush();
}

void Coffee::Instrumentor::writeFooter() {
	_outputStream << "]}";
	_outputStream.flush();
}

void Coffee::Instrumentor::writeProfile(const ProfileResult& result) {
	std::stringstream json;
	
	std::string name = result.name;
	std::replace(name.begin(), name.end(), '"', '\'');

	json << std::setprecision(3) << std::fixed
		<< ", {"
		<< R"("cat":"function", )"
		<< R"("dur":)" << result.elapsedTime.count() << ", "
		<< R"("name":")" << name << "\", "
		<< R"("ph":"X", )"
		<< R"("pid":0, )"
		<< R"("tid":)" << result.threadId << ", "
		<< R"("ts":)" << result.start.count()
		<< "}";

	std::lock_guard lock(_mutex);
	if(_currentSession) {
		_outputStream << json.str();
		_outputStream.flush();
	}
}

// ---------------------------------------------------------------------------------
// ----- InstrumentationTimer ------------------------------------------------------
// ---------------------------------------------------------------------------------

Coffee::InstrumentationTimer::InstrumentationTimer(const char* name) :
	_name(name)
{
	_startTimePoint = std::chrono::steady_clock::now();
}

Coffee::InstrumentationTimer::~InstrumentationTimer() {
	if(!_stopped) {
		stop();
	}
}

void Coffee::InstrumentationTimer::stop() {
	const auto endTimePoint = std::chrono::steady_clock::now();
	const auto start        = ProfileResult::FloatingPointMicroseconds { _startTimePoint.time_since_epoch() };
	const auto elapsed      = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(_startTimePoint).time_since_epoch();
	Instrumentor::getInstance().writeProfile({ _name, start, elapsed, std::this_thread::get_id() });

	_stopped = true;
}

