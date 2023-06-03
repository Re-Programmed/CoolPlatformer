#include "glad/include/glad/glad.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include "rendering/Window.h"
#define STB_IMAGE_IMPLEMENTATION
#include "./stbi_image/stbi_image.h"
#include "Objects/GUI/StaticGUIElement.h"
//#include "./Input/InputManager.h"

using namespace GAME_NAME;

Window* ApplicationWindow;

void errorCallback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}


int main()
{
	glfwSetErrorCallback(errorCallback);

	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}
	ApplicationWindow = new Window(false);

	glfwSwapInterval(1);

	while(!ApplicationWindow->ShouldClose())
	{
		ApplicationWindow->Render();
	}

	delete ApplicationWindow;

	//glfwTerminate();
}


