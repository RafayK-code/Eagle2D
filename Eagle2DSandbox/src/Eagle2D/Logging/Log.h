#pragma once
#include "Logger.h"

namespace Eagle
{
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<Logger>& GetLogger() { return m_Logger; }
	private:
		static std::shared_ptr<Logger> m_Logger;
	};
}

#define EG_FATAL(...)  ::Eagle::Log::GetLogger()->Fatal(__VA_ARGS__)
#define EG_ERROR(...)  ::Eagle::Log::GetLogger()->Error(__VA_ARGS__)
#define EG_WARN(...)   ::Eagle::Log::GetLogger()->Warn(__VA_ARGS__)
#define EG_INFO(...)   ::Eagle::Log::GetLogger()->Info(__VA_ARGS__)
#define EG_TRACE(...)  ::Eagle::Log::GetLogger()->Trace(__VA_ARGS__)

#ifdef _DEBUG 
#ifdef EG_ENABLE_ASSERTS
#define EG_ASSERT(x, ...) {if(!(x)) {EG_FATAL("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
#define EG_ASSERT(x, ...)
#endif
#else
#define EG_ASSERT(x, ...)
#endif