
// Luhao 2023/10/31

#include "../engine/Log.h"
#include "../engine/Platform/Window.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>

int main()
{
	Noval::Log::Init();
	LOG_INFO("Application Begin:");

	auto window = std::unique_ptr<Nova::Window>(Nova::Window::Create());

	while (1)
	{
		glClearColor((GLfloat)0.3, (GLfloat)0.3, (GLfloat)0.3, (GLfloat)1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		window->OnUpdate();
	}

    return 1;
}