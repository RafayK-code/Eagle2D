#pragma once
#include <memory>
#include <iostream>
#include <windows.h>

namespace Eagle
{
	class Logger
	{
	public:
		Logger()
		{
			m_Console = GetStdHandle(STD_OUTPUT_HANDLE);
		}

		template <typename T, typename... Args>
		void Trace(const T& msg, Args&&... m_Args)
		{
			SetConsoleTextAttribute(m_Console, 15);
			std::cout << msg;
			((std::cout << std::forward<Args>(m_Args)), ...);
			std::cout << std::endl;
		}

		template <typename T, typename... Args>
		void Info(const T& msg, Args&&... m_Args)
		{
			SetConsoleTextAttribute(m_Console, 2);
			std::cout << msg;
			((std::cout << std::forward<Args>(m_Args)), ...);
			std::cout << std::endl;
		}

		template <typename T, typename... Args>
		void Warn(const T& msg, Args&&... m_Args)
		{
			SetConsoleTextAttribute(m_Console, 14);
			std::cout << msg;
			((std::cout << std::forward<Args>(m_Args)), ...);
			std::cout << std::endl;
		}

		template <typename T, typename... Args>
		void Error(const T& msg, Args&&... m_Args)
		{
			SetConsoleTextAttribute(m_Console, FOREGROUND_RED | FOREGROUND_GREEN);
			std::cout << msg;
			((std::cout << std::forward<Args>(m_Args)), ...);
			std::cout << std::endl;
		}

		template <typename T, typename... Args>
		void Fatal(const T& msg, Args&&... m_Args)
		{
			SetConsoleTextAttribute(m_Console, 4);
			std::cout << msg;
			((std::cout << std::forward<Args>(m_Args)), ...);
			std::cout << std::endl;
		}

	private:
		HANDLE m_Console;
	};
}