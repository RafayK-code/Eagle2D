#include "egpch.h"
#include "Log.h"

namespace Eagle
{
	std::shared_ptr<Logger> Log::m_Logger;

	void Log::Init()
	{
		m_Logger = std::make_shared<Logger>();
	}
}