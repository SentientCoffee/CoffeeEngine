#pragma once

#include <memory>

// Platform check
#ifndef CF_PLATFORM_WINDOWS
	#error CoffeeEngine only supports Windows!
#endif

// Bit shift (bitfields, right now used for event flagging)
#define BIT_SHIFT(x) (1 << (x))

// Function binding
#define CF_BIND_FN(fn) std::bind(&fn, this, std::placeholders::_1)

// Asserts
#if CF_ENABLE_ASSERTS
	#define CF_CORE_ASSERT(exp, msg, ...)\
		if(!(exp)) {\
			CF_CORE_CRITICAL("ASSERTION FAILED: {0}", #exp);\
			CF_CORE_CRITICAL(msg, ##__VA_ARGS__);\
			__debugbreak();\
		}

	#define CF_ASSERT(exp, msg, ...)\
		if(!(exp)) {\
			CF_CRITICAL("ASSERTION FAILED: {0}", #exp);\
			CF_CRITICAL(msg, ##__VA_ARGS__);\
			__debugbreak();\
		}
#else
	#define CF_CORE_ASSERT(exp, ...)
	#define CF_ASSERT(exp, ...)
#endif

namespace Coffee {

	template<class T>
	using Scope = std::unique_ptr<T>;
	template<class T, typename ...Args>
	constexpr Scope<T> createScope(Args&& ...args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<class T>
	using Ref = std::shared_ptr<T>;
	template<class T, typename ...Args>
	constexpr Ref<T> createRef(Args&& ...args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}