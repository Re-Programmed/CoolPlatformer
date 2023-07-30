#include "glad/include/glad/glad.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include "rendering/Window.h"
#define STB_IMAGE_IMPLEMENTATION
#include "./stbi_image/stbi_image.h"
#include "Objects/GUI/StaticGUIElement.h"
#if _DEBUG
#include "./Debug/DebugLog.h"
#endif
#include "!TestGame/TestGame.h"
//#include "./Input/InputManager.h"

#define THREAD_LIMIT 128

using namespace GAME_NAME;

Window* ApplicationWindow;

void errorCallback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

//I'm not sure but I think this function is where the program starts. I'll have to check...
int main()
{
#if _DEBUG
	DEBUG::DebugLog::LogPlain("Started Application", ";1;36;42");
#endif

	glfwSetErrorCallback(errorCallback);

	if (!glfwInit())
	{
		exit(EXIT_FAILURE); //		:(
	}

	ApplicationWindow = new Window(true, new TestGame());

	glfwSwapInterval(1);

	while(!ApplicationWindow->ShouldClose())
	{
		ApplicationWindow->Render();
	}

	delete ApplicationWindow;

	//glfwTerminate();
}


