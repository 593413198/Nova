
// Luhao 2023.11.19

#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Nova {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}
