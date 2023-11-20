
// Luhao 2023.11.20

#pragma once

#include "texture.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Nova
{
	std::shared_ptr<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererDeviceType::OpenGL:
			return std::make_shared<OpenGLTexture2D>(path);
		}
		NOVA_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}
