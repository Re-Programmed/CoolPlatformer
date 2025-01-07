#pragma once

#ifdef _DEBUG

#include <vector>
#include <string>

class DebugCommands
{
public:
	static void RunRecieverThread();
	static void HandleCommands();
private:
	static std::vector<std::string> m_queuedCommands;
};

#endif // _DEBUG
