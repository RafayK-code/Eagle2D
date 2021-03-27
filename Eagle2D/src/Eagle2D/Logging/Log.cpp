#include "egpch.h"
#include "Log.h"

namespace Eagle
{
	std::shared_ptr<Logger> Log::_CoreLogger;
	std::shared_ptr<Logger> Log::_ClientLogger;

	void Log::Init(const char* name)
	{
		_CoreLogger = std::make_shared<Logger>("EAGLE");
		_ClientLogger = std::make_shared<Logger>(name);
	}

	std::shared_ptr<Logger>& Log::GetCoreLogger()
	{
		return _CoreLogger;
	}

	std::shared_ptr<Logger>& Log::GetClientLogger()
	{
		return _ClientLogger;
	}
}