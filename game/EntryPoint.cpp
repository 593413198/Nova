
// Luhao 2023/10/31

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../engine/Nova.h"

extern Nova::Application* Nova::CreateApplication();

int main()
{
	Noval::Log::Init();
	LOG_INFO("Application Begin:");

	auto app = Nova::CreateApplication();
	app->Run();

    return 1;
}