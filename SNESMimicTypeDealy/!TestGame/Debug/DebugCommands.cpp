#ifdef _DEBUG

#include "DebugCommands.h"
#include <thread>
#include "../TestGame.h"
#include <iostream>

#include "../../Debug/DebugLog.h"

#include "../Objects/Environment/Effects/Rain.h"

#define DebugCommands_Log(x) DEBUG::DebugLog::Log(std::string("[Debug Commands] ").append(x), true, ";33");

std::vector<std::string> DebugCommands::m_queuedCommands = std::vector<std::string>(2);

void DebugCommands::RunRecieverThread()
{

	std::thread debugRecieveThread([]() {

		//Random sleep.
		Sleep(1000);
		DEBUG::DebugLog::Log("[Debug Commands] Initilized!", true, ";33");

		while (!glfwWindowShouldClose(GAME_NAME::TestGame::FirstWindow))
		{
			std::string input;
			std::cin >> input;

			m_queuedCommands.push_back(input);
		}
		});

	debugRecieveThread.detach();
}

void DebugCommands::HandleCommands()
{
	for (auto input : m_queuedCommands)
	{
		if (input == "ping")
		{
			DEBUG::DebugLog::Log("[Debug Commands] Pong", true, ";33");
			continue;
		}

		if (input == "rainon")
		{
			DebugCommands_Log("Toggled Rain On.");

			GAME_NAME::Objects::Environment::Effects::Rain::StartRainEffect();
			continue;
		}

		if (input == "rainoff")
		{
			DebugCommands_Log("Toggled Rain Off.");

			GAME_NAME::Objects::Environment::Effects::Rain::EndRainEffect();
			continue;
		}
	}

	m_queuedCommands.clear();
}

#endif