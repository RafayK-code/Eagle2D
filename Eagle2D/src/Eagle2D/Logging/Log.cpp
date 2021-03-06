#include "egpch.h"
#include "Log.h"

namespace Eagle
{
	std::shared_ptr<Logger> Log::m_CoreLogger;
	std::shared_ptr<Logger> Log::m_ClientLogger;

	void Log::Init(std::string name)
	{
		m_CoreLogger = std::make_shared<Logger>("EAGLE");
		m_ClientLogger = std::make_shared<Logger>(name);
	}

	std::shared_ptr<Logger>& Log::GetCoreLogger()
	{
		return m_CoreLogger;
	}

	std::shared_ptr<Logger>& Log::GetClientLogger()
	{
		return m_ClientLogger;
	}
}