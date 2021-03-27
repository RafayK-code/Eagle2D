#pragma once
#include <memory>
#include <iostream>
#include <windows.h>

#pragma warning(push)
#pragma warning(disable:4251)

namespace Eagle
{
	class EAGLE_API Logger
	{
	public:
		Logger()
			: _Name("LOG")
		{
			_Console = GetStdHandle(STD_OUTPUT_HANDLE);
		}

		Logger(const char* name)
			: _Name(name)
		{
			_Console = GetStdHandle(STD_OUTPUT_HANDLE);
		}

		template <typename T, typename... Args>
		void Trace(const T& msg, Args&&... m_Args)
		{
			SetConsoleTextAttribute(_Console, 15);
			std::cout << _Name << " TRACE : " << msg;
			((std::cout << std::forward<Args>(m_Args)), ...);
			std::cout << std::endl;
		}

		template <typename T, typename... Args>
		void Info(const T& msg, Args&&... m_Args)
		{
			SetConsoleTextAttribute(_Console, 2);
			std::cout << _Name << " INFO : " << msg;
			((std::cout << std::forward<Args>(m_Args)), ...);
			std::cout << std::endl;
		}

		template <typename T, typename... Args>
		void Warn(const T& msg, Args&&... m_Args)
		{
			SetConsoleTextAttribute(_Console, 14);
			std::cout << _Name << " WARN : " << msg;
			((std::cout << std::forward<Args>(m_Args)), ...);
			std::cout << std::endl;
		}

		template <typename T, typename... Args>
		void Error(const T& msg, Args&&... m_Args)
		{
			SetConsoleTextAttribute(_Console, FOREGROUND_RED | FOREGROUND_GREEN);
			std::cout << _Name << " ERROR : " << msg;
			((std::cout << std::forward<Args>(m_Args)), ...);
			std::cout << std::endl;
		}

		template <typename T, typename... Args>
		void Fatal(const T& msg, Args&&... m_Args)
		{
			SetConsoleTextAttribute(_Console, 4);
			std::cout << _Name << " FATAL : " << msg;
			((std::cout << std::forward<Args>(m_Args)), ...);
			std::cout << std::endl;
		}

	private:
		HANDLE _Console;
		std::string _Name;
	};
}

#pragma warning(pop)