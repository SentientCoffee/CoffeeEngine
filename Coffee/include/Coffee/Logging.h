#pragma once

#include "Coffee/Core.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Coffee {

	class COFFEE_API Logger {
	public:
		
		static void init();

		inline static std::shared_ptr<spdlog::logger>& getEngineLogger();
		inline static std::shared_ptr<spdlog::logger>& getClientLogger();

	private:

		static std::shared_ptr<spdlog::logger> _engineLogger;
		static std::shared_ptr<spdlog::logger> _clientLogger;
	};
	
}

#if CF_DEBUG

// Core log macros
#define CF_CORE_CRITICAL(msg, ...)		::Coffee::Logger::getEngineLogger()->critical(msg, ##__VA_ARGS__);
#define CF_CORE_ERROR(msg, ...)			::Coffee::Logger::getEngineLogger()->error(msg, ##__VA_ARGS__);
#define CF_CORE_WARNING(msg, ...)		::Coffee::Logger::getEngineLogger()->warn(msg, ##__VA_ARGS__);
#define CF_CORE_INFO(msg, ...)			::Coffee::Logger::getEngineLogger()->info(msg, ##__VA_ARGS__);
#define CF_CORE_TRACE(msg, ...)			::Coffee::Logger::getEngineLogger()->trace(msg, ##__VA_ARGS__);

// Client log macros 
#define CF_CRITICAL(msg, ...)			::Coffee::Logger::getClientLogger()->critical(msg, ##__VA_ARGS__);
#define CF_ERROR(msg, ...)				::Coffee::Logger::getClientLogger()->error(msg, ##__VA_ARGS__);
#define CF_WARNING(msg, ...)			::Coffee::Logger::getClientLogger()->warn(msg, ##__VA_ARGS__);
#define CF_INFO(msg, ...)				::Coffee::Logger::getClientLogger()->info(msg, ##__VA_ARGS__);
#define CF_TRACE(msg, ...)				::Coffee::Logger::getClientLogger()->trace(msg, ##__VA_ARGS__);

#else

#define CF_CORE_FATAL(msg, ...)			__noop
#define CF_CORE_ERROR(msg, ...)			__noop
#define CF_CORE_WARNING(msg, ...)		__noop
#define CF_CORE_INFO(msg, ...)			__noop
#define CF_CORE_TRACE(msg, ...)			__noop

// Client log macros 
#define CF_FATAL(msg, ...)				__noop
#define CF_ERROR(msg, ...)				__noop
#define CF_WARNING(msg, ...)			__noop
#define CF_INFO(msg, ...)				__noop
#define CF_TRACE(msg, ...)				__noop

#endif