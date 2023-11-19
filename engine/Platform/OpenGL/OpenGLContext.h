
// Luhao 2023.11.19

#pragma once

#include "Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Nova {
class OpenGLContext : public GraphicsContext {
public:
	OpenGLContext(GLFWwindow* windowHandle);

	virtual void Init() override;
	virtual void SwapBuffers() override;

private:
	GLFWwindow* m_WindowHandle;
};
}
