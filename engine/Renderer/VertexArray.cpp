
// Luhao 2023.11.19

#include "VertexArray.h"
#include "Renderer.h"
#include "Log.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Nova {
	VertexArray* VertexArray::Create() {
		switch (Renderer::GetDeviceType())
		{
		case RendererDeviceType::OpenGL:
			return new OpenGLVertexArray();
		};
		NOVA_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}