
// Luhao 2023.11.18

#include "OpenGLContext.h"
#include "Log.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "tracy/Tracy.hpp"

namespace Nova {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) :m_WindowHandle(windowHandle) {
		NOVA_ASSERT(windowHandle, "Window handle is null");
	}

	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		NOVA_ASSERT(status, "Failed to initialize Glad!");

		LOG_INFO("OpenGL Info:");
		LOG_INFO(" Vendor: {0}", (char*)glGetString(GL_VENDOR));
		LOG_INFO(" Renderer: {0}", (char*)glGetString(GL_RENDERER));
		LOG_INFO(" Version: {0}", (char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers() {
		ZoneScopedN("OpenGLContext_SwapBuffers");
		glfwSwapBuffers(m_WindowHandle);
	}
}

