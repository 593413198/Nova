
// Luhao 2023.11.19

#include "Buffer.h"
#include "Log.h"
#include "Platform/OpenGL/OpenGLContext.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Renderer.h"

namespace Nova {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
		// 目前只支持 OpenGL
		switch (Renderer::GetDeviceType())
		{
		case RendererDeviceType::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		}
		NOVA_ASSERT(false, "Unkown Device Type");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size) {
		// 目前只支持 OpenGL
		switch (Renderer::GetDeviceType())
		{
		case RendererDeviceType::OpenGL:
			return new OpenGLIndexBuffer(indices, size);
		}

		NOVA_ASSERT(false, "Unkown Device Type");
		return nullptr;
	}
}
