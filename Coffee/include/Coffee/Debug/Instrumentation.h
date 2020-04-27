#pragma once

#include <string>
#include <chrono>
#include <fstream>

namespace Coffee {
	
	struct ProfileResult {
		using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;
		
		std::string name;
		FloatingPointMicroseconds start;
		std::chrono::microseconds elapsedTime;
		std::thread::id threadId;
	};

	struct InstrumentationSession {
		std::string name;
	};

	class Instrumentor {
	public:

		Instrumentor() = default;
		~Instrumentor() = default;

		void beginSession(const std::string& name, const std::string& filepath = "results.json");
		void endSession();

		void writeProfile(const ProfileResult& result);
		
		static Instrumentor& getInstance() {
			static Instrumentor instance;
			return instance;
		}

	private:

		void writeHeader();
		void writeFooter();
		void internalEndSession();

		std::mutex _mutex;
		InstrumentationSession* _currentSession = nullptr;
		std::ofstream _outputStream;
	};

	class InstrumentationTimer {

		using HighResClockTimePoint = std::chrono::time_point<std::chrono::steady_clock>;
		
	public:

		InstrumentationTimer(const char* name);
		~InstrumentationTimer();

		void stop();

	private:

		const char* _name;
		HighResClockTimePoint _startTimePoint {};
		bool _stopped = false;
	};
	
}

#if CF_ENABLE_PROFILING

#define CF_PROFILE_BEGIN_SESSION(name, filepath)	::Coffee::Instrumentor::getInstance().beginSession(name, filepath)
#define CF_PROFILE_END_SESSION()					::Coffee::Instrumentor::getInstance().endSession()
#define CF_PROFILE_SCOPE(name)						::Coffee::InstrumentationTimer timer##__LINE__(name)
#define CF_PROFILE_FUNCTION()						CF_PROFILE_SCOPE(__FUNCSIG__)

#else

#define CF_PROFILE_BEGIN_SESSION(name, filepath)
#define CF_PROFILE_END_SESSION()
#define CF_PROFILE_FUNCTION()
#define CF_PROFILE_SCOPE(name)

#endif