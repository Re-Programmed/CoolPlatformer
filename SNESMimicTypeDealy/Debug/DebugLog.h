#pragma once
#if _DEBUG
#include <iostream>
#include <string>
#include <GLFW/glfw3.h>

namespace DEBUG
{
	static class DebugLog
	{
	public:
		/// <summary>
		/// Logs a warning.
		/// </summary>
		/// <param name="warning">The warning to show.</param>
		/// <param name="showTime">If true, shows the time elasped when the message was displayed.</param>
		/// <param name="additionalStyle">Any ANSI codes to add to the text. Must start with a ";".</param>
		static void LogWarning(std::string warning, bool showTime = true, std::string additionalStyle = "")
		{
			std::string ou = "\033[33" + additionalStyle + "m" + (showTime ? ("[" + std::to_string(glfwGetTime()) + "]") : "") + " [WARNING] " + warning + "\033[0m\n";

			std::cout << ou;
		}

		/// <summary>
		/// Logs.
		/// </summary>
		/// <param name="log">The text to show.</param>
		/// <param name="showTime">If true, shows the time elasped when the message was displayed.</param>
		/// <param name="additionalStyle">Any ANSI codes to add to the text. Must start with a ";".</param>
		static void Log(std::string log, bool showTime = true, std::string additionalStyle = "")
		{
			std::string ou = "\033[37" + additionalStyle + "m" + (showTime ? ("[" + std::to_string(glfwGetTime()) + "]") : "") + " [LOG] " + log + "\033[0m\n";

			std::cout << ou;
		}

		/// <summary>
		/// Logs that an error has occured.
		/// </summary>
		/// <param name="error"></param>
		static void LogError(std::string error)
		{
			std::string ou = "\033[1;31m[" + std::to_string(glfwGetTime()) + "] [ERROR] " + error + "\033[0m\n";

			std::cout << ou;
		}

		/// <summary>
		/// Logs plain text.
		/// </summary>
		/// <param name="log">The text to show.</param>
		/// <param name="showTime">If true, shows the time elasped when the message was displayed.</param>
		/// <param name="additionalStyle">Any ANSI codes to add to the text. Must start with a ";".</param>
		static void LogPlain(std::string log, std::string additionalStyle = "")
		{
			std::string ou = "\033[0" + additionalStyle + "m" + log + "\033[0m\n";

			std::cout << ou;
		}
	};
}
#endif