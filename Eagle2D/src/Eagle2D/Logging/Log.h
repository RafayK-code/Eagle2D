#pragma once
#include "Core.h"

#include "Logger.h"

#pragma warning(push)
#pragma warning(disable:4251)

namespace Eagle
{
	class EAGLE_API Log
	{
	public:
		static void Init(const char* name);

		static std::shared_ptr<Logger>& GetCoreLogger();
		static std::shared_ptr<Logger>& GetClientLogger();

	private:
		static std::shared_ptr<Logger> _CoreLogger;
		static std::shared_ptr<Logger> _ClientLogger;
	};
}

#pragma warning(push)

#define EG_CORE_FATAL(...)  ::Eagle::Log::GetCoreLogger()->Fatal(__VA_ARGS__)
#define EG_CORE_ERROR(...)  ::Eagle::Log::GetCoreLogger()->Error(__VA_ARGS__)
#define EG_CORE_WARN(...)   ::Eagle::Log::GetCoreLogger()->Warn(__VA_ARGS__)
#define EG_CORE_INFO(...)   ::Eagle::Log::GetCoreLogger()->Info(__VA_ARGS__)
#define EG_CORE_TRACE(...)  ::Eagle::Log::GetCoreLogger()->Trace(__VA_ARGS__)

#define EG_FATAL(...)       ::Eagle::Log::GetClientLogger()->Fatal(__VA_ARGS__)
#define EG_ERROR(...)       ::Eagle::Log::GetClientLogger()->Error(__VA_ARGS__)
#define EG_WARN(...)        ::Eagle::Log::GetClientLogger()->Warn(__VA_ARGS__)
#define EG_INFO(...)        ::Eagle::Log::GetClientLogger()->Info(__VA_ARGS__)
#define EG_TRACE(...)       ::Eagle::Log::GetClientLogger()->Trace(__VA_ARGS__)

#ifdef _DEBUG 
#ifdef EG_ENABLE_ASSERTS
#define EG_ASSERT(x, ...) {if(!(x)) {EG_FATAL("Assertion Failed: ", __VA_ARGS__); __debugbreak();}}
#define EG_CORE_ASSERT(x, ...) {if(!(x)) {EG_CORE_FATAL("Assertion Failed: ", __VA_ARGS__); __debugbreak();}}
#else
#define EG_ASSERT(x, ...)
#define EG_CORE_ASSERT(x, ...)
#endif
#else
#define EG_ASSERT(x, ...)
#define EG_CORE_ASSERT(x, ...)
#endif