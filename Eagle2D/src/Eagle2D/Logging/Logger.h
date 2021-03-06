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
			: m_Name("LOG")
		{
			m_Console = GetStdHandle(STD_OUTPUT_HANDLE);
		}

		Logger(std::string name)
			: m_Name(name)
		{
			m_Console = GetStdHandle(STD_OUTPUT_HANDLE);
		}

		template <typename T, typename... Args>
		void Trace(const T& msg, Args&&... m_Args)
		{
			SetConsoleTextAttribute(m_Console, 15);
			std::cout << m_Name << " TRACE : " << msg;
			((std::cout << std::forward<Args>(m_Args)), ...);
			std::cout << std::endl;
		}

		template <typename T, typename... Args>
		void Info(const T& msg, Args&&... m_Args)
		{
			SetConsoleTextAttribute(m_Console, 2);
			std::cout << m_Name << " INFO : " << msg;
			((std::cout << std::forward<Args>(m_Args)), ...);
			std::cout << std::endl;
		}

		template <typename T, typename... Args>
		void Warn(const T& msg, Args&&... m_Args)
		{
			SetConsoleTextAttribute(m_Console, 14);
			std::cout << m_Name << " WARN : " << msg;
			((std::cout << std::forward<Args>(m_Args)), ...);
			std::cout << std::endl;
		}

		template <typename T, typename... Args>
		void Error(const T& msg, Args&&... m_Args)
		{
			SetConsoleTextAttribute(m_Console, FOREGROUND_RED | FOREGROUND_GREEN);
			std::cout << m_Name << " ERROR : " << msg;
			((std::cout << std::forward<Args>(m_Args)), ...);
			std::cout << std::endl;
		}

		template <typename T, typename... Args>
		void Fatal(const T& msg, Args&&... m_Args)
		{
			SetConsoleTextAttribute(m_Console, 4);
			std::cout << m_Name << " FATAL : " << msg;
			((std::cout << std::forward<Args>(m_Args)), ...);
			std::cout << std::endl;
		}

	private:
		HANDLE m_Console;
		std::string m_Name;
	};
}

#pragma warning(pop)